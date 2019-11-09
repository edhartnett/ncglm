/*
  Code to read data from the GOES-17 Global Lightning Mapper.

  Ed Hartnett, 10/10/19
  Amsterdam
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/time.h> /* Extra high precision time info. */
#include <math.h>
#include <assert.h>
#include <netcdf.h>
#include "goes_glm.h"

/* Attribute names. */
#define TITLE "title"
#define SUMMARY "summary"
#define PLATFORM_ID "platform_ID"

/* Number of timing runs when -t option is used. */
#define NUM_TRIALS 10

/* Usage description. */
#define USAGE   "\
  [-v]        Verbose\n\
  [-t]        Perform timing runs\n"

/**
 * Read and unpack all the event data in the file. It will be loaded
 * into the pre-allocated array of struct event. 
 *
 * Note from PUG-L2+ Vol. 5:
 *
 *   5.0.2 Unsigned Integer Processing
 * 
 *   The classic model for netCDF (used by the GS) does not support
 *   unsigned integers larger than 8 bits. Many of the variables in
 *   GOES-R netCDF files are unsigned integers of 16-bit or 32-bit
 *   length. The following process is recommended to convert these
 *   unsigned integers:
 *
 *   1. Retrieve the variable data from the netCDF file.
 *
 *   2. For this variable, retrieve the attribute “_Unsigned”.
 *
 *   3. If the “_Unsigned” attribute is set to “true” or “True”, then
 *   cast the variable data to be unsigned.  The steps above must be
 *   completed before applying the scale_factor and add_offset values
 *   to convert from scaled integer to science units. Also, the
 *   valid_range and _FillValue attribute values are to be governed by
 *   the “_Unsigned” attribute.
 *
 * @param ncid ID of already opened GLM file.
 * @param nevents The number of events.
 * @param event Pointer to already-allocated arrat of GLM_EVENT_T.
 *
 * @return 0 for success, error code otherwise.
 * @author Ed Hartnett
*/
static int
read_event_vars(int ncid, int nevents, GLM_EVENT_T *event)
{
    /* Event varids. */
    int event_id_varid;
    int event_time_offset_varid, event_lat_varid, event_lon_varid;
    int event_energy_varid, event_parent_group_id_varid;

    /* Storage for packed data. */
    int *event_id = NULL;
    short *event_lat = NULL;
    short *event_time_offset = NULL, *event_lon = NULL;
    short *event_energy = NULL;
    int *event_parent_group_id = NULL;

    /* Scale factors and offsets. */
    float event_time_offset_scale, event_time_offset_offset;
    float event_lat_scale, event_lat_offset;
    float event_lon_scale, event_lon_offset;
    float event_energy_scale, event_energy_offset;

    int i;
    int ret;

    /* Check inputs. */
    assert(ncid && event && nevents > 0);

    /* Allocate storeage for event variables. */
    if (!(event_id = malloc(nevents * sizeof(int))))
	return GLM_ERR_MEMORY;
    if (!(event_time_offset = malloc(nevents * sizeof(short))))
	return GLM_ERR_TIMER;
    if (!(event_lat = malloc(nevents * sizeof(short))))
	return GLM_ERR_MEMORY;
    if (!(event_lon = malloc(nevents * sizeof(short))))
	return GLM_ERR_MEMORY;
    if (!(event_energy = malloc(nevents * sizeof(short))))
	return GLM_ERR_MEMORY;
    if (!(event_parent_group_id = malloc(nevents * sizeof(int))))
	return GLM_ERR_MEMORY;

    /* Find the varids for the event variables. Also get the scale
     * factors and offsets. */
    if ((ret = nc_inq_varid(ncid, EVENT_ID, &event_id_varid)))
	NC_ERR(ret);
    
    if ((ret = nc_inq_varid(ncid, EVENT_TIME_OFFSET, &event_time_offset_varid)))
	NC_ERR(ret);
    if ((ret = nc_get_att_float(ncid, event_time_offset_varid, SCALE_FACTOR, &event_time_offset_scale)))
	NC_ERR(ret);
    if ((ret = nc_get_att_float(ncid, event_time_offset_varid, ADD_OFFSET, &event_time_offset_offset)))
	NC_ERR(ret);
    
    if ((ret = nc_inq_varid(ncid, EVENT_LAT, &event_lat_varid)))
	NC_ERR(ret);
    if ((ret = nc_get_att_float(ncid, event_lat_varid, SCALE_FACTOR, &event_lat_scale)))
	NC_ERR(ret);
    if ((ret = nc_get_att_float(ncid, event_lat_varid, ADD_OFFSET, &event_lat_offset)))
	NC_ERR(ret);
    
    if ((ret = nc_inq_varid(ncid, EVENT_LON, &event_lon_varid)))
	NC_ERR(ret);
    if ((ret = nc_get_att_float(ncid, event_lon_varid, SCALE_FACTOR, &event_lon_scale)))
	NC_ERR(ret);
    if ((ret = nc_get_att_float(ncid, event_lon_varid, ADD_OFFSET, &event_lon_offset)))
	NC_ERR(ret);
    
    if ((ret = nc_inq_varid(ncid, EVENT_ENERGY, &event_energy_varid)))
	NC_ERR(ret);
    if ((ret = nc_get_att_float(ncid, event_energy_varid, SCALE_FACTOR, &event_energy_scale)))
	NC_ERR(ret);
    if ((ret = nc_get_att_float(ncid, event_energy_varid, ADD_OFFSET, &event_energy_offset)))
	NC_ERR(ret);

    /* event_parent_group_id is not packed. */
    if ((ret = nc_inq_varid(ncid, EVENT_PARENT_GROUP_ID, &event_parent_group_id_varid)))
	NC_ERR(ret);
    
    /* Read the event variables. */
    if ((ret = nc_get_var_int(ncid, event_id_varid, event_id)))
	NC_ERR(ret);
    if ((ret = nc_get_var_short(ncid, event_time_offset_varid, event_time_offset)))
	NC_ERR(ret);
    if ((ret = nc_get_var_short(ncid, event_lat_varid, event_lat)))
	NC_ERR(ret);
    if ((ret = nc_get_var_short(ncid, event_lon_varid, event_lon)))
	NC_ERR(ret);
    if ((ret = nc_get_var_short(ncid, event_energy_varid, event_energy)))
	NC_ERR(ret);
    if ((ret = nc_get_var_int(ncid, event_parent_group_id_varid, event_parent_group_id)))
	NC_ERR(ret);

    /* Unpack the data into our already-allocated array of struct
     * GLM_EVENT. */
    for (i = 0; i < nevents; i++)
    {
	event[i].id = event_id[i];
	event[i].time_offset = (float)((unsigned short)event_time_offset[i]) *
	    (unsigned short)event_time_offset_scale + (unsigned short)event_time_offset_offset;
	event[i].lat = (float)((unsigned short)event_lat[i]) *
	    (unsigned short)event_lat_scale + (unsigned short)event_lat_offset;
	event[i].lon = (float)((unsigned short)event_lon[i]) *
	    (unsigned short)event_lon_scale + (unsigned short)event_lon_offset;
	event[i].energy = (float)((unsigned short)event_energy[i]) *
	    (unsigned short)event_energy_scale + (unsigned short)event_energy_offset;
	event[i].parent_group_id = event_parent_group_id[i];
    }

    /* Free event storage. */
    if (event_id)
	free(event_id);
    if (event_time_offset)
	free(event_time_offset);
    if (event_lat)
	free(event_lat);
    if (event_lon)
	free(event_lon);
    if (event_energy)
	free(event_energy);
    if (event_parent_group_id)
	free(event_parent_group_id);
  
    return 0;
}

