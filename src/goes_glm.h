/* Header file for data from the Geostationary Lightning Mapper.
 *
 * Ed Hartnett
 * 10/27/19
 * Amsterdam
 */
#ifndef _GOES_GLM_H
#define _GOES_GLM_H

#include "glm_data.h"

#define GLM_ERR_TIMER 99
#define GLM_ERR_MEMORY 100

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

    int show_att(int ncid, int varid, char *name);
    int glm_read_event_vars(int ncid, int nevents, GLM_EVENT_T *event);
    int read_group_vars(int ncid, int ngroups, GLM_GROUP_T *group);
    int read_flash_vars(int ncid, int nflashes, GLM_FLASH_T *flash);
    int read_dims(int ncid, size_t *nevents, size_t *ngroups, size_t *nflashes);
    int read_scalars(int ncid, GLM_SCALAR_T *glm_scalar);
    int glm_read_file(char *file_name, int verbose);
    int glm_read_file_arrays(char *file_name, int verbose);

#if defined(__cplusplus)
}
#endif

#endif /* _GOES_GLM_H */
