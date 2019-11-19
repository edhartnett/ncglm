/**
 * @file
 * Code to read data from the GOES-17 Global Lightning Mapper.
 *
 * @author Ed Hartnett, 10/10/19, Amsterdam
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
#include "ncglm.h"

/** Name of title attribute. */
#define TITLE "title"

/** Name of summary attribute. */
#define SUMMARY "summary"

/** Name of platform_ID attribute. */
#define PLATFORM_ID "platform_ID"

/** Number of timing runs when -t option is used. */
#define NUM_TRIALS 10

/**
 * Read the dimensions.
 *
 * @param ncid ID of already opened GLM file.
 * @param nevent Pointer that gets the number of events. Ignored if NULL.
 * @param ngroup Pointer that gets the number of groups. Ignored if NULL.
 * @param nflash Pointer that gets the number of flashes. Ignored if NULL.
 *
 * @return 0 for success, error code otherwise.
 * @author Ed Hartnett
 */
int
glm_read_dims(int ncid, size_t *nevent, size_t *ngroup, size_t *nflash)
{
    /* Dimensions and their lengths. */
    int event_dimid, group_dimid, flash_dimid;
    int number_of_time_bounds_dimid;
    int number_of_field_of_view_bounds_dimid;
    int number_of_wavelength_bounds_dimid;
    size_t ntime_bounds, nfov_bounds, nwl_bounds;
    int ret;

    /* Check inputs. */
    assert(ncid > 0);

    if (nflash)
    {
        if ((ret = nc_inq_dimid(ncid, NUMBER_OF_FLASHES, &flash_dimid)))
            NC_ERR(ret);
        if ((ret = nc_inq_dimlen(ncid, flash_dimid, nflash)))
            NC_ERR(ret);
    }

    if (ngroup)
    {
        if ((ret = nc_inq_dimid(ncid, NUMBER_OF_GROUPS, &group_dimid)))
            NC_ERR(ret);
        if ((ret = nc_inq_dimlen(ncid, group_dimid, ngroup)))
            NC_ERR(ret);
    }

    if (nevent)
    {
        if ((ret = nc_inq_dimid(ncid, NUMBER_OF_EVENTS, &event_dimid)))
            NC_ERR(ret);
        if ((ret = nc_inq_dimlen(ncid, event_dimid, nevent)))
            NC_ERR(ret);
    }

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

/**
 * Read the scalars and small variables from the GLM file.
 *
 * @param ncid ID of already opened GLM file.
 * @param glm_scalar Pointer to already allocated GLM_SCALAR_T.
 *
 * @return 0 for success, error code otherwise.
 * @author Ed Hartnett
 */
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

/**
 * From GOES R SERIESPRODUCT DEFINITION AND USERS’ GUIDE(PUG) Vol 3
 * (https://www.goes-r.gov/users/docs/PUG-L1b-vol3.pdf)
 *
 * The classic model for netCDF (used by the GS) does not support
 * unsigned integers larger than 8 bits.  Many of the variables in
 * GOES-R netCDF files are unsigned integers of 16-bit or 32-bit
 * length.  The following process is recommended to convert these
 * unsigned integers:
 *
 * 1.Retrieve the variable data from the netCDF file.
 *
 * 2.For this variable, retrieve the attribute “_Unsigned”.
 *
 * 3.If the “_Unsigned” attribute is set to “true” or “True”, then
 * cast the variable data to be unsigned.
 *
 * The steps above must be completed before applying the scale_factor
 * and add_offset values to convert from scaled integer to science
 * units.  Also, the valid_range and _FillValue attribute values are
 * to be governed by the “_Unsigned” attribute
 *
 * From a netCDF group email:
 * https://www.unidata.ucar.edu/mailing_lists/archives/netcdfgroup/2002/msg00034.html
 *
 * Normally you store a group of numbers, all with the same scale and
 * offset. So first you calculate the min and max of that group of
 * numbers. Also let max_integer = maximum integer (eg for INTEGER*2
 * this equals 32,167).
 *
 *  then
 *  offset = min
 *  scale = max_integer / (max - min)
 *
 *  store this number into netcdf file:
 *
 *  store_x = (x - offset) * scale = max_integer * (x - min) / (max - min)
 *
 *  note that when x = min, store_x = 0, and when x = max, store_x
 *  max_integer.
 *
 *  the reading program should use the formula
 *
 *  x = store_x/scale + offset.
 *
 * @param file_name Name of the GLM file.
 * @param verbose Non-zero for some printf output.
 *
 * @return 0 for success, error code otherwise.
 * @author Ed Hartnett
*/
int
glm_read_file(char *file_name, int verbose)
{
    int ncid;

    size_t nevents, ngroups, nflashes;
    size_t my_nevent;

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
    /* if (verbose) */
    /* { */
    /*     if (show_att(ncid, NC_GLOBAL, TITLE)) */
    /*         return GLM_ERR_MEMORY; */
    /*     if (show_att(ncid, NC_GLOBAL, PLATFORM_ID)) */
    /*         return GLM_ERR_MEMORY; */
    /*     if (show_att(ncid, NC_GLOBAL, SUMMARY)) */
    /*         return GLM_ERR_MEMORY; */
    /* } */

    /* Read the size of the dimensions. */
    if ((ret = glm_read_dims(ncid, &nevents, &ngroups, &nflashes)))
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
    if ((ret = glm_read_event_structs(ncid, &my_nevent, event)))
	return GLM_ERR_MEMORY;
    if ((ret = glm_read_group_structs(ncid, ngroups, group)))
	return GLM_ERR_MEMORY;
    if ((ret = glm_read_flash_structs(ncid, nflashes, flash)))
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
    size_t my_nevent;

    /* Arrays for event data. */
    int *event_id;
    unsigned int *time_offset;
    float *lat, *lon, *energy;
    int *parent_group_id;

    /* Arrays for group data. */
    GLM_GROUP_T *group;

    /* Arrays for flash data. */
    GLM_FLASH_T *flash;

    /* Scalar data. */
    GLM_SCALAR_T glm_scalar;

    int ret;
    
    /* Open the data file as read-only. */
    if ((ret = nc_open(file_name, NC_NOWRITE, &ncid)))
	NC_ERR(ret);

    /* Read the size of the dimensions. */
    if ((ret = glm_read_dims(ncid, &nevents, &ngroups, &nflashes)))
	return GLM_ERR_MEMORY;
    
    if (verbose)
	printf("nflashes %zu ngroups %zu nevents %zu\n", nflashes,
	       ngroups, nevents);

    /* Allocate storage for event arrays. */
    if (!(event_id = malloc(nevents * sizeof(int))))
	return GLM_ERR_MEMORY;
    if (!(time_offset = malloc(nevents * sizeof(unsigned int))))
	return GLM_ERR_MEMORY;
    if (!(lat = malloc(nevents * sizeof(float))))
	return GLM_ERR_MEMORY;
    if (!(lon = malloc(nevents * sizeof(float))))
	return GLM_ERR_MEMORY;
    if (!(energy = malloc(nevents * sizeof(float))))
	return GLM_ERR_MEMORY;
    if (!(parent_group_id = malloc(nevents * sizeof(int))))
	return GLM_ERR_MEMORY;

    /* Allocate storage for group arrays. */
    if (!(group = malloc(ngroups * sizeof(GLM_GROUP_T))))
	return GLM_ERR_MEMORY;

    /* Allocate storage for flash arrays. */
    if (!(flash = malloc(nflashes * sizeof(GLM_FLASH_T))))
	return GLM_ERR_MEMORY;

    /* Read the vars. */
    if ((ret = glm_read_event_arrays(ncid, &my_nevent, event_id, time_offset,
                                     lat, lon, energy, parent_group_id)))
	return GLM_ERR_MEMORY;
    /* if ((ret = read_group_vars(ncid, ngroups, group))) */
    /*     return GLM_ERR_MEMORY; */
    /* if ((ret = read_flash_vars(ncid, nflashes, flash))) */
    /*     return GLM_ERR_MEMORY; */
    if ((ret = read_scalars(ncid, &glm_scalar)))
	return GLM_ERR_MEMORY;

    /* Close the data file. */
    if ((ret = nc_close(ncid)))
	NC_ERR(ret);

    /* Free memory. */
    free(event_id);
    free(group);
    free(flash);
    
    return 0;
}