/**
 * Read and unpack all the event data in the file. It will be loaded
 * into the pre-allocated array of struct event. 
 *
 * @param ncid ID of already opened GLM file.
 * @param nevents The number of events.
 * @param event Pointer to already-allocated arrat of GLM_EVENT_T.
 *
 * @return 0 for success, error code otherwise.
 * @author Ed Hartnett
*/
int
glm_read_event_vars(int ncid, int nevents, GLM_EVENT_T *event)
{
    int ret;
    
    if ((ret = read_event_vars(ncid, nevents, event)))
	return ret;
    
    return 0;
}

/* Read and unpack all the group data in the file. It will be loaded
 * into the pre-allocated array of struct group. */
int
read_group_vars(int ncid, int ngroups, GLM_GROUP_T *group)
{
    /* Groups. */
    int group_id_varid, group_time_offset_varid;
    int group_frame_time_offset_varid, group_lat_varid, group_lon_varid;
    int group_area_varid, group_energy_varid, group_parent_flash_id_varid;
    int group_quality_flag_varid;
    int *group_id = NULL;
    short *group_time_offset = NULL;
    short *group_frame_time_offset = NULL;
    float *group_lat = NULL, *group_lon = NULL;
    short *group_area = NULL, *group_energy = NULL, *group_parent_flash_id = NULL;
    short *group_quality_flag = NULL;

    /* Scale factors and offsets. */
    float group_time_offset_scale, group_time_offset_offset;
    float group_frame_time_offset_scale, group_frame_time_offset_offset;
    float group_area_scale, group_area_offset;
    float group_energy_scale, group_energy_offset;

    int i;
    int ret;

    /* Allocate storeage for group variables. */
    if (!(group_id = malloc(ngroups * sizeof(int))))
	return GLM_ERR_MEMORY;
    if (!(group_time_offset = malloc(ngroups * sizeof(short))))
	return GLM_ERR_MEMORY;
    if (!(group_frame_time_offset = malloc(ngroups * sizeof(short))))
	return GLM_ERR_MEMORY;
    if (!(group_lat = malloc(ngroups * sizeof(float))))
	return GLM_ERR_MEMORY;
    if (!(group_lon = malloc(ngroups * sizeof(float))))
	return GLM_ERR_MEMORY;
    if (!(group_area = malloc(ngroups * sizeof(short))))
	return GLM_ERR_MEMORY;
    if (!(group_energy = malloc(ngroups * sizeof(short))))
	return GLM_ERR_MEMORY;
    if (!(group_parent_flash_id = malloc(ngroups * sizeof(short))))
	return GLM_ERR_MEMORY;
    if (!(group_quality_flag = malloc(ngroups * sizeof(short))))
	return GLM_ERR_MEMORY;

    /* Find the varids for the group variables. */
    if ((ret = nc_inq_varid(ncid, GROUP_ID, &group_id_varid)))
	NC_ERR(ret);

    if ((ret = nc_inq_varid(ncid, GROUP_TIME_OFFSET, &group_time_offset_varid)))
	NC_ERR(ret);
    if ((ret = nc_get_att_float(ncid, group_time_offset_varid, SCALE_FACTOR, &group_time_offset_scale)))
	NC_ERR(ret);
    if ((ret = nc_get_att_float(ncid, group_time_offset_varid, ADD_OFFSET, &group_time_offset_offset)))
	NC_ERR(ret);

    if ((ret = nc_inq_varid(ncid, GROUP_FRAME_TIME_OFFSET, &group_frame_time_offset_varid)))
	NC_ERR(ret);
    if ((ret = nc_get_att_float(ncid, group_frame_time_offset_varid, SCALE_FACTOR, &group_frame_time_offset_scale)))
	NC_ERR(ret);
    if ((ret = nc_get_att_float(ncid, group_frame_time_offset_varid, ADD_OFFSET, &group_frame_time_offset_offset)))
	NC_ERR(ret);

    /* group_lat is not packed. */
    if ((ret = nc_inq_varid(ncid, GROUP_LAT, &group_lat_varid)))
	NC_ERR(ret);

    /* group_lon is not packed. */
    if ((ret = nc_inq_varid(ncid, GROUP_LON, &group_lon_varid)))
	NC_ERR(ret);

    if ((ret = nc_inq_varid(ncid, GROUP_AREA, &group_area_varid)))
	NC_ERR(ret);
    if ((ret = nc_get_att_float(ncid, group_area_varid, SCALE_FACTOR, &group_area_scale)))
	NC_ERR(ret);
    if ((ret = nc_get_att_float(ncid, group_area_varid, ADD_OFFSET, &group_area_offset)))
	NC_ERR(ret);

    if ((ret = nc_inq_varid(ncid, GROUP_ENERGY, &group_energy_varid)))
	NC_ERR(ret);
    if ((ret = nc_get_att_float(ncid, group_energy_varid, SCALE_FACTOR, &group_energy_scale)))
	NC_ERR(ret);
    if ((ret = nc_get_att_float(ncid, group_energy_varid, ADD_OFFSET, &group_energy_offset)))
	NC_ERR(ret);

    /* group_parent_flash_id is not packed. */
    if ((ret = nc_inq_varid(ncid, GROUP_PARENT_FLASH_ID, &group_parent_flash_id_varid)))
	NC_ERR(ret);

    /* group_quality_flag is not packed. */
    if ((ret = nc_inq_varid(ncid, GROUP_QUALITY_FLAG, &group_quality_flag_varid)))
	NC_ERR(ret);

    /* Read the group variables. */
    if ((ret = nc_get_var_int(ncid, group_id_varid, group_id)))
	NC_ERR(ret);
    if ((ret = nc_get_var_short(ncid, group_time_offset_varid, group_time_offset)))
	NC_ERR(ret);
    if ((ret = nc_get_var_short(ncid, group_frame_time_offset_varid, group_frame_time_offset)))
	NC_ERR(ret);
    if ((ret = nc_get_var_float(ncid, group_lat_varid, group_lat)))
	NC_ERR(ret);
    if ((ret = nc_get_var_float(ncid, group_lon_varid, group_lon)))
	NC_ERR(ret);
    if ((ret = nc_get_var_short(ncid, group_area_varid, group_area)))
    	NC_ERR(ret);
    if ((ret = nc_get_var_short(ncid, group_energy_varid, group_energy)))
    	NC_ERR(ret);
    if ((ret = nc_get_var_short(ncid, group_parent_flash_id_varid, group_parent_flash_id)))
    	NC_ERR(ret);
    if ((ret = nc_get_var_short(ncid, group_quality_flag_varid, group_quality_flag)))
    	NC_ERR(ret);

    /* Unpack the data into our already-allocated array of struct
     * GLM_GROUP. */
    for (i = 0; i < ngroups; i++)
    {
	group[i].id = group_id[i];
	group[i].time_offset = (float)((unsigned short)group_time_offset[i]) *
	    (unsigned short)group_time_offset_scale + (unsigned short)group_time_offset_offset;
	group[i].lat = group_lat[i];
	group[i].lon = group_lon[i];
	group[i].area = (float)((unsigned short)group_area[i]) *
	    (unsigned short)group_area_scale + (unsigned short)group_area_offset;
	group[i].energy = (float)((unsigned short)group_energy[i]) *
	    (unsigned short)group_energy_scale + (unsigned short)group_energy_offset;
	group[i].parent_flash_id = group_parent_flash_id[i];
	group[i].quality_flag = group_quality_flag[i];
    }

    /* Free group storage. */
    if (group_id)
	free(group_id);
    if (group_time_offset)
	free(group_time_offset);
    if (group_frame_time_offset)
	free(group_frame_time_offset);
    if (group_lat)
	free(group_lat);
    if (group_lon)
	free(group_lon);
    if (group_area)
	free(group_area);
    if (group_energy)
	free(group_energy);
    if (group_parent_flash_id)
	free(group_parent_flash_id);
    if (group_quality_flag)
	free(group_quality_flag);

    return 0;
}

