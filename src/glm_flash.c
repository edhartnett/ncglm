/**
 * @file
 * Code to flash group data from the GOES-17 Global Lightning Mapper.
 *
 * @author Ed Hartnett, 11/16/19
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ncglm.h"

/**
 * Read and unpack all the flash data in the file. It will be loaded
 * into the pre-allocated array of struct flash.
 *
 * @param ncid ID of already opened GLM file.
 * @param nflash A pointer that gets the number of flashes. Ignored if
 * NULL.
 * @param flash Pointer to already-allocated arrat of GLM_FLASH_T, or
 * NULL if arrays are to be read.
 * @param time_offset_of_first_event Pointer to already-allocated
 * array of unsigned int for time_offset_of_first_event data, or NULL
 * if struct reads are being done.
 * @param time_offset_of_last_event Pointer to already-allocated
 * array of unsigned int for time_offset_of_last_event data, or NULL
 * if struct reads are being done.
 * @param frame_time_offset_of_first_event Pointer to
 * already-allocated array of unsigned int for
 * frame_time_offset_of_first_event data, or NULL if struct reads are
 * being done.
 * @param frame_time_offset_of_last_event Pointer to already-allocated
 * array of unsigned int for frame_time_offset_of_last_event data, or
 * NULL if struct reads are being done.
 * @param lat Pointer to already-allocated array of float for lat
 * data, or NULL if struct reads are being done.
 * @param lon Pointer to already-allocated array of float for lon
 * data, or NULL if struct reads are being done.
 * @param area Pointer to already-allocated array of float for
 * area data, or NULL if struct reads are being done.
 * @param energy Pointer to already-allocated array of float for
 * energy data, or NULL if struct reads are being done.
 * @param quality_flag Pointer to already-allocated array of short
 * for quality flag data, or NULL if struct reads are being done.
 *
 *
 * @return 0 for success, error code otherwise.
 * @author Ed Hartnett
 */
static int
read_flash_vars(int ncid, size_t *nflash, GLM_FLASH_T *flash,
                unsigned int *time_offset_of_first_event,
                unsigned int *time_offset_of_last_event,
                unsigned int *frame_time_offset_of_first_event,
                unsigned int *frame_time_offset_of_last_event,
                float *lat, float *lon, float *area, float *energy,
                short *quality_flag)
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
    size_t my_nflash;

    /* Scale factors and offsets. */
    float flash_time_offset_of_first_event_scale, flash_time_offset_of_first_event_offset;
    float flash_time_offset_of_last_event_scale, flash_time_offset_of_last_event_offset;
    float flash_frame_time_offset_of_first_event_scale, flash_frame_time_offset_of_first_event_offset;
    float flash_frame_time_offset_of_last_event_scale, flash_frame_time_offset_of_last_event_offset;
    float flash_area_scale, flash_area_offset;
    float flash_energy_scale, flash_energy_offset;

    int i;
    int ret;

    /* How many flashes to read? */
    if ((ret = glm_read_dims(ncid, NULL, NULL, &my_nflash)))
        return ret;

    /* Return the number of flashes to user if desired. */
    if (nflash)
        *nflash = my_nflash;

    /* Allocate storeage for flash variables. */
    if (!(flash_id = malloc(my_nflash * sizeof(short))))
	return GLM_ERR_MEMORY;
    if (!(flash_time_offset_of_first_event = malloc(my_nflash * sizeof(short))))
	return GLM_ERR_MEMORY;
    if (!(flash_time_offset_of_last_event = malloc(my_nflash * sizeof(short))))
	return GLM_ERR_MEMORY;
    if (!(flash_frame_time_offset_of_first_event = malloc(my_nflash * sizeof(short))))
	return GLM_ERR_MEMORY;
    if (!(flash_frame_time_offset_of_last_event = malloc(my_nflash * sizeof(short))))
	return GLM_ERR_MEMORY;
    if (!(flash_lat = malloc(my_nflash * sizeof(float))))
	return GLM_ERR_MEMORY;
    if (!(flash_lon = malloc(my_nflash * sizeof(float))))
	return GLM_ERR_MEMORY;
    if (!(flash_area = malloc(my_nflash * sizeof(short))))
	return GLM_ERR_MEMORY;
    if (!(flash_energy = malloc(my_nflash * sizeof(short))))
	return GLM_ERR_MEMORY;
    if (!(flash_quality_flag = malloc(my_nflash * sizeof(short))))
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
    for (i = 0; i < my_nflash; i++)
    {
	flash[i].id = flash_id[i];
	flash[i].time_offset_of_first_event = (float)((unsigned short)flash_time_offset_of_first_event[i]) *
	    flash_time_offset_of_first_event_scale + flash_time_offset_of_first_event_offset;
	flash[i].time_offset_of_last_event = (float)((unsigned short)flash_time_offset_of_last_event[i]) *
	    flash_time_offset_of_last_event_scale + flash_time_offset_of_last_event_offset;
	flash[i].frame_time_offset_of_first_event = (float)((unsigned short)flash_frame_time_offset_of_first_event[i]) *
	    flash_frame_time_offset_of_first_event_scale + flash_frame_time_offset_of_first_event_offset;
	flash[i].frame_time_offset_of_last_event = (float)((unsigned short)flash_frame_time_offset_of_last_event[i]) *
	    flash_frame_time_offset_of_last_event_scale + flash_frame_time_offset_of_last_event_offset;
	flash[i].lat = flash_lat[i];
	flash[i].lon = flash_lon[i];
	flash[i].area = (float)((unsigned short)flash_area[i]) * flash_area_scale +
	    flash_area_offset;
	flash[i].energy = (float)((unsigned short)flash_energy[i]) * flash_energy_scale +
            flash_energy_offset;
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

/**
 * Read and unpack all the flash data in the file. It will be loaded
 * into the pre-allocated array of struct GLM_FLASH_T.
 *
 * @param ncid ID of already opened GLM file.
 * @param nflash A pointer that gets the number of flashes. Ignored if
 * NULL.
 * @param flash Pointer to already-allocated arrat of GLM_FLASH_T.
 *
 * @return 0 for success, error code otherwise.
 * @author Ed Hartnett
*/
int
glm_read_flash_structs(int ncid, size_t *nflash, GLM_FLASH_T *flash)
{
    int ret;

    if ((ret = read_flash_vars(ncid, nflash, flash, NULL, NULL,
                               NULL, NULL, NULL, NULL, NULL, NULL, NULL)))
	return ret;

    return 0;
}

/**
 * Read and unpack all the flash data in the file. It will be loaded
 * into the pre-allocated array of struct GLM_FLASH_T.
 *
 * @param ncid ID of already opened GLM file.
 * @param nflash A pointer that gets the number of flashes. Ignored if
 * NULL.
 *
 * @return 0 for success, error code otherwise.
 * @author Ed Hartnett
*/
int
glm_read_flash_arrays(int ncid, size_t *nflash,
                      unsigned int *time_offset_of_first_event,
                      unsigned int *time_offset_of_last_event,
                      unsigned int *frame_time_offset_of_first_event,
                      unsigned int *frame_time_offset_of_last_event,
                      float *lat, float *lon, float *area, float *energy,
                      short *quality_flag)
{
    int ret;

    if ((ret = read_flash_vars(ncid, nflash, NULL, time_offset_of_first_event,
                               time_offset_of_last_event, frame_time_offset_of_first_event,
                               frame_time_offset_of_last_event, lat, lon, area,
                               energy, quality_flag)))
	return ret;

    return 0;
}
