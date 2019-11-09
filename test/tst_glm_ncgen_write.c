#include <stdio.h>
#include <stdlib.h>
#include <netcdf.h>



void
check_err(const int stat, const int line, const char *file) {
    if (stat != NC_NOERR) {
        (void)fprintf(stderr,"line %d of %s: %s\n", line, file, nc_strerror(stat));
        fflush(stderr);
        exit(1);
    }
}

int
main() {/* create ncdump2.nc */

    int  stat;  /* return status */
    int  ncid;  /* netCDF id */

    /* group ids */
    int OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp;

    /* dimension ids */
    int number_of_flashes_dim;
    int number_of_groups_dim;
    int number_of_events_dim;
    int number_of_time_bounds_dim;
    int number_of_field_of_view_bounds_dim;
    int number_of_wavelength_bounds_dim;

    /* dimension lengths */
    size_t number_of_flashes_len = NC_UNLIMITED;
    size_t number_of_groups_len = NC_UNLIMITED;
    size_t number_of_events_len = NC_UNLIMITED;
    size_t number_of_time_bounds_len = 2;
    size_t number_of_field_of_view_bounds_len = 2;
    size_t number_of_wavelength_bounds_len = 2;

    /* variable ids */
    int event_id_id;
    int event_time_offset_id;
    int event_lat_id;
    int event_lon_id;
    int event_energy_id;
    int event_parent_group_id_id;
    int group_id_id;
    int group_time_offset_id;
    int group_frame_time_offset_id;
    int group_lat_id;
    int group_lon_id;
    int group_area_id;
    int group_energy_id;
    int group_parent_flash_id_id;
    int group_quality_flag_id;
    int flash_id_id;
    int flash_time_offset_of_first_event_id;
    int flash_time_offset_of_last_event_id;
    int flash_frame_time_offset_of_first_event_id;
    int flash_frame_time_offset_of_last_event_id;
    int flash_lat_id;
    int flash_lon_id;
    int flash_area_id;
    int flash_energy_id;
    int flash_quality_flag_id;
    int product_time_id;
    int product_time_bounds_id;
    int lightning_wavelength_id;
    int lightning_wavelength_bounds_id;
    int group_time_threshold_id;
    int flash_time_threshold_id;
    int lat_field_of_view_id;
    int lat_field_of_view_bounds_id;
    int goes_lat_lon_projection_id;
    int event_count_id;
    int group_count_id;
    int flash_count_id;
    int percent_navigated_L1b_events_id;
    int yaw_flip_flag_id;
    int nominal_satellite_subpoint_lat_id;
    int nominal_satellite_height_id;
    int nominal_satellite_subpoint_lon_id;
    int lon_field_of_view_id;
    int lon_field_of_view_bounds_id;
    int percent_uncorrectable_L0_errors_id;
    int algorithm_dynamic_input_data_container_id;
    int processing_parm_version_container_id;
    int algorithm_product_version_container_id;

    /* rank (number of dimensions) for each variable */
#   define RANK_event_id 1
#   define RANK_event_time_offset 1
#   define RANK_event_lat 1
#   define RANK_event_lon 1
#   define RANK_event_energy 1
#   define RANK_event_parent_group_id 1
#   define RANK_group_id 1
#   define RANK_group_time_offset 1
#   define RANK_group_frame_time_offset 1
#   define RANK_group_lat 1
#   define RANK_group_lon 1
#   define RANK_group_area 1
#   define RANK_group_energy 1
#   define RANK_group_parent_flash_id 1
#   define RANK_group_quality_flag 1
#   define RANK_flash_id 1
#   define RANK_flash_time_offset_of_first_event 1
#   define RANK_flash_time_offset_of_last_event 1
#   define RANK_flash_frame_time_offset_of_first_event 1
#   define RANK_flash_frame_time_offset_of_last_event 1
#   define RANK_flash_lat 1
#   define RANK_flash_lon 1
#   define RANK_flash_area 1
#   define RANK_flash_energy 1
#   define RANK_flash_quality_flag 1
#   define RANK_product_time 0
#   define RANK_product_time_bounds 1
#   define RANK_lightning_wavelength 0
#   define RANK_lightning_wavelength_bounds 1
#   define RANK_group_time_threshold 0
#   define RANK_flash_time_threshold 0
#   define RANK_lat_field_of_view 0
#   define RANK_lat_field_of_view_bounds 1
#   define RANK_goes_lat_lon_projection 0
#   define RANK_event_count 0
#   define RANK_group_count 0
#   define RANK_flash_count 0
#   define RANK_percent_navigated_L1b_events 0
#   define RANK_yaw_flip_flag 0
#   define RANK_nominal_satellite_subpoint_lat 0
#   define RANK_nominal_satellite_height 0
#   define RANK_nominal_satellite_subpoint_lon 0
#   define RANK_lon_field_of_view 0
#   define RANK_lon_field_of_view_bounds 1
#   define RANK_percent_uncorrectable_L0_errors 0
#   define RANK_algorithm_dynamic_input_data_container 0
#   define RANK_processing_parm_version_container 0
#   define RANK_algorithm_product_version_container 0

    /* variable shapes */
    int event_id_dims[RANK_event_id];
    int event_time_offset_dims[RANK_event_time_offset];
    int event_lat_dims[RANK_event_lat];
    int event_lon_dims[RANK_event_lon];
    int event_energy_dims[RANK_event_energy];
    int event_parent_group_id_dims[RANK_event_parent_group_id];
    int group_id_dims[RANK_group_id];
    int group_time_offset_dims[RANK_group_time_offset];
    int group_frame_time_offset_dims[RANK_group_frame_time_offset];
    int group_lat_dims[RANK_group_lat];
    int group_lon_dims[RANK_group_lon];
    int group_area_dims[RANK_group_area];
    int group_energy_dims[RANK_group_energy];
    int group_parent_flash_id_dims[RANK_group_parent_flash_id];
    int group_quality_flag_dims[RANK_group_quality_flag];
    int flash_id_dims[RANK_flash_id];
    int flash_time_offset_of_first_event_dims[RANK_flash_time_offset_of_first_event];
    int flash_time_offset_of_last_event_dims[RANK_flash_time_offset_of_last_event];
    int flash_frame_time_offset_of_first_event_dims[RANK_flash_frame_time_offset_of_first_event];
    int flash_frame_time_offset_of_last_event_dims[RANK_flash_frame_time_offset_of_last_event];
    int flash_lat_dims[RANK_flash_lat];
    int flash_lon_dims[RANK_flash_lon];
    int flash_area_dims[RANK_flash_area];
    int flash_energy_dims[RANK_flash_energy];
    int flash_quality_flag_dims[RANK_flash_quality_flag];
    int product_time_bounds_dims[RANK_product_time_bounds];
    int lightning_wavelength_bounds_dims[RANK_lightning_wavelength_bounds];
    int lat_field_of_view_bounds_dims[RANK_lat_field_of_view_bounds];
    int lon_field_of_view_bounds_dims[RANK_lon_field_of_view_bounds];

    /* enter define mode */
    stat = nc_create("ncdump2.nc", NC_CLOBBER|NC_NETCDF4, &ncid);
    check_err(stat,__LINE__,__FILE__);
    OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp = ncid;

    /* define dimensions */
    stat = nc_def_dim(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "number_of_flashes", number_of_flashes_len, &number_of_flashes_dim);
    check_err(stat,__LINE__,__FILE__);
    stat = nc_def_dim(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "number_of_groups", number_of_groups_len, &number_of_groups_dim);
    check_err(stat,__LINE__,__FILE__);
    stat = nc_def_dim(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "number_of_events", number_of_events_len, &number_of_events_dim);
    check_err(stat,__LINE__,__FILE__);
    stat = nc_def_dim(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "number_of_time_bounds", number_of_time_bounds_len, &number_of_time_bounds_dim);
    check_err(stat,__LINE__,__FILE__);
    stat = nc_def_dim(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "number_of_field_of_view_bounds", number_of_field_of_view_bounds_len, &number_of_field_of_view_bounds_dim);
    check_err(stat,__LINE__,__FILE__);
    stat = nc_def_dim(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "number_of_wavelength_bounds", number_of_wavelength_bounds_len, &number_of_wavelength_bounds_dim);
    check_err(stat,__LINE__,__FILE__);

    /* define variables */

    event_id_dims[0] = number_of_events_dim;
    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "event_id", NC_INT, RANK_event_id, event_id_dims, &event_id_id);
    check_err(stat,__LINE__,__FILE__);

    event_time_offset_dims[0] = number_of_events_dim;
    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "event_time_offset", NC_SHORT, RANK_event_time_offset, event_time_offset_dims, &event_time_offset_id);
    check_err(stat,__LINE__,__FILE__);

    event_lat_dims[0] = number_of_events_dim;
    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "event_lat", NC_SHORT, RANK_event_lat, event_lat_dims, &event_lat_id);
    check_err(stat,__LINE__,__FILE__);

    event_lon_dims[0] = number_of_events_dim;
    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "event_lon", NC_SHORT, RANK_event_lon, event_lon_dims, &event_lon_id);
    check_err(stat,__LINE__,__FILE__);

    event_energy_dims[0] = number_of_events_dim;
    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "event_energy", NC_SHORT, RANK_event_energy, event_energy_dims, &event_energy_id);
    check_err(stat,__LINE__,__FILE__);

    event_parent_group_id_dims[0] = number_of_events_dim;
    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "event_parent_group_id", NC_INT, RANK_event_parent_group_id, event_parent_group_id_dims, &event_parent_group_id_id);
    check_err(stat,__LINE__,__FILE__);

    group_id_dims[0] = number_of_groups_dim;
    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "group_id", NC_INT, RANK_group_id, group_id_dims, &group_id_id);
    check_err(stat,__LINE__,__FILE__);

    group_time_offset_dims[0] = number_of_groups_dim;
    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "group_time_offset", NC_SHORT, RANK_group_time_offset, group_time_offset_dims, &group_time_offset_id);
    check_err(stat,__LINE__,__FILE__);

    group_frame_time_offset_dims[0] = number_of_groups_dim;
    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "group_frame_time_offset", NC_SHORT, RANK_group_frame_time_offset, group_frame_time_offset_dims, &group_frame_time_offset_id);
    check_err(stat,__LINE__,__FILE__);

    group_lat_dims[0] = number_of_groups_dim;
    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "group_lat", NC_FLOAT, RANK_group_lat, group_lat_dims, &group_lat_id);
    check_err(stat,__LINE__,__FILE__);

    group_lon_dims[0] = number_of_groups_dim;
    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "group_lon", NC_FLOAT, RANK_group_lon, group_lon_dims, &group_lon_id);
    check_err(stat,__LINE__,__FILE__);

    group_area_dims[0] = number_of_groups_dim;
    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "group_area", NC_SHORT, RANK_group_area, group_area_dims, &group_area_id);
    check_err(stat,__LINE__,__FILE__);

    group_energy_dims[0] = number_of_groups_dim;
    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "group_energy", NC_SHORT, RANK_group_energy, group_energy_dims, &group_energy_id);
    check_err(stat,__LINE__,__FILE__);

    group_parent_flash_id_dims[0] = number_of_groups_dim;
    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "group_parent_flash_id", NC_SHORT, RANK_group_parent_flash_id, group_parent_flash_id_dims, &group_parent_flash_id_id);
    check_err(stat,__LINE__,__FILE__);

    group_quality_flag_dims[0] = number_of_groups_dim;
    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "group_quality_flag", NC_SHORT, RANK_group_quality_flag, group_quality_flag_dims, &group_quality_flag_id);
    check_err(stat,__LINE__,__FILE__);

    flash_id_dims[0] = number_of_flashes_dim;
    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "flash_id", NC_SHORT, RANK_flash_id, flash_id_dims, &flash_id_id);
    check_err(stat,__LINE__,__FILE__);

    flash_time_offset_of_first_event_dims[0] = number_of_flashes_dim;
    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "flash_time_offset_of_first_event", NC_SHORT, RANK_flash_time_offset_of_first_event, flash_time_offset_of_first_event_dims, &flash_time_offset_of_first_event_id);
    check_err(stat,__LINE__,__FILE__);

    flash_time_offset_of_last_event_dims[0] = number_of_flashes_dim;
    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "flash_time_offset_of_last_event", NC_SHORT, RANK_flash_time_offset_of_last_event, flash_time_offset_of_last_event_dims, &flash_time_offset_of_last_event_id);
    check_err(stat,__LINE__,__FILE__);

    flash_frame_time_offset_of_first_event_dims[0] = number_of_flashes_dim;
    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "flash_frame_time_offset_of_first_event", NC_SHORT, RANK_flash_frame_time_offset_of_first_event, flash_frame_time_offset_of_first_event_dims, &flash_frame_time_offset_of_first_event_id);
    check_err(stat,__LINE__,__FILE__);

    flash_frame_time_offset_of_last_event_dims[0] = number_of_flashes_dim;
    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "flash_frame_time_offset_of_last_event", NC_SHORT, RANK_flash_frame_time_offset_of_last_event, flash_frame_time_offset_of_last_event_dims, &flash_frame_time_offset_of_last_event_id);
    check_err(stat,__LINE__,__FILE__);

    flash_lat_dims[0] = number_of_flashes_dim;
    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "flash_lat", NC_FLOAT, RANK_flash_lat, flash_lat_dims, &flash_lat_id);
    check_err(stat,__LINE__,__FILE__);

    flash_lon_dims[0] = number_of_flashes_dim;
    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "flash_lon", NC_FLOAT, RANK_flash_lon, flash_lon_dims, &flash_lon_id);
    check_err(stat,__LINE__,__FILE__);

    flash_area_dims[0] = number_of_flashes_dim;
    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "flash_area", NC_SHORT, RANK_flash_area, flash_area_dims, &flash_area_id);
    check_err(stat,__LINE__,__FILE__);

    flash_energy_dims[0] = number_of_flashes_dim;
    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "flash_energy", NC_SHORT, RANK_flash_energy, flash_energy_dims, &flash_energy_id);
    check_err(stat,__LINE__,__FILE__);

    flash_quality_flag_dims[0] = number_of_flashes_dim;
    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "flash_quality_flag", NC_SHORT, RANK_flash_quality_flag, flash_quality_flag_dims, &flash_quality_flag_id);
    check_err(stat,__LINE__,__FILE__);

    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "product_time", NC_DOUBLE, RANK_product_time, 0, &product_time_id);
    check_err(stat,__LINE__,__FILE__);

    product_time_bounds_dims[0] = number_of_time_bounds_dim;
    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "product_time_bounds", NC_DOUBLE, RANK_product_time_bounds, product_time_bounds_dims, &product_time_bounds_id);
    check_err(stat,__LINE__,__FILE__);

    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "lightning_wavelength", NC_FLOAT, RANK_lightning_wavelength, 0, &lightning_wavelength_id);
    check_err(stat,__LINE__,__FILE__);

    lightning_wavelength_bounds_dims[0] = number_of_wavelength_bounds_dim;
    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "lightning_wavelength_bounds", NC_FLOAT, RANK_lightning_wavelength_bounds, lightning_wavelength_bounds_dims, &lightning_wavelength_bounds_id);
    check_err(stat,__LINE__,__FILE__);

    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "group_time_threshold", NC_FLOAT, RANK_group_time_threshold, 0, &group_time_threshold_id);
    check_err(stat,__LINE__,__FILE__);

    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "flash_time_threshold", NC_FLOAT, RANK_flash_time_threshold, 0, &flash_time_threshold_id);
    check_err(stat,__LINE__,__FILE__);

    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "lat_field_of_view", NC_FLOAT, RANK_lat_field_of_view, 0, &lat_field_of_view_id);
    check_err(stat,__LINE__,__FILE__);

    lat_field_of_view_bounds_dims[0] = number_of_field_of_view_bounds_dim;
    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "lat_field_of_view_bounds", NC_FLOAT, RANK_lat_field_of_view_bounds, lat_field_of_view_bounds_dims, &lat_field_of_view_bounds_id);
    check_err(stat,__LINE__,__FILE__);

    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "goes_lat_lon_projection", NC_INT, RANK_goes_lat_lon_projection, 0, &goes_lat_lon_projection_id);
    check_err(stat,__LINE__,__FILE__);

    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "event_count", NC_INT, RANK_event_count, 0, &event_count_id);
    check_err(stat,__LINE__,__FILE__);

    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "group_count", NC_INT, RANK_group_count, 0, &group_count_id);
    check_err(stat,__LINE__,__FILE__);

    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "flash_count", NC_INT, RANK_flash_count, 0, &flash_count_id);
    check_err(stat,__LINE__,__FILE__);

    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "percent_navigated_L1b_events", NC_FLOAT, RANK_percent_navigated_L1b_events, 0, &percent_navigated_L1b_events_id);
    check_err(stat,__LINE__,__FILE__);

    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "yaw_flip_flag", NC_BYTE, RANK_yaw_flip_flag, 0, &yaw_flip_flag_id);
    check_err(stat,__LINE__,__FILE__);

    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "nominal_satellite_subpoint_lat", NC_FLOAT, RANK_nominal_satellite_subpoint_lat, 0, &nominal_satellite_subpoint_lat_id);
    check_err(stat,__LINE__,__FILE__);

    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "nominal_satellite_height", NC_FLOAT, RANK_nominal_satellite_height, 0, &nominal_satellite_height_id);
    check_err(stat,__LINE__,__FILE__);

    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "nominal_satellite_subpoint_lon", NC_FLOAT, RANK_nominal_satellite_subpoint_lon, 0, &nominal_satellite_subpoint_lon_id);
    check_err(stat,__LINE__,__FILE__);

    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "lon_field_of_view", NC_FLOAT, RANK_lon_field_of_view, 0, &lon_field_of_view_id);
    check_err(stat,__LINE__,__FILE__);

    lon_field_of_view_bounds_dims[0] = number_of_field_of_view_bounds_dim;
    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "lon_field_of_view_bounds", NC_FLOAT, RANK_lon_field_of_view_bounds, lon_field_of_view_bounds_dims, &lon_field_of_view_bounds_id);
    check_err(stat,__LINE__,__FILE__);

    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "percent_uncorrectable_L0_errors", NC_FLOAT, RANK_percent_uncorrectable_L0_errors, 0, &percent_uncorrectable_L0_errors_id);
    check_err(stat,__LINE__,__FILE__);

    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "algorithm_dynamic_input_data_container", NC_INT, RANK_algorithm_dynamic_input_data_container, 0, &algorithm_dynamic_input_data_container_id);
    check_err(stat,__LINE__,__FILE__);

    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "processing_parm_version_container", NC_INT, RANK_processing_parm_version_container, 0, &processing_parm_version_container_id);
    check_err(stat,__LINE__,__FILE__);

    stat = nc_def_var(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, "algorithm_product_version_container", NC_INT, RANK_algorithm_product_version_container, 0, &algorithm_product_version_container_id);
    check_err(stat,__LINE__,__FILE__);

    /* assign global attributes */

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, NC_GLOBAL, "production_site", 5, "WCDAS");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, NC_GLOBAL, "featureType", 5, "point");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, NC_GLOBAL, "dataset_name", 69, "OR_GLM-L2-LCFA_G17_s20192692359400_e20192700000000_c20192700000028.nc");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, NC_GLOBAL, "naming_authority", 15, "gov.nesdis.noaa");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, NC_GLOBAL, "Conventions", 6, "CF-1.7");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, NC_GLOBAL, "institution", 159, "DOC/NOAA/NESDIS> U.S. Department of Commerce, National Oceanic and Atmospheric Administration, National Environmental Satellite, Data, and Information Services");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, NC_GLOBAL, "project", 4, "GOES");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, NC_GLOBAL, "iso_series_metadata_id", 36, "f5816f53-fd6d-11e3-a3ac-0800200c9a66");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, NC_GLOBAL, "Metadata_Conventions", 30, "Unidata Dataset Discovery v1.0");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, NC_GLOBAL, "keywords_vocabulary", 84, "NASA Global Change Master Directory (GCMD) Earth Science Keywords, Version 7.0.0.0.0");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, NC_GLOBAL, "standard_name_vocabulary", 42, "CF Standard Name Table (v35, 20 July 2016)");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, NC_GLOBAL, "title", 56, "GLM L2 Lightning Detections: Events, Groups, and Flashes");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, NC_GLOBAL, "summary", 732, "The Lightning Detections: Events, Groups, and Flashes product consists of a hierarchy of earth-located lightning radiant energy measures including events, groups, and flashes. Lightning events are detected by the instrument. Lightning groups are a collection of one or more lightning events that satisfy temporal and spatial coincidence thresholds. Similarly, lightning flashes are a collection of one or more lightning groups that satisfy temporal and spatial coincidence thresholds. The product includes the relationship among lightning events, groups, and flashes, and the area coverage of lightning groups and flashes. The product also includes processing and data quality metadata, and satellite state and location information.");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, NC_GLOBAL, "license", 64, "Unclassified data.  Access is restricted to approved users only.");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, NC_GLOBAL, "keywords", 96, "ATMOSPHERE > ATMOSPHERIC ELECTRICITY > LIGHTNING, ATMOSPHERE > ATMOSPHERIC PHENOMENA > LIGHTNING");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, NC_GLOBAL, "cdm_data_type", 5, "Point");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, NC_GLOBAL, "processing_level", 55, "National Aeronautics and Space Administration (NASA) L2");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, NC_GLOBAL, "orbital_slot", 9, "GOES-West");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, NC_GLOBAL, "platform_ID", 3, "G17");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, NC_GLOBAL, "instrument_ID", 3, "FM2");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, NC_GLOBAL, "instrument_type", 44, "GOES-R Series Geostationary Lightning Mapper");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, NC_GLOBAL, "spatial_resolution", 12, "8km at nadir");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, NC_GLOBAL, "date_created", 22, "2019-09-27T00:00:02.8Z");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, NC_GLOBAL, "time_coverage_start", 22, "2019-09-26T23:59:40.0Z");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, NC_GLOBAL, "time_coverage_end", 22, "2019-09-27T00:00:00.0Z");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, NC_GLOBAL, "production_data_source", 8, "Realtime");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, NC_GLOBAL, "production_environment", 2, "OE");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, NC_GLOBAL, "LUT_Filenames", 804, "GLM_CALINR_AllFilters(FM2W_CDRL79RevD_PR_08_01_01_ADR928RR)-615449900.0.h5 GLM_SolarGlintParameters(FMAA_CDRL79RevH_DO_08_00_00)-587190369.0.xml GLM_AlignmentParameters(FMAW_INT_ONLY_DO_07_00_00)-600000000.0.xml GLM_BackgroundGain(FM2A_CDRL79RevG_DO_08_00_00)-598329337.0.h5 GLM_CoastlineID_Parameters(FM2W_CDRL79Rev-_DO_07_00_00)-600000000.0.xml GLM_DownSamplingLUTs(FMAA_CDRL46RevM_DO_08_00_00)-600000000.0.h5 GLM_BG_Assemble(FMAA_CDRL46RevM_DO_08_00_00)-600000000.0.xml GLM_GSHHS_Data(FM2W_CDRL79RevC_DO_08_00_00)-603000000.0.h5 GLM_IlluminationMask_PV_LUT(FMAA_CDRL46RevM_DO_08_00_00)-600000000.0.h5 GLMNavigationParams(FM2W_CDRL79RevC_DO_08_00_00)-604324800.0.xml GLM_L1aDS_CALINR(FMAA_CDRL43RevJ_DO_08_00_00)-600000000.0.h5 AI_GLM-L2-GLMSemiStaticParams(FMAW_CDRL46RevM_PR_08_01_00)-615444400.0.bin");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, NC_GLOBAL, "id", 36, "e12c8e5b-d65c-462d-9a57-878b5881716a");
    check_err(stat,__LINE__,__FILE__);
    }


    /* assign per-variable attributes */

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_id_id, "long_name", 41, "product-unique lightning event identifier");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_id_id, "_Unsigned", 4, "true");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_id_id, "units", 1, "1");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_time_offset_id, "long_name", 55, "GLM L2+ Lightning Detection: event's time of occurrence");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_time_offset_id, "standard_name", 4, "time");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_time_offset_id, "_Unsigned", 4, "true");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float scale_factor_att[1] = {((float)0.00038147561)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_time_offset_id, "scale_factor", NC_FLOAT, 1, scale_factor_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float add_offset_att[1] = {((float)-5)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_time_offset_id, "add_offset", NC_FLOAT, 1, add_offset_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_time_offset_id, "units", 37, "seconds since 2019-09-26 23:59:40.000");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_time_offset_id, "axis", 1, "T");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_lat_id, "long_name", 54, "GLM L2+ Lightning Detection: event latitude coordinate");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_lat_id, "standard_name", 8, "latitude");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_lat_id, "_Unsigned", 4, "true");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float scale_factor_att[1] = {((float)0.00203128)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_lat_id, "scale_factor", NC_FLOAT, 1, scale_factor_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float add_offset_att[1] = {((float)-66.559998)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_lat_id, "add_offset", NC_FLOAT, 1, add_offset_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_lat_id, "units", 13, "degrees_north");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_lat_id, "axis", 1, "Y");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_lon_id, "long_name", 55, "GLM L2+ Lightning Detection: event longitude coordinate");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_lon_id, "standard_name", 9, "longitude");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_lon_id, "_Unsigned", 4, "true");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float scale_factor_att[1] = {((float)0.00203128)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_lon_id, "scale_factor", NC_FLOAT, 1, scale_factor_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float add_offset_att[1] = {((float)-203.56)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_lon_id, "add_offset", NC_FLOAT, 1, add_offset_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_lon_id, "units", 12, "degrees_east");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_lon_id, "axis", 1, "X");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const short _FillValue_att[1] = {-1} ;
    stat = nc_put_att_short(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_energy_id, "_FillValue", NC_SHORT, 1, _FillValue_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_energy_id, "long_name", 49, "GLM L2+ Lightning Detection: event radiant energy");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_energy_id, "standard_name", 24, "lightning_radiant_energy");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_energy_id, "_Unsigned", 4, "true");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float scale_factor_att[1] = {((float)1.52597e-15)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_energy_id, "scale_factor", NC_FLOAT, 1, scale_factor_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float add_offset_att[1] = {((float)0)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_energy_id, "add_offset", NC_FLOAT, 1, add_offset_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_energy_id, "units", 1, "J");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_energy_id, "coordinates", 89, "event_parent_group_id event_id lightning_wavelength event_time_offset event_lat event_lon");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_energy_id, "grid_mapping", 23, "goes_lat_lon_projection");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_energy_id, "cell_methods", 198, "lightning_wavelength: sum event_time_offset: point (sensor pixels have 2 ms integration time) area: sum (interval: 8 km comment: resolution of sensor data at nadir, filtered events only) where cloud");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_parent_group_id_id, "long_name", 64, "product-unique lightning group identifier for one or more events");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_parent_group_id_id, "_Unsigned", 4, "true");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_parent_group_id_id, "units", 1, "1");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_id_id, "long_name", 41, "product-unique lightning group identifier");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_id_id, "_Unsigned", 4, "true");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_id_id, "units", 1, "1");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_time_offset_id, "long_name", 89, "GLM L2+ Lightning Detection: mean time of group's constituent events' times of occurrence");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_time_offset_id, "standard_name", 4, "time");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_time_offset_id, "_Unsigned", 4, "true");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float scale_factor_att[1] = {((float)0.00038147561)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_time_offset_id, "scale_factor", NC_FLOAT, 1, scale_factor_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float add_offset_att[1] = {((float)-5)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_time_offset_id, "add_offset", NC_FLOAT, 1, add_offset_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_time_offset_id, "units", 37, "seconds since 2019-09-26 23:59:40.000");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_time_offset_id, "axis", 1, "T");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_frame_time_offset_id, "long_name", 89, "GLM L2+ Lightning Detection: mean time of group's constituent events' times of occurrence");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_frame_time_offset_id, "standard_name", 4, "time");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_frame_time_offset_id, "_Unsigned", 4, "true");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float scale_factor_att[1] = {((float)0.00038147561)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_frame_time_offset_id, "scale_factor", NC_FLOAT, 1, scale_factor_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float add_offset_att[1] = {((float)-5)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_frame_time_offset_id, "add_offset", NC_FLOAT, 1, add_offset_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_frame_time_offset_id, "units", 37, "seconds since 2019-09-26 23:59:40.000");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_frame_time_offset_id, "axis", 1, "T");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_lat_id, "long_name", 124, "GLM L2+ Lightning Detection: group centroid (mean constituent event latitude weighted by their energies) latitude coordinate");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_lat_id, "standard_name", 8, "latitude");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_lat_id, "units", 13, "degrees_north");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_lat_id, "axis", 1, "Y");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_lon_id, "long_name", 125, "GLM L2+ Lightning Detection: group centroid (mean constituent event latitude weighted by their energies) longitude coordinate");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_lon_id, "standard_name", 9, "longitude");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_lon_id, "units", 12, "degrees_east");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_lon_id, "axis", 1, "X");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const short _FillValue_att[1] = {-1} ;
    stat = nc_put_att_short(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_area_id, "_FillValue", NC_SHORT, 1, _FillValue_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_area_id, "long_name", 104, "GLM L2+ Lightning Detection: group area coverage (pixels containing at least one constituent event only)");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_area_id, "_Unsigned", 4, "true");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const short valid_range_att[2] = {0, -6} ;
    stat = nc_put_att_short(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_area_id, "valid_range", NC_SHORT, 2, valid_range_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float scale_factor_att[1] = {((float)152601.91)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_area_id, "scale_factor", NC_FLOAT, 1, scale_factor_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float add_offset_att[1] = {((float)0)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_area_id, "add_offset", NC_FLOAT, 1, add_offset_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_area_id, "units", 2, "m2");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_area_id, "coordinates", 132, "group_parent_flash_id event_parent_group_id group_id lightning_wavelength group_time_threshold group_time_offset group_lat group_lon");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_area_id, "grid_mapping", 23, "goes_lat_lon_projection");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_area_id, "cell_methods", 301, "lightning_wavelength: sum group_time_offset: mean (times of occurrence of group's constituent events defined by variable event_parent_group_id) area: sum (interval: 8 km comment: resolution of sensor data at nadir, adjacent pixels only, including the diagonal, in sensor focal plane array) where cloud");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const short _FillValue_att[1] = {-1} ;
    stat = nc_put_att_short(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_energy_id, "_FillValue", NC_SHORT, 1, _FillValue_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_energy_id, "long_name", 49, "GLM L2+ Lightning Detection: group radiant energy");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_energy_id, "standard_name", 24, "lightning_radiant_energy");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_energy_id, "_Unsigned", 4, "true");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const short valid_range_att[2] = {0, -6} ;
    stat = nc_put_att_short(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_energy_id, "valid_range", NC_SHORT, 2, valid_range_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float scale_factor_att[1] = {((float)1.52597e-15)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_energy_id, "scale_factor", NC_FLOAT, 1, scale_factor_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float add_offset_att[1] = {((float)0)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_energy_id, "add_offset", NC_FLOAT, 1, add_offset_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_energy_id, "units", 1, "J");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_energy_id, "coordinates", 132, "group_parent_flash_id event_parent_group_id group_id lightning_wavelength group_time_threshold group_time_offset group_lat group_lon");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_energy_id, "grid_mapping", 23, "goes_lat_lon_projection");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_energy_id, "cell_measures", 16, "area: group_area");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_energy_id, "cell_methods", 285, "lightning_wavelength: sum group_time_offset: mean (times of occurrence of group's constituent events defined by variable event_parent_group_id) area: mean (centroid location of constituent events defined by variable event_parent_group_id weighted by their radiant energies) where cloud");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_energy_id, "ancillary_variables", 18, "group_quality_flag");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_parent_flash_id_id, "long_name", 64, "product-unique lightning flash identifier for one or more groups");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_parent_flash_id_id, "_Unsigned", 4, "true");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_parent_flash_id_id, "units", 1, "1");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const short _FillValue_att[1] = {-1} ;
    stat = nc_put_att_short(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_quality_flag_id, "_FillValue", NC_SHORT, 1, _FillValue_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_quality_flag_id, "long_name", 53, "GLM L2+ Lightning Detection: group data quality flags");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_quality_flag_id, "standard_name", 11, "status_flag");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_quality_flag_id, "_Unsigned", 4, "true");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const short valid_range_att[2] = {0, 5} ;
    stat = nc_put_att_short(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_quality_flag_id, "valid_range", NC_SHORT, 2, valid_range_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_quality_flag_id, "units", 1, "1");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_quality_flag_id, "coordinates", 88, "group_id lightning_wavelength group_time_threshold group_time_offset group_lat group_lon");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_quality_flag_id, "grid_mapping", 23, "goes_lat_lon_projection");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_quality_flag_id, "cell_methods", 285, "lightning_wavelength: sum group_time_offset: mean (times of occurrence of group's constituent events defined by variable event_parent_group_id) area: mean (centroid location of constituent events defined by variable event_parent_group_id weighted by their radiant energies) where cloud");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const short flag_values_att[4] = {0, 1, 3, 5} ;
    stat = nc_put_att_short(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_quality_flag_id, "flag_values", NC_SHORT, 4, flag_values_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_quality_flag_id, "flag_meanings", 221, "good_quality_qf degraded_due_to_group_constituent_events_out_of_time_order_or_parent_flash_abnormal_qf degraded_due_to_group_constituent_event_count_exceeds_threshold_qf degraded_due_to_group_duration_exceeds_threshold_qf");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const signed char number_of_qf_values_att[1] = {4} ;
    stat = nc_put_att_schar(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_quality_flag_id, "number_of_qf_values", NC_BYTE, 1, number_of_qf_values_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float percent_good_quality_qf_att[1] = {((float)1)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_quality_flag_id, "percent_good_quality_qf", NC_FLOAT, 1, percent_good_quality_qf_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float percent_degraded_due_to_group_constituent_events_out_of_time_order_or_parent_flash_abnormal_qf_att[1] = {((float)0)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_quality_flag_id, "percent_degraded_due_to_group_constituent_events_out_of_time_order_or_parent_flash_abnormal_qf", NC_FLOAT, 1, percent_degraded_due_to_group_constituent_events_out_of_time_order_or_parent_flash_abnormal_qf_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float percent_degraded_due_to_group_constituent_event_count_exceeds_threshold_qf_att[1] = {((float)0)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_quality_flag_id, "percent_degraded_due_to_group_constituent_event_count_exceeds_threshold_qf", NC_FLOAT, 1, percent_degraded_due_to_group_constituent_event_count_exceeds_threshold_qf_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float percent_degraded_due_to_group_duration_exceeds_threshold_qf_att[1] = {((float)0)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_quality_flag_id, "percent_degraded_due_to_group_duration_exceeds_threshold_qf", NC_FLOAT, 1, percent_degraded_due_to_group_duration_exceeds_threshold_qf_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_id_id, "long_name", 41, "product-unique lightning flash identifier");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_id_id, "_Unsigned", 4, "true");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_id_id, "units", 1, "1");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_time_offset_of_first_event_id, "long_name", 83, "GLM L2+ Lightning Detection: time of occurrence of first constituent event in flash");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_time_offset_of_first_event_id, "standard_name", 4, "time");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_time_offset_of_first_event_id, "_Unsigned", 4, "true");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float scale_factor_att[1] = {((float)0.00038147561)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_time_offset_of_first_event_id, "scale_factor", NC_FLOAT, 1, scale_factor_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float add_offset_att[1] = {((float)-5)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_time_offset_of_first_event_id, "add_offset", NC_FLOAT, 1, add_offset_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_time_offset_of_first_event_id, "units", 37, "seconds since 2019-09-26 23:59:40.000");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_time_offset_of_first_event_id, "axis", 1, "T");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_time_offset_of_last_event_id, "long_name", 82, "GLM L2+ Lightning Detection: time of occurrence of last constituent event in flash");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_time_offset_of_last_event_id, "standard_name", 4, "time");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_time_offset_of_last_event_id, "_Unsigned", 4, "true");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float scale_factor_att[1] = {((float)0.00038147561)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_time_offset_of_last_event_id, "scale_factor", NC_FLOAT, 1, scale_factor_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float add_offset_att[1] = {((float)-5)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_time_offset_of_last_event_id, "add_offset", NC_FLOAT, 1, add_offset_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_time_offset_of_last_event_id, "units", 37, "seconds since 2019-09-26 23:59:40.000");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_frame_time_offset_of_first_event_id, "long_name", 83, "GLM L2+ Lightning Detection: time of occurrence of first constituent event in flash");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_frame_time_offset_of_first_event_id, "standard_name", 4, "time");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_frame_time_offset_of_first_event_id, "_Unsigned", 4, "true");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float scale_factor_att[1] = {((float)0.00038147561)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_frame_time_offset_of_first_event_id, "scale_factor", NC_FLOAT, 1, scale_factor_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float add_offset_att[1] = {((float)-5)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_frame_time_offset_of_first_event_id, "add_offset", NC_FLOAT, 1, add_offset_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_frame_time_offset_of_first_event_id, "units", 37, "seconds since 2019-09-26 23:59:40.000");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_frame_time_offset_of_first_event_id, "axis", 1, "T");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_frame_time_offset_of_last_event_id, "long_name", 82, "GLM L2+ Lightning Detection: time of occurrence of last constituent event in flash");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_frame_time_offset_of_last_event_id, "standard_name", 4, "time");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_frame_time_offset_of_last_event_id, "_Unsigned", 4, "true");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float scale_factor_att[1] = {((float)0.00038147561)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_frame_time_offset_of_last_event_id, "scale_factor", NC_FLOAT, 1, scale_factor_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float add_offset_att[1] = {((float)-5)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_frame_time_offset_of_last_event_id, "add_offset", NC_FLOAT, 1, add_offset_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_frame_time_offset_of_last_event_id, "units", 37, "seconds since 2019-09-26 23:59:40.000");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_lat_id, "long_name", 124, "GLM L2+ Lightning Detection: flash centroid (mean constituent event latitude weighted by their energies) latitude coordinate");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_lat_id, "standard_name", 8, "latitude");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_lat_id, "units", 13, "degrees_north");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_lat_id, "axis", 1, "Y");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_lon_id, "long_name", 125, "GLM L2+ Lightning Detection: flash centroid (mean constituent event latitude weighted by their energies) longitude coordinate");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_lon_id, "standard_name", 9, "longitude");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_lon_id, "units", 12, "degrees_east");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_lon_id, "axis", 1, "X");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const short _FillValue_att[1] = {-1} ;
    stat = nc_put_att_short(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_area_id, "_FillValue", NC_SHORT, 1, _FillValue_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_area_id, "long_name", 104, "GLM L2+ Lightning Detection: flash area coverage (pixels containing at least one constituent event only)");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_area_id, "_Unsigned", 4, "true");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const short valid_range_att[2] = {0, -6} ;
    stat = nc_put_att_short(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_area_id, "valid_range", NC_SHORT, 2, valid_range_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float scale_factor_att[1] = {((float)152601.91)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_area_id, "scale_factor", NC_FLOAT, 1, scale_factor_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float add_offset_att[1] = {((float)0)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_area_id, "add_offset", NC_FLOAT, 1, add_offset_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_area_id, "units", 2, "m2");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_area_id, "coordinates", 157, "group_parent_flash_id flash_id lightning_wavelength flash_time_threshold flash_time_offset_of_first_event flash_time_offset_of_last_event flash_lat flash_lon");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_area_id, "grid_mapping", 23, "goes_lat_lon_projection");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_area_id, "cell_methods", 256, "lightning_wavelength: sum flash_time_offset_of_first_event: flash_time_offset_of_last_event: sum area: sum (interval: 8 km comment: resolution of sensor data at nadir, area of constituent groups' areas defined by variable group_parent_flash_id) where cloud");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const short _FillValue_att[1] = {-1} ;
    stat = nc_put_att_short(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_energy_id, "_FillValue", NC_SHORT, 1, _FillValue_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_energy_id, "long_name", 49, "GLM L2+ Lightning Detection: flash radiant energy");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_energy_id, "standard_name", 24, "lightning_radiant_energy");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_energy_id, "_Unsigned", 4, "true");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const short valid_range_att[2] = {0, -6} ;
    stat = nc_put_att_short(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_energy_id, "valid_range", NC_SHORT, 2, valid_range_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float scale_factor_att[1] = {((float)1.52597e-15)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_energy_id, "scale_factor", NC_FLOAT, 1, scale_factor_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float add_offset_att[1] = {((float)0)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_energy_id, "add_offset", NC_FLOAT, 1, add_offset_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_energy_id, "units", 1, "J");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_energy_id, "coordinates", 157, "group_parent_flash_id flash_id lightning_wavelength flash_time_threshold flash_time_offset_of_first_event flash_time_offset_of_last_event flash_lat flash_lon");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_energy_id, "grid_mapping", 23, "goes_lat_lon_projection");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_energy_id, "cell_measures", 16, "area: flash_area");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_energy_id, "cell_methods", 265, "lightning_wavelength: sum flash_time_offset_of_first_event: flash_time_offset_of_last_event: sum area: mean (centroid location of constituent events defined by variables group_parent_flash_id and event_parent_group_id weighted by their radiant energies) where cloud");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_energy_id, "ancillary_variables", 18, "flash_quality_flag");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const short _FillValue_att[1] = {-1} ;
    stat = nc_put_att_short(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_quality_flag_id, "_FillValue", NC_SHORT, 1, _FillValue_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_quality_flag_id, "long_name", 53, "GLM L2+ Lightning Detection: flash data quality flags");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_quality_flag_id, "standard_name", 11, "status_flag");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_quality_flag_id, "_Unsigned", 4, "true");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const short valid_range_att[2] = {0, 5} ;
    stat = nc_put_att_short(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_quality_flag_id, "valid_range", NC_SHORT, 2, valid_range_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_quality_flag_id, "units", 1, "1");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_quality_flag_id, "coordinates", 135, "flash_id lightning_wavelength flash_time_threshold flash_time_offset_of_first_event flash_time_offset_of_last_event flash_lat flash_lon");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_quality_flag_id, "grid_mapping", 23, "goes_lat_lon_projection");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_quality_flag_id, "cell_methods", 265, "lightning_wavelength: sum flash_time_offset_of_first_event: flash_time_offset_of_last_event: sum area: mean (centroid location of constituent events defined by variables group_parent_flash_id and event_parent_group_id weighted by their radiant energies) where cloud");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const short flag_values_att[4] = {0, 1, 3, 5} ;
    stat = nc_put_att_short(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_quality_flag_id, "flag_values", NC_SHORT, 4, flag_values_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_quality_flag_id, "flag_meanings", 196, "good_quality_qf degraded_due_to_flash_constituent_events_out_of_time_order_qf degraded_due_to_flash_constituent_event_count_exceeds_threshold_qf degraded_due_to_flash_duration_exceeds_threshold_qf");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const signed char number_of_qf_values_att[1] = {4} ;
    stat = nc_put_att_schar(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_quality_flag_id, "number_of_qf_values", NC_BYTE, 1, number_of_qf_values_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float percent_good_quality_qf_att[1] = {((float)1)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_quality_flag_id, "percent_good_quality_qf", NC_FLOAT, 1, percent_good_quality_qf_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float percent_degraded_due_to_flash_constituent_events_out_of_time_order_qf_att[1] = {((float)0)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_quality_flag_id, "percent_degraded_due_to_flash_constituent_events_out_of_time_order_qf", NC_FLOAT, 1, percent_degraded_due_to_flash_constituent_events_out_of_time_order_qf_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float percent_degraded_due_to_flash_constituent_event_count_exceeds_threshold_qf_att[1] = {((float)0)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_quality_flag_id, "percent_degraded_due_to_flash_constituent_event_count_exceeds_threshold_qf", NC_FLOAT, 1, percent_degraded_due_to_flash_constituent_event_count_exceeds_threshold_qf_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float percent_degraded_due_to_flash_duration_exceeds_threshold_qf_att[1] = {((float)0)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_quality_flag_id, "percent_degraded_due_to_flash_duration_exceeds_threshold_qf", NC_FLOAT, 1, percent_degraded_due_to_flash_duration_exceeds_threshold_qf_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, product_time_id, "long_name", 50, "start time of observations associated with product");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, product_time_id, "standard_name", 4, "time");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, product_time_id, "units", 33, "seconds since 2000-01-01 12:00:00");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, product_time_id, "axis", 1, "T");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, product_time_id, "bounds", 19, "product_time_bounds");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, product_time_bounds_id, "long_name", 58, "start and end time of observations associated with product");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, lightning_wavelength_id, "long_name", 37, "central wavelength for lightning data");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, lightning_wavelength_id, "standard_name", 40, "sensor_band_central_radiation_wavelength");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, lightning_wavelength_id, "units", 2, "nm");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, lightning_wavelength_id, "bounds", 27, "lightning_wavelength_bounds");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, lightning_wavelength_bounds_id, "long_name", 89, "wavelength range lightning data (full width at half the maximum of the response function)");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_time_threshold_id, "long_name", 73, "lightning group maximum time difference among lightning events in a group");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_time_threshold_id, "units", 1, "s");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_time_threshold_id, "long_name", 73, "lightning flash maximum time difference among lightning events in a flash");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_time_threshold_id, "units", 1, "s");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, lat_field_of_view_id, "long_name", 47, "latitude coordinate for center of field of view");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, lat_field_of_view_id, "standard_name", 8, "latitude");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, lat_field_of_view_id, "units", 13, "degrees_north");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, lat_field_of_view_id, "axis", 1, "Y");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, lat_field_of_view_id, "bounds", 24, "lat_field_of_view_bounds");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, lat_field_of_view_bounds_id, "long_name", 60, "latitude coordinates for north/south extent of field of view");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, goes_lat_lon_projection_id, "long_name", 38, "GOES-R latitude / longitude projection");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, goes_lat_lon_projection_id, "grid_mapping_name", 18, "latitude_longitude");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const double semi_major_axis_att[1] = {((double)6378137)} ;
    stat = nc_put_att_double(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, goes_lat_lon_projection_id, "semi_major_axis", NC_DOUBLE, 1, semi_major_axis_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const double semi_minor_axis_att[1] = {((double)6356752.31414)} ;
    stat = nc_put_att_double(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, goes_lat_lon_projection_id, "semi_minor_axis", NC_DOUBLE, 1, semi_minor_axis_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const double inverse_flattening_att[1] = {((double)298.2572221)} ;
    stat = nc_put_att_double(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, goes_lat_lon_projection_id, "inverse_flattening", NC_DOUBLE, 1, inverse_flattening_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const double longitude_of_prime_meridian_att[1] = {((double)0)} ;
    stat = nc_put_att_double(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, goes_lat_lon_projection_id, "longitude_of_prime_meridian", NC_DOUBLE, 1, longitude_of_prime_meridian_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_count_id, "long_name", 37, "number of lightning events in product");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const int _FillValue_att[1] = {-1} ;
    stat = nc_put_att_int(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_count_id, "_FillValue", NC_INT, 1, _FillValue_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const int valid_range_att[2] = {1, 630000} ;
    stat = nc_put_att_int(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_count_id, "valid_range", NC_INT, 2, valid_range_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_count_id, "units", 5, "count");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_count_id, "coordinates", 69, "lightning_wavelength product_time lat_field_of_view lon_field_of_view");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_count_id, "grid_mapping", 23, "goes_lat_lon_projection");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, event_count_id, "cell_methods", 88, "lightning_wavelength: sum product_time: sum area: sum (filtered events only) where cloud");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_count_id, "long_name", 37, "number of lightning groups in product");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const int _FillValue_att[1] = {-1} ;
    stat = nc_put_att_int(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_count_id, "_FillValue", NC_INT, 1, _FillValue_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const int valid_range_att[2] = {1, 630000} ;
    stat = nc_put_att_int(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_count_id, "valid_range", NC_INT, 2, valid_range_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_count_id, "units", 5, "count");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_count_id, "coordinates", 69, "lightning_wavelength product_time lat_field_of_view lon_field_of_view");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_count_id, "grid_mapping", 23, "goes_lat_lon_projection");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, group_count_id, "cell_methods", 65, "lightning_wavelength: sum product_time: sum area: sum where cloud");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_count_id, "long_name", 38, "number of lightning flashes in product");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const int _FillValue_att[1] = {-1} ;
    stat = nc_put_att_int(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_count_id, "_FillValue", NC_INT, 1, _FillValue_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const int valid_range_att[2] = {1, 630000} ;
    stat = nc_put_att_int(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_count_id, "valid_range", NC_INT, 2, valid_range_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_count_id, "units", 5, "count");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_count_id, "coordinates", 69, "lightning_wavelength product_time lat_field_of_view lon_field_of_view");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_count_id, "grid_mapping", 23, "goes_lat_lon_projection");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, flash_count_id, "cell_methods", 65, "lightning_wavelength: sum product_time: sum area: sum where cloud");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, percent_navigated_L1b_events_id, "long_name", 80, "after false event filtering, percent of lightning events navigated by instrument");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float _FillValue_att[1] = {((float)-999)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, percent_navigated_L1b_events_id, "_FillValue", NC_FLOAT, 1, _FillValue_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float valid_range_att[2] = {((float)0), ((float)1)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, percent_navigated_L1b_events_id, "valid_range", NC_FLOAT, 2, valid_range_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, percent_navigated_L1b_events_id, "units", 7, "percent");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, percent_navigated_L1b_events_id, "coordinates", 69, "lightning_wavelength product_time lat_field_of_view lon_field_of_view");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, percent_navigated_L1b_events_id, "grid_mapping", 23, "goes_lat_lon_projection");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, percent_navigated_L1b_events_id, "cell_methods", 126, "lightning_wavelength: sum product_time: sum area: sum (filtered, and filtered and navigated lightning events only) where cloud");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, yaw_flip_flag_id, "long_name", 65, "Flag indicating spacecraft is operating in yaw flip configuration");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, yaw_flip_flag_id, "_Unsigned", 4, "true");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const signed char _FillValue_att[1] = {-1} ;
    stat = nc_put_att_schar(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, yaw_flip_flag_id, "_FillValue", NC_BYTE, 1, _FillValue_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const signed char valid_range_att[2] = {0, 2} ;
    stat = nc_put_att_schar(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, yaw_flip_flag_id, "valid_range", NC_BYTE, 2, valid_range_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, yaw_flip_flag_id, "units", 1, "1");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, yaw_flip_flag_id, "coordinates", 12, "product_time");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, yaw_flip_flag_id, "cell_methods", 17, "product_time: sum");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const signed char flag_values_att[3] = {0, 1, 2} ;
    stat = nc_put_att_schar(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, yaw_flip_flag_id, "flag_values", NC_BYTE, 3, flag_values_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, yaw_flip_flag_id, "flag_meanings", 24, "upright neither inverted");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, nominal_satellite_subpoint_lat_id, "units", 13, "degrees_north");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, nominal_satellite_subpoint_lat_id, "long_name", 55, "nominal satellite subpoint latitude (platform latitude)");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, nominal_satellite_subpoint_lat_id, "standard_name", 8, "latitude");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float _FillValue_att[1] = {((float)-999)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, nominal_satellite_subpoint_lat_id, "_FillValue", NC_FLOAT, 1, _FillValue_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, nominal_satellite_height_id, "units", 2, "km");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, nominal_satellite_height_id, "long_name", 67, "nominal satellite height above GRS 80 ellipsoid (platform altitude)");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, nominal_satellite_height_id, "standard_name", 32, "height_above_reference_ellipsoid");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float _FillValue_att[1] = {((float)-999)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, nominal_satellite_height_id, "_FillValue", NC_FLOAT, 1, _FillValue_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, nominal_satellite_subpoint_lon_id, "units", 12, "degrees_east");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, nominal_satellite_subpoint_lon_id, "long_name", 57, "nominal satellite subpoint longitude (platform longitude)");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, nominal_satellite_subpoint_lon_id, "standard_name", 9, "longitude");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float _FillValue_att[1] = {((float)-999)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, nominal_satellite_subpoint_lon_id, "_FillValue", NC_FLOAT, 1, _FillValue_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, lon_field_of_view_id, "long_name", 48, "longitude coordinate for center of field of view");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, lon_field_of_view_id, "standard_name", 9, "longitude");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, lon_field_of_view_id, "units", 12, "degrees_east");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, lon_field_of_view_id, "axis", 1, "X");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, lon_field_of_view_id, "bounds", 24, "lon_field_of_view_bounds");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, lon_field_of_view_bounds_id, "long_name", 59, "longitude coordinates for west/east extent of field of view");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, percent_uncorrectable_L0_errors_id, "long_name", 48, "percent data lost due to uncorrectable L0 errors");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float _FillValue_att[1] = {((float)-999)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, percent_uncorrectable_L0_errors_id, "_FillValue", NC_FLOAT, 1, _FillValue_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    static const float valid_range_att[2] = {((float)0), ((float)1)} ;
    stat = nc_put_att_float(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, percent_uncorrectable_L0_errors_id, "valid_range", NC_FLOAT, 2, valid_range_att);
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, percent_uncorrectable_L0_errors_id, "units", 7, "percent");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, percent_uncorrectable_L0_errors_id, "coordinates", 48, "product_time lat_field_of_view lon_field_of_view");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, percent_uncorrectable_L0_errors_id, "grid_mapping", 23, "goes_lat_lon_projection");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, percent_uncorrectable_L0_errors_id, "cell_methods", 58, "product_time: sum area: sum (uncorrectable L0 errors only)");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, algorithm_dynamic_input_data_container_id, "long_name", 55, "container for filenames of dynamic algorithm input data");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, algorithm_dynamic_input_data_container_id, "input_GLM_L0_data", 51, "OR_GLM-L0_G17_s20192692359400_e20192700000000_c*.nc");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, algorithm_dynamic_input_data_container_id, "input_GLM_L1b_data", 4, "null");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, processing_parm_version_container_id, "long_name", 44, "container for processing parameter filenames");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, processing_parm_version_container_id, "L1b_processing_parm_version", 27, "OR-PARM-LCFA_G17_v01r00.zip");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, algorithm_product_version_container_id, "long_name", 60, "container for algorithm package filename and product version");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, algorithm_product_version_container_id, "algorithm_version", 29, "OR_GLM-L2-ALG-LCFA_v01r00.zip");
    check_err(stat,__LINE__,__FILE__);
    }

    {
    stat = nc_put_att_text(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp, algorithm_product_version_container_id, "product_version", 6, "v01r00");
    check_err(stat,__LINE__,__FILE__);
    }


    /* leave define mode */
    stat = nc_enddef (OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp);
    check_err(stat,__LINE__,__FILE__);

    /* assign variable data */

    stat = nc_close(OR_GLM_MINUS_L2_MINUS_LCFA_G17_s20192692359400_e20192700000000_c20192700000028_grp);
    check_err(stat,__LINE__,__FILE__);
    return 0;
}