/* Read and unpack all the flash data in the file. It will be loaded
 * into the pre-allocated array of struct flash. */
int
read_flash_vars(int ncid, int nflashes, GLM_FLASH_T *flash)
{
    /* Flashes. Note that event_id and group_id are int, but flash_id
     * is short. */
    int flash_id_varid;
    int flash_time_offset_of_first_event_varid;
    int flash_time_offset_of_last_event_varid;
    int flash_frame_time_offset_of_first_event_varid;
    int flash_frame_time_offset_of_last_event_varid;
    int flash_lat_varid, flash_lon_varid;
    int flash_area_varid, flash_energy_varid;
    int flash_quality_flag_varid;
    short *flash_id = NULL;
    short *flash_time_offset_of_first_event = NULL;
    short *flash_time_offset_of_last_event = NULL;
    short *flash_frame_time_offset_of_first_event = NULL;
    short *flash_frame_time_offset_of_last_event = NULL;
    float *flash_lat = NULL, *flash_lon = NULL;
    short *flash_area = NULL, *flash_energy = NULL;
    short *flash_quality_flag = NULL;

    /* Scale factors and offsets. */
    float flash_time_offset_of_first_event_scale, flash_time_offset_of_first_event_offset;
    float flash_time_offset_of_last_event_scale, flash_time_offset_of_last_event_offset;
    float flash_frame_time_offset_of_first_event_scale, flash_frame_time_offset_of_first_event_offset;
    float flash_frame_time_offset_of_last_event_scale, flash_frame_time_offset_of_last_event_offset;
    float flash_area_scale, flash_area_offset;
    float flash_energy_scale, flash_energy_offset;

    int i;
    int ret;

    /* Allocate storeage for flash variables. */
    if (!(flash_id = malloc(nflashes * sizeof(short))))
	return GLM_ERR_MEMORY;
    if (!(flash_time_offset_of_first_event = malloc(nflashes * sizeof(short))))
	return GLM_ERR_MEMORY;
    if (!(flash_time_offset_of_last_event = malloc(nflashes * sizeof(short))))
	return GLM_ERR_MEMORY;
    if (!(flash_frame_time_offset_of_first_event = malloc(nflashes * sizeof(short))))
	return GLM_ERR_MEMORY;
    if (!(flash_frame_time_offset_of_last_event = malloc(nflashes * sizeof(short))))
	return GLM_ERR_MEMORY;
    if (!(flash_lat = malloc(nflashes * sizeof(float))))
	return GLM_ERR_MEMORY;
    if (!(flash_lon = malloc(nflashes * sizeof(float))))
	return GLM_ERR_MEMORY;
    if (!(flash_area = malloc(nflashes * sizeof(short))))
	return GLM_ERR_MEMORY;
    if (!(flash_energy = malloc(nflashes * sizeof(short))))
	return GLM_ERR_MEMORY;
    if (!(flash_quality_flag = malloc(nflashes * sizeof(short))))
	return GLM_ERR_MEMORY;

    /* Find the varids for the flash variables. */
    if ((ret = nc_inq_varid(ncid, FLASH_ID, &flash_id_varid)))
	NC_ERR(ret);

    if ((ret = nc_inq_varid(ncid, FLASH_TIME_OFFSET_OF_FIRST_EVENT, &flash_time_offset_of_first_event_varid)))
	NC_ERR(ret);
    if ((ret = nc_get_att_float(ncid, flash_time_offset_of_first_event_varid, SCALE_FACTOR, &flash_time_offset_of_first_event_scale)))
	NC_ERR(ret);
    if ((ret = nc_get_att_float(ncid, flash_time_offset_of_first_event_varid, ADD_OFFSET, &flash_time_offset_of_first_event_offset)))
	NC_ERR(ret);

    if ((ret = nc_inq_varid(ncid, FLASH_TIME_OFFSET_OF_LAST_EVENT, &flash_time_offset_of_last_event_varid)))
	NC_ERR(ret);
    if ((ret = nc_get_att_float(ncid, flash_time_offset_of_last_event_varid, SCALE_FACTOR, &flash_time_offset_of_last_event_scale)))
	NC_ERR(ret);
    if ((ret = nc_get_att_float(ncid, flash_time_offset_of_last_event_varid, ADD_OFFSET, &flash_time_offset_of_last_event_offset)))
	NC_ERR(ret);

    if ((ret = nc_inq_varid(ncid, FLASH_FRAME_TIME_OFFSET_OF_FIRST_EVENT,
			    &flash_frame_time_offset_of_first_event_varid)))
	NC_ERR(ret);
    if ((ret = nc_get_att_float(ncid, flash_frame_time_offset_of_first_event_varid, SCALE_FACTOR,
				&flash_frame_time_offset_of_first_event_scale)))
	NC_ERR(ret);
    if ((ret = nc_get_att_float(ncid, flash_frame_time_offset_of_first_event_varid, ADD_OFFSET,
				&flash_frame_time_offset_of_first_event_offset)))
	NC_ERR(ret);

    if ((ret = nc_inq_varid(ncid, FLASH_FRAME_TIME_OFFSET_OF_LAST_EVENT,
			    &flash_frame_time_offset_of_last_event_varid)))
	NC_ERR(ret);
    if ((ret = nc_get_att_float(ncid, flash_frame_time_offset_of_last_event_varid, SCALE_FACTOR,
				&flash_frame_time_offset_of_last_event_scale)))
	NC_ERR(ret);
    if ((ret = nc_get_att_float(ncid, flash_frame_time_offset_of_last_event_varid, ADD_OFFSET,
				&flash_frame_time_offset_of_last_event_offset)))
	NC_ERR(ret);

    /* flash_lat is not packed. */
    if ((ret = nc_inq_varid(ncid, FLASH_LAT, &flash_lat_varid)))
	NC_ERR(ret);

    /* flash_lon is not packed. */
    if ((ret = nc_inq_varid(ncid, FLASH_LON, &flash_lon_varid)))
	NC_ERR(ret);

    if ((ret = nc_inq_varid(ncid, FLASH_AREA, &flash_area_varid)))
	NC_ERR(ret);
    if ((ret = nc_get_att_float(ncid, flash_area_varid, SCALE_FACTOR, &flash_area_scale)))
	NC_ERR(ret);
    if ((ret = nc_get_att_float(ncid, flash_area_varid, ADD_OFFSET, &flash_area_offset)))
	NC_ERR(ret);

    if ((ret = nc_inq_varid(ncid, FLASH_ENERGY, &flash_energy_varid)))
	NC_ERR(ret);
    if ((ret = nc_get_att_float(ncid, flash_energy_varid, SCALE_FACTOR, &flash_energy_scale)))
	NC_ERR(ret);
    if ((ret = nc_get_att_float(ncid, flash_energy_varid, ADD_OFFSET, &flash_energy_offset)))
	NC_ERR(ret);


    /* flash_quality_flag is not packed. */
    if ((ret = nc_inq_varid(ncid, FLASH_QUALITY_FLAG, &flash_quality_flag_varid)))
	NC_ERR(ret);

    /* Read the flash variables. */
    if ((ret = nc_get_var_short(ncid, flash_id_varid, flash_id)))
	NC_ERR(ret);
    if ((ret = nc_get_var_short(ncid, flash_time_offset_of_first_event_varid,
				flash_time_offset_of_first_event)))
	NC_ERR(ret);
    if ((ret = nc_get_var_short(ncid, flash_time_offset_of_last_event_varid,
				flash_time_offset_of_last_event)))
	NC_ERR(ret); 
    if ((ret = nc_get_var_short(ncid, flash_frame_time_offset_of_first_event_varid,
				flash_frame_time_offset_of_first_event)))
	NC_ERR(ret);
    if ((ret = nc_get_var_short(ncid, flash_frame_time_offset_of_last_event_varid,
				flash_frame_time_offset_of_last_event)))
	NC_ERR(ret);
    if ((ret = nc_get_var_float(ncid, flash_lat_varid, flash_lat)))
	NC_ERR(ret);
    if ((ret = nc_get_var_float(ncid, flash_lon_varid, flash_lon)))
	NC_ERR(ret);
    if ((ret = nc_get_var_short(ncid, flash_area_varid, flash_area)))
    	NC_ERR(ret);
    if ((ret = nc_get_var_short(ncid, flash_energy_varid, flash_energy)))
    	NC_ERR(ret);
    if ((ret = nc_get_var_short(ncid, flash_quality_flag_varid, flash_quality_flag)))
    	NC_ERR(ret);

    /* Unpack the data into our already-allocated array of struct
     * GLM_FLASH. */
    for (i = 0; i < nflashes; i++)
    {
	flash[i].id = flash_id[i];
	flash[i].time_offset_of_first_event = (float)((unsigned short)flash_time_offset_of_first_event[i]) *
	    (unsigned short)flash_time_offset_of_first_event_scale + (unsigned short)flash_time_offset_of_first_event_offset;
	flash[i].time_offset_of_last_event = (float)((unsigned short)flash_time_offset_of_last_event[i]) *
	    (unsigned short)flash_time_offset_of_last_event_scale + (unsigned short)flash_time_offset_of_last_event_offset;
	flash[i].frame_time_offset_of_first_event = (float)((unsigned short)flash_frame_time_offset_of_first_event[i]) *
	    (unsigned short)flash_frame_time_offset_of_first_event_scale + (unsigned short)flash_frame_time_offset_of_first_event_offset;
	flash[i].frame_time_offset_of_last_event = (float)((unsigned short)flash_frame_time_offset_of_last_event[i]) *
	    (unsigned short)flash_frame_time_offset_of_last_event_scale + (unsigned short)flash_frame_time_offset_of_last_event_offset;
	flash[i].lat = flash_lat[i];
	flash[i].lon = flash_lon[i];
	flash[i].area = (float)((unsigned short)flash_area[i]) * (unsigned short)flash_area_scale +
	    (unsigned short)flash_area_offset;
	flash[i].energy = (float)((unsigned short)flash_energy[i]) * (unsigned short)flash_energy_scale +
	    (unsigned short)flash_energy_offset;
	flash[i].quality_flag = flash_quality_flag[i];
    }

    /* Free flash storage. */
    if (flash_id)
	free(flash_id);
    if (flash_time_offset_of_first_event)
	free(flash_time_offset_of_first_event);
    if (flash_time_offset_of_last_event)
	free(flash_time_offset_of_last_event);
    if (flash_frame_time_offset_of_first_event)
	free(flash_frame_time_offset_of_first_event);
    if (flash_frame_time_offset_of_last_event)
	free(flash_frame_time_offset_of_last_event);
    if (flash_lat)
	free(flash_lat);
    if (flash_lon)
	free(flash_lon);
    if (flash_area)
	free(flash_area);
    if (flash_energy)
	free(flash_energy);
    if (flash_quality_flag)
	free(flash_quality_flag);

    return 0;
}

