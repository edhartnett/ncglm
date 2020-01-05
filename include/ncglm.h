/* Header file for data from the Geostationary Lightning Mapper.
 *
 * Ed Hartnett
 * 10/27/19
 * Amsterdam
 */
#ifndef _GOES_GLM_H
#define _GOES_GLM_H

#include <netcdf.h>
#include "glm_data.h"

#define GLM_ERR_TIMER 99
#define GLM_ERR_MEMORY 100
#define GLM_ERR_UNEXPECTED 101

/* This macro prints an error message with line number and name of
 * test program, and the netCDF error string. */
#define NC_ERR(stat) do {						\
        fflush(stdout); /* Make sure our stdout is synced with stderr. */ \
        fprintf(stderr, "Sorry! Unexpected result, %s, line: %d %s\n",	\
                __FILE__, __LINE__, nc_strerror(stat));			\
        fflush(stderr);							\
        return 2;							\
    } while (0)

#if defined(__cplusplus)
extern "C" {
#endif

    /* Learn the lengths of each dimension. */
    int glm_read_dims(int ncid, size_t *nevent, size_t *ngroup, size_t *nflash);

    /* Read event data into array of GLM_EVENT_T struct. */
    int glm_read_event_structs(int ncid, size_t *nevent, GLM_EVENT_T *event);

    /* Read group data into array of GLM_GROUP_T struct. */
    int glm_read_group_structs(int ncid, size_t *ngroups, GLM_GROUP_T *group);

    /* Read flash data into array of GLM_FLASH_T struct. */
    int glm_read_flash_structs(int ncid, size_t *nflashes, GLM_FLASH_T *flash);

    /* Read event data into arrays. */
    int glm_read_event_arrays(int ncid, size_t *nevent, int *event_id,
                              float *time_offset, float *lat, float *lon,
                              float *energy, int *parent_group_id);

    /* Read group data into arrays. */
    int glm_read_group_arrays(int ncid, size_t *ngroups, float *time_offset,
                              float *lat, float *lon, float *energy, float *area,
                              unsigned int *parent_flash_id, short *quality_flag);

    /* Read flash data into arrays. */
    int glm_read_flash_arrays(int ncid, size_t *nflash,
                              float *time_offset_of_first_event,
                              float *time_offset_of_last_event,
                              float *frame_time_offset_of_first_event,
                              float *frame_time_offset_of_last_event,
                              float *lat, float *lon, float *area, float *energy,
                              short *quality_flag);

    /* Read scalars and small arrays into GLM_SCALAR_T struct. */
    int read_scalars(int ncid, GLM_SCALAR_T *glm_scalar);

    /* Read the whole file. */
    int glm_read_file(char *file_name, int verbose);

    /* Read the whole file into arrays. */
    int glm_read_file_arrays(char *file_name, int verbose);

#if defined(__cplusplus)
}
#endif

#endif /* _GOES_GLM_H */
