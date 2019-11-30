/**
 * @file
 * Code to read event data from the GOES-17 Global Lightning Mapper.
 *
 * @author Ed Hartnett, 11/16/19
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ncglm.h"

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
 * @param nevent A pointer that gets the number of events
 * read. Ignored if NULL.
 * @param event Pointer to already-allocated arrat of GLM_EVENT_T, or
 * NULL if array reads are being done.
 * @param event_id Pointer to already-allocated array of int for
 * event_id data, or NULL if struct reads are being done.
 * @param time_offset Pointer to already-allocated array of unsigned
 * int for time_offset data, or NULL if struct reads are being done.
 * @param lat Pointer to already-allocated array of float for lat
 * data, or NULL if struct reads are being done.
 * @param lon Pointer to already-allocated array of float for lon
 * data, or NULL if struct reads are being done.
 * @param energy Pointer to already-allocated array of float for
 * energy data, or NULL if struct reads are being done.
 * @param parent_group_id Pointer to already-allocated array of int
 * for parent_group_id data, or NULL if struct reads are being done.
 *
 * @return 0 for success, error code otherwise.
 * @author Ed Hartnett
*/
static int
read_event_vars(int ncid, size_t *nevent, GLM_EVENT_T *event, int *event_id,
                float *time_offset, float *lat, float *lon, float *energy,
                int *parent_group_id)
{
    size_t my_nevent;

    /* Event varids. */
    int event_id_varid;
    int event_time_offset_varid, event_lat_varid, event_lon_varid;
    int event_energy_varid, event_parent_group_id_varid;

    /* Storage for packed data. */
    int *my_event_id = NULL;
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
    assert(ncid && (event || event_id));

    /* How many events to read? */
    if ((ret = glm_read_dims(ncid, &my_nevent, NULL, NULL)))
        return ret;

    /* Return the number of events to user if desired. */
    if (nevent)
        *nevent = my_nevent;

    /* Allocate storeage for event variables. */
    if (!(my_event_id = malloc(my_nevent * sizeof(int))))
	return GLM_ERR_MEMORY;
    if (!(event_time_offset = malloc(my_nevent * sizeof(short))))
	return GLM_ERR_TIMER;
    if (!(event_lat = malloc(my_nevent * sizeof(short))))
	return GLM_ERR_MEMORY;
    if (!(event_lon = malloc(my_nevent * sizeof(short))))
	return GLM_ERR_MEMORY;
    if (!(event_energy = malloc(my_nevent * sizeof(short))))
	return GLM_ERR_MEMORY;
    if (!(event_parent_group_id = malloc(my_nevent * sizeof(int))))
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
    if ((ret = nc_get_var_int(ncid, event_id_varid, my_event_id)))
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
    for (i = 0; i < my_nevent; i++)
    {
        float my_time_offset;
        float my_lat;
        float my_lon;
        float my_energy;

        /* Unpack some values. */
        my_time_offset = (float)((unsigned short)event_time_offset[i] + 65536) *
            event_time_offset_scale + event_time_offset_offset;
        my_lat = (float)((unsigned short)event_lat[i]) * event_lat_scale +
            event_lat_offset;
        my_lon = (float)((unsigned short)event_lon[i]) * event_lon_scale +
            event_lon_offset;
        my_energy = (float)((unsigned short)event_energy[i]) *
            event_energy_scale + event_energy_offset;

        if (event) /* fill structs */
        {
            event[i].id = my_event_id[i];
            event[i].time_offset = my_time_offset;
            event[i].lat = my_lat;
            event[i].lon = my_lon;
            event[i].energy = my_energy;
            event[i].parent_group_id = event_parent_group_id[i];
        }
        else /* fill arrays */
        {
            event_id[i] = my_event_id[i];
            time_offset[i] = my_time_offset;
            lat[i] = my_lat;
            lon[i] = my_lon;
            energy[i] = my_energy;
            parent_group_id[i] = event_parent_group_id[i];
        }
    }

    /* Free event storage. */
    if (my_event_id)
	free(my_event_id);
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
 * @param nevent Pointer that gets the number of events. Ignored if
 * NULL.
 * @param event Pointer to already-allocated arrat of GLM_EVENT_T.
 *
 * @return 0 for success, error code otherwise.
 * @author Ed Hartnett
*/
int
glm_read_event_structs(int ncid, size_t *nevent, GLM_EVENT_T *event)
{
    int ret;

    if ((ret = read_event_vars(ncid, nevent, event, NULL, NULL,
                               NULL, NULL, NULL, NULL)))
	return ret;

    return 0;
}

/**
 * Read and unpack all the event data in the file. It will be loaded
 * into the pre-allocated array of struct event.
 *
 * @param ncid ID of already opened GLM file.
 * @param nevent Pointer that gets the number of events. Ignored if
 * NULL.
 * @param event_id Pointer to already-allocated arrat of int for
 * event_id values.
 * @param time_offset Pointer to already-allocated array of unsigned
 * int for time_offset data, or NULL if struct reads are being done.
 * @param lat Pointer to already-allocated array of float for lat
 * data, or NULL if struct reads are being done.
 * @param lon Pointer to already-allocated array of float for lon
 * data, or NULL if struct reads are being done.
 * @param energy Pointer to already-allocated array of float for
 * energy data, or NULL if struct reads are being done.
 * @param parent_group_id Pointer to already-allocated array of int
 * for parent_group_id data, or NULL if struct reads are being done.
 *
 * @return 0 for success, error code otherwise.
 * @author Ed Hartnett
*/
int
glm_read_event_arrays(int ncid, size_t *nevent, int *event_id,
                      float *time_offset, float *lat, float *lon,
                      float *energy, int *parent_group_id)
{
    int ret;

    if ((ret = read_event_vars(ncid, nevent, NULL, event_id, time_offset,
                               lat, lon, energy, parent_group_id)))
	return ret;

    return 0;
}