int
read_dims(int ncid, size_t *nevents, size_t *ngroups, size_t *nflashes)
{
    /* Dimensions and their lengths. */
    int event_dimid, group_dimid, flash_dimid;
    int number_of_time_bounds_dimid;
    int number_of_field_of_view_bounds_dimid;
    int number_of_wavelength_bounds_dimid;
    size_t ntime_bounds, nfov_bounds, nwl_bounds;
    int ret;

    /* Check inputs. */
    assert(ncid > 0 && nevents && ngroups && nflashes);

    if ((ret = nc_inq_dimid(ncid, NUMBER_OF_FLASHES, &flash_dimid)))
	NC_ERR(ret);
    if ((ret = nc_inq_dimlen(ncid, flash_dimid, nflashes)))
	NC_ERR(ret);
    
    if ((ret = nc_inq_dimid(ncid, NUMBER_OF_GROUPS, &group_dimid)))
	NC_ERR(ret);
    if ((ret = nc_inq_dimlen(ncid, group_dimid, ngroups)))
	NC_ERR(ret);

    if ((ret = nc_inq_dimid(ncid, NUMBER_OF_EVENTS, &event_dimid)))
	NC_ERR(ret);
    if ((ret = nc_inq_dimlen(ncid, event_dimid, nevents)))
	NC_ERR(ret);

    /* This dimension will always be length 2. */
    if ((ret = nc_inq_dimid(ncid, NUMBER_OF_TIME_BOUNDS, &number_of_time_bounds_dimid)))
	NC_ERR(ret);
    if ((ret = nc_inq_dimlen(ncid, number_of_time_bounds_dimid, &ntime_bounds)))
	NC_ERR(ret);
    assert(ntime_bounds == EXTRA_DIM_LEN);

    /* This dimension will always be length 2. */
    if ((ret = nc_inq_dimid(ncid, NUMBER_OF_FIELD_OF_VIEW_BOUNDS, &number_of_field_of_view_bounds_dimid)))
	NC_ERR(ret);
    if ((ret = nc_inq_dimlen(ncid, number_of_field_of_view_bounds_dimid, &nfov_bounds)))
	NC_ERR(ret);
    assert(nfov_bounds == EXTRA_DIM_LEN);

    /* This dimension will always be length 2. */
    if ((ret = nc_inq_dimid(ncid, NUMBER_OF_WAVELENGTH_BOUNDS, &number_of_wavelength_bounds_dimid)))
	NC_ERR(ret);
    if ((ret = nc_inq_dimlen(ncid, number_of_wavelength_bounds_dimid, &nwl_bounds)))
	NC_ERR(ret);
    assert(nwl_bounds == EXTRA_DIM_LEN);

    return 0;
}

