/**
 * @file
 * Code to read group data from the GOES-17 Global Lightning Mapper.
 *
 * @author Ed Hartnett, 11/16/19
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ncglm.h"

/**
 * This internal function will read and unpack all the group data in
 * the file. It will be loaded into either pre-allocated array of struct
 * group, or arrays of pre-allocated storage for each group var.
 *
 * @param ncid ID of already opened GLM file.
 * @param ngroup A pointer that gets the number of groups. Ignored if
 * NULL.
 * @param group Pointer to already-allocated arrat of GLM_GROUP_T, or
 * NULL if arrays are being read.
 * @param time_offset Pointer to already-allocated array of unsigned
 * int for time_offset data, or NULL if struct reads are being done.
 * @param lat Pointer to already-allocated array of float for lat
 * data, or NULL if struct reads are being done.
 * @param lon Pointer to already-allocated array of float for lon
 * data, or NULL if struct reads are being done.
 * @param energy Pointer to already-allocated array of float for
 * energy data, or NULL if struct reads are being done.
 * @param area Pointer to already-allocated array of float for
 * area data, or NULL if struct reads are being done.
 * @param parent_flash_id Pointer to already-allocated array of int
 * for parent_flash_id data, or NULL if struct reads are being done.
 * @param quality_flag Pointer to already-allocated array of short
 * for quality flag data, or NULL if struct reads are being done.
 *
 * @return 0 for success, error code otherwise.
 * @author Ed Hartnett
*/
static int
read_group_vars(int ncid, size_t *ngroup, GLM_GROUP_T *group,
                float *time_offset, float *lat, float *lon,
                float *energy, float *area, unsigned int *parent_flash_id,
                short *quality_flag)
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
    size_t my_ngroup;

    /* Scale factors and offsets. */
    float group_time_offset_scale, group_time_offset_offset;
    float group_frame_time_offset_scale, group_frame_time_offset_offset;
    float group_area_scale, group_area_offset;
    float group_energy_scale, group_energy_offset;

    int i;
    int ret;

    /* How many groups to read? */
    if ((ret = glm_read_dims(ncid, NULL, &my_ngroup, NULL)))
        return ret;

    /* Return the number of groups to user if desired. */
    if (ngroup)
        *ngroup = my_ngroup;

    /* Allocate storeage for group variables. */
    if (!(group_id = malloc(my_ngroup * sizeof(int))))
	return GLM_ERR_MEMORY;
    if (!(group_time_offset = malloc(my_ngroup * sizeof(short))))
	return GLM_ERR_MEMORY;
    if (!(group_frame_time_offset = malloc(my_ngroup * sizeof(short))))
	return GLM_ERR_MEMORY;
    if (!(group_lat = malloc(my_ngroup * sizeof(float))))
	return GLM_ERR_MEMORY;
    if (!(group_lon = malloc(my_ngroup * sizeof(float))))
	return GLM_ERR_MEMORY;
    if (!(group_area = malloc(my_ngroup * sizeof(short))))
	return GLM_ERR_MEMORY;
    if (!(group_energy = malloc(my_ngroup * sizeof(short))))
	return GLM_ERR_MEMORY;
    if (!(group_parent_flash_id = malloc(my_ngroup * sizeof(short))))
	return GLM_ERR_MEMORY;
    if (!(group_quality_flag = malloc(my_ngroup * sizeof(short))))
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
    for (i = 0; i < my_ngroup; i++)
    {
	group[i].id = group_id[i];
	group[i].time_offset = (float)((unsigned short)group_time_offset[i] + 65536) *
	    group_time_offset_scale + group_time_offset_offset;
	group[i].lat = group_lat[i];
	group[i].lon = group_lon[i];
	group[i].area = (float)((unsigned short)group_area[i]) *
	    group_area_scale + group_area_offset;
	group[i].energy = (float)((unsigned short)group_energy[i]) *
	    group_energy_scale + group_energy_offset;
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

/**
 * Read and unpack all the group data in the file. It will be loaded
 * into the pre-allocated array of struct group.
 *
 * @param ncid ID of already opened GLM file.
 * @param ngroup A pointer that gets the number of groups. Ignored if
 * NULL.
 * @param group Pointer to already-allocated arrat of GLM_GROUP_T.
 *
 * @return 0 for success, error code otherwise.
 * @author Ed Hartnett
*/
int
glm_read_group_structs(int ncid, size_t *ngroup, GLM_GROUP_T *group)
{
    int ret;

    if ((ret = read_group_vars(ncid, ngroup, group, NULL, NULL,
                               NULL, NULL, NULL, NULL, NULL)))
	return ret;

    return 0;
}

/**
 * Read and unpack all the group data in the file. It will be loaded
 * into the pre-allocated arrays for each element of the group data.
 *
 * @param ncid ID of already opened GLM file.
 * @param ngroup A pointer that gets the number of groups. Ignored if
 * NULL.
 * @param time_offset Pointer to already-allocated array of unsigned
 * int for time_offset data, or NULL if struct reads are being done.
 * @param lat Pointer to already-allocated array of float for lat
 * data, or NULL if struct reads are being done.
 * @param lon Pointer to already-allocated array of float for lon
 * data, or NULL if struct reads are being done.
 * @param energy Pointer to already-allocated array of float for
 * energy data, or NULL if struct reads are being done.
 * @param area Pointer to already-allocated array of float for
 * area data, or NULL if struct reads are being done.
 * @param parent_flash_id Pointer to already-allocated array of int
 * for parent_flash_id data, or NULL if struct reads are being done.
 * @param quality_flag Pointer to already-allocated array of short
 * for quality flag data, or NULL if struct reads are being done.
 *
 * @return 0 for success, error code otherwise.
 * @author Ed Hartnett
*/
int
glm_read_group_arrays(int ncid, size_t *ngroup, float *time_offset,
                      float *lat, float *lon, float *energy, float *area,
                      unsigned int *parent_flash_id, short *quality_flag)
{
    int ret;

    if ((ret = read_group_vars(ncid, ngroup, NULL, time_offset, lat,
                               lon, energy, area, parent_flash_id, quality_flag)))
	return ret;

    return 0;
}