int
read_scalars(int ncid, GLM_SCALAR_T *glm_scalar)
{
    int product_time_varid;
    int product_time_bounds_varid;
    int lightning_wavelength_varid;
    int lightning_wavelength_bounds_varid;
    int group_time_threshold_varid;
    int flash_time_threshold_varid;
    int lat_field_of_view_varid;
    int lat_field_of_view_bounds_varid;
    int goes_lat_lon_projection_varid;
    int event_count_varid;
    int group_count_varid;
    int flash_count_varid;
    int percent_navigated_L1b_events_varid;
    int yaw_flip_flag_varid;
    int nominal_satellite_subpoint_lat_varid;
    int nominal_satellite_height_varid;
    int nominal_satellite_subpoint_lon_varid;
    int lon_field_of_view_varid;
    int lon_field_of_view_bounds_varid;
    int percent_uncorrectable_L0_errors_varid;
    int algorithm_dynamic_input_data_container_varid;
    int processing_parm_version_container_varid;
    int algorithm_product_version_container_varid;
    int ret;

    /* Get varids and values of scalars and small vars. */
    if ((ret = nc_inq_varid(ncid, PRODUCT_TIME, &product_time_varid)))
	NC_ERR(ret);
    if ((ret = nc_get_var_double(ncid, product_time_varid, &glm_scalar->product_time)))
    	NC_ERR(ret);

    if ((ret = nc_inq_varid(ncid, PRODUCT_TIME_BOUNDS, &product_time_bounds_varid)))
	NC_ERR(ret);
    if ((ret = nc_get_var_double(ncid, product_time_bounds_varid, glm_scalar->product_time_bounds)))
    	NC_ERR(ret);
    
    if ((ret = nc_inq_varid(ncid, LIGHTNING_WAVELENGTH, &lightning_wavelength_varid)))
	NC_ERR(ret);
    if ((ret = nc_get_var_float(ncid, lightning_wavelength_varid, &glm_scalar->lightning_wavelength)))
    	NC_ERR(ret);

    if ((ret = nc_inq_varid(ncid, LIGHTNING_WAVELENGTH_BOUNDS, &lightning_wavelength_bounds_varid)))
	NC_ERR(ret);
    if ((ret = nc_get_var_float(ncid, lightning_wavelength_bounds_varid, glm_scalar->lightning_wavelength_bounds)))
    	NC_ERR(ret);
    
    if ((ret = nc_inq_varid(ncid, GROUP_TIME_THRESHOLD, &group_time_threshold_varid)))
	NC_ERR(ret);
    if ((ret = nc_get_var_float(ncid, group_time_threshold_varid, &glm_scalar->group_time_threshold)))
    	NC_ERR(ret);

    if ((ret = nc_inq_varid(ncid, FLASH_TIME_THRESHOLD, &flash_time_threshold_varid)))
	NC_ERR(ret);
    if ((ret = nc_get_var_float(ncid, flash_time_threshold_varid, &glm_scalar->flash_time_threshold)))
    	NC_ERR(ret);

    if ((ret = nc_inq_varid(ncid, LAT_FIELD_OF_VIEW, &lat_field_of_view_varid)))
	NC_ERR(ret);
    if ((ret = nc_get_var_float(ncid, lat_field_of_view_varid, &glm_scalar->lat_field_of_view)))
    	NC_ERR(ret);

    if ((ret = nc_inq_varid(ncid, LAT_FIELD_OF_VIEW_BOUNDS, &lat_field_of_view_bounds_varid)))
	NC_ERR(ret);
    if ((ret = nc_get_var_float(ncid, lat_field_of_view_bounds_varid, glm_scalar->lat_field_of_view_bounds)))
    	NC_ERR(ret);

    if ((ret = nc_inq_varid(ncid, GOES_LAT_LON_PROJECTION, &goes_lat_lon_projection_varid)))
	NC_ERR(ret);
    if ((ret = nc_get_var_int(ncid, goes_lat_lon_projection_varid, &glm_scalar->goes_lat_lon_projection)))
    	NC_ERR(ret);

    if ((ret = nc_inq_varid(ncid, EVENT_COUNT, &event_count_varid)))
	NC_ERR(ret);
    if ((ret = nc_get_var_int(ncid, event_count_varid, &glm_scalar->event_count)))
    	NC_ERR(ret);

    if ((ret = nc_inq_varid(ncid, GROUP_COUNT, &group_count_varid)))
	NC_ERR(ret);
    if ((ret = nc_get_var_int(ncid, group_count_varid, &glm_scalar->group_count)))
    	NC_ERR(ret);

    if ((ret = nc_inq_varid(ncid, FLASH_COUNT, &flash_count_varid)))
	NC_ERR(ret);
    if ((ret = nc_get_var_int(ncid, flash_count_varid, &glm_scalar->flash_count)))
    	NC_ERR(ret);

    if ((ret = nc_inq_varid(ncid, PERCENT_NAVIGATED_L1B_EVENTS, &percent_navigated_L1b_events_varid)))
	NC_ERR(ret);
    if ((ret = nc_get_var_float(ncid, percent_navigated_L1b_events_varid, &glm_scalar->percent_navigated_L1b_events)))
    	NC_ERR(ret);

    if ((ret = nc_inq_varid(ncid, YAW_FLIP_FLAG, &yaw_flip_flag_varid)))
	NC_ERR(ret);
    if ((ret = nc_get_var_schar(ncid, yaw_flip_flag_varid, &glm_scalar->yaw_flip_flag)))
    	NC_ERR(ret);

    if ((ret = nc_inq_varid(ncid, NOMINAL_SATELLITE_SUBPOINT_LAT, &nominal_satellite_subpoint_lat_varid)))
	NC_ERR(ret);
    if ((ret = nc_get_var_float(ncid, nominal_satellite_subpoint_lat_varid, &glm_scalar->nominal_satellite_subpoint_lat)))
    	NC_ERR(ret);

    if ((ret = nc_inq_varid(ncid, NOMINAL_SATELLITE_HEIGHT, &nominal_satellite_height_varid)))
	NC_ERR(ret);
    if ((ret = nc_get_var_float(ncid, nominal_satellite_height_varid, &glm_scalar->nominal_satellite_height)))
    	NC_ERR(ret);

    if ((ret = nc_inq_varid(ncid, NOMINAL_SATELLITE_SUBPOINT_LON, &nominal_satellite_subpoint_lon_varid)))
	NC_ERR(ret);
    if ((ret = nc_get_var_float(ncid, nominal_satellite_subpoint_lon_varid, &glm_scalar->nominal_satellite_subpoint_lon)))
    	NC_ERR(ret);

    if ((ret = nc_inq_varid(ncid, LON_FIELD_OF_VIEW, &lon_field_of_view_varid)))
	NC_ERR(ret);
    if ((ret = nc_get_var_float(ncid, lon_field_of_view_varid, &glm_scalar->lon_field_of_view)))
    	NC_ERR(ret);

    if ((ret = nc_inq_varid(ncid, LON_FIELD_OF_VIEW_BOUNDS, &lon_field_of_view_bounds_varid)))
	NC_ERR(ret);
    if ((ret = nc_get_var_float(ncid, lon_field_of_view_bounds_varid, glm_scalar->lon_field_of_view_bounds)))
    	NC_ERR(ret);

    if ((ret = nc_inq_varid(ncid, PERCENT_UNCORRECTABLE_L0_ERRORS,
			    &percent_uncorrectable_L0_errors_varid)))
	NC_ERR(ret);
    if ((ret = nc_get_var_float(ncid, percent_uncorrectable_L0_errors_varid,
				&glm_scalar->percent_uncorrectable_L0_errors)))
    	NC_ERR(ret);

    if ((ret = nc_inq_varid(ncid, ALGORITHM_DYNAMIC_INPUT_DATA_CONTAINER,
			    &algorithm_dynamic_input_data_container_varid)))
	NC_ERR(ret);
    if ((ret = nc_get_var_int(ncid, algorithm_dynamic_input_data_container_varid,
			      &glm_scalar->algorithm_dynamic_input_data_container)))
    	NC_ERR(ret);

    if ((ret = nc_inq_varid(ncid, PROCESSING_PARM_VERSION_CONTAINER,
			    &processing_parm_version_container_varid)))
	NC_ERR(ret);
    if ((ret = nc_get_var_int(ncid, processing_parm_version_container_varid,
			      &glm_scalar->processing_parm_version_container)))
    	NC_ERR(ret);

    if ((ret = nc_inq_varid(ncid, PROCESSING_PARM_VERSION_CONTAINER,
			    &processing_parm_version_container_varid)))
	NC_ERR(ret);
    if ((ret = nc_get_var_int(ncid, processing_parm_version_container_varid,
			      &glm_scalar->processing_parm_version_container)))
    	NC_ERR(ret);

    if ((ret = nc_inq_varid(ncid, ALGORITHM_PRODUCT_VERSION_CONTAINER,
			    &algorithm_product_version_container_varid)))
	NC_ERR(ret);
    if ((ret = nc_get_var_int(ncid, algorithm_product_version_container_varid,
			      &glm_scalar->algorithm_product_version_container)))
    	NC_ERR(ret);

    return 0;
}

/*
  From GOES R SERIESPRODUCT DEFINITION AND USERS’ GUIDE(PUG) Vol 3
  (https://www.goes-r.gov/users/docs/PUG-L1b-vol3.pdf)

  The classic model for netCDF (used by the GS) does not support
  unsigned integers larger than 8 bits.  Many of the variables in
  GOES-R netCDF files are unsigned integers of 16-bit or 32-bit
  length.  The following process is recommended to convert these
  unsigned integers:

  1.Retrieve the variable data from the netCDF file.

  2.For this variable, retrieve the attribute “_Unsigned”.

  3.If the “_Unsigned” attribute is set to “true” or “True”, then
  cast the variable data to be unsigned.

  The steps above must be completed before applying the
  scale_factor and add_offset values to convert from scaled
  integer to science units.  Also, the valid_range and _FillValue
  attribute values are to be governed by the “_Unsigned” attribute

  From a netCDF group email:
  https://www.unidata.ucar.edu/mailing_lists/archives/netcdfgroup/2002/msg00034.html

  Normally you store a group of numbers, all with the same scale
  and offset. So first you calculate the min and max of that group
  of numbers. Also let max_integer = maximum integer (eg for
  INTEGER*2 this equals 32,167).

  then
  offset = min
  scale = max_integer / (max - min)

  store this number into netcdf file:

  store_x = (x - offset) * scale = max_integer * (x - min) / (max - min)

  note that when x = min, store_x = 0, and when x = max, store_x
  max_integer.

  the reading program should use the formula

  x = store_x/scale + offset.

*/
int
glm_read_file(char *file_name, int verbose)
{
    int ncid;

    size_t nevents, ngroups, nflashes;

    /* Structs of events, groups, flashes. */
    GLM_EVENT_T *event;
    GLM_GROUP_T *group;
    GLM_FLASH_T *flash;
    GLM_SCALAR_T glm_scalar;

    int ret;
    
    /* Open the data file as read-only. */
    if ((ret = nc_open(file_name, NC_NOWRITE, &ncid)))
	NC_ERR(ret);

    /* Optionally display some of the global attributes. The GLM data
     * files comply with the CF Conventions, and other metadata
     * standards. */
    if (verbose)
    {
	if (show_att(ncid, NC_GLOBAL, TITLE))
	    return GLM_ERR_MEMORY;
	if (show_att(ncid, NC_GLOBAL, PLATFORM_ID))
	    return GLM_ERR_MEMORY;
	if (show_att(ncid, NC_GLOBAL, SUMMARY))
	    return GLM_ERR_MEMORY;
    }

    /* Read the size of the dimensions. */
    if ((ret = read_dims(ncid, &nevents, &ngroups, &nflashes)))
	return GLM_ERR_MEMORY;
    
    if (verbose)
	printf("nflashes %zu ngroups %zu nevents %zu\n", nflashes,
	       ngroups, nevents);

    /* Allocate storage. */
    if (!(event = malloc(nevents * sizeof(GLM_EVENT_T))))
	return GLM_ERR_MEMORY;
    if (!(group = malloc(ngroups * sizeof(GLM_GROUP_T))))
	return GLM_ERR_MEMORY;
    if (!(flash = malloc(nflashes * sizeof(GLM_FLASH_T))))
	return GLM_ERR_MEMORY;

    /* Read the vars. */
    if ((ret = read_event_vars(ncid, nevents, event)))
	return GLM_ERR_MEMORY;
    if ((ret = read_group_vars(ncid, ngroups, group)))
	return GLM_ERR_MEMORY;
    if ((ret = read_flash_vars(ncid, nflashes, flash)))
	return GLM_ERR_MEMORY;
    if ((ret = read_scalars(ncid, &glm_scalar)))
	return GLM_ERR_MEMORY;

    /* Close the data file. */
    if ((ret = nc_close(ncid)))
	NC_ERR(ret);

    /* Free memory. */
    free(event);
    free(group);
    free(flash);
    
    return 0;
}

/**
 * Read the contents of the GLM file into arrays of data.
 * 
 * @param file_name GLM file to open and read.
 * @param verbose Non-zero to get some printf output as file is read.
 *
 * @return 0 for success, error code otherwise.
 * @author Ed Hartnett
 */
int
glm_read_file_arrays(char *file_name, int verbose)
{
    int ncid;

    size_t nevents, ngroups, nflashes;

    /* Structs of events, groups, flashes. */
    GLM_EVENT_T *event;
    GLM_GROUP_T *group;
    GLM_FLASH_T *flash;
    GLM_SCALAR_T glm_scalar;

    int ret;
    
    /* Open the data file as read-only. */
    if ((ret = nc_open(file_name, NC_NOWRITE, &ncid)))
	NC_ERR(ret);

    /* Optionally display some of the global attributes. The GLM data
     * files comply with the CF Conventions, and other metadata
     * standards. */
    if (verbose)
    {
	if (show_att(ncid, NC_GLOBAL, TITLE))
	    return GLM_ERR_MEMORY;
	if (show_att(ncid, NC_GLOBAL, PLATFORM_ID))
	    return GLM_ERR_MEMORY;
	if (show_att(ncid, NC_GLOBAL, SUMMARY))
	    return GLM_ERR_MEMORY;
    }

    /* Read the size of the dimensions. */
    if ((ret = read_dims(ncid, &nevents, &ngroups, &nflashes)))
	return GLM_ERR_MEMORY;
    
    if (verbose)
	printf("nflashes %zu ngroups %zu nevents %zu\n", nflashes,
	       ngroups, nevents);

    /* Allocate storage. */
    if (!(event = malloc(nevents * sizeof(GLM_EVENT_T))))
	return GLM_ERR_MEMORY;
    if (!(group = malloc(ngroups * sizeof(GLM_GROUP_T))))
	return GLM_ERR_MEMORY;
    if (!(flash = malloc(nflashes * sizeof(GLM_FLASH_T))))
	return GLM_ERR_MEMORY;

    /* Read the vars. */
    if ((ret = read_event_vars(ncid, nevents, event)))
	return GLM_ERR_MEMORY;
    if ((ret = read_group_vars(ncid, ngroups, group)))
	return GLM_ERR_MEMORY;
    if ((ret = read_flash_vars(ncid, nflashes, flash)))
	return GLM_ERR_MEMORY;
    if ((ret = read_scalars(ncid, &glm_scalar)))
	return GLM_ERR_MEMORY;

    /* Close the data file. */
    if ((ret = nc_close(ncid)))
	NC_ERR(ret);

    /* Free memory. */
    free(event);
    free(group);
    free(flash);
    
    return 0;
}
