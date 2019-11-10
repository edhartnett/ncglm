# This is the main cmake file for ncglm, a library to help read the
# netCDF data files from the Global Lightning Mapper (GLM) instrument
# on GOES-16 and GOES-17.
#
# Ed Hartnett 11/10/19

cmake_minimum_required(VERSION 3.10)

# set the project name
project(ncglm VERSION 1.0)

#Add custom CMake Module
SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/"
  CACHE INTERNAL "Location of our custom CMake modules.")

# Find netCDF.
include(FindNetCDF)

include_directories("${NETCDF_INCLUDES}")

# Create a config.h.
configure_file(config.h.cmake.in config.h)

# Build in this subdirectory.
add_subdirectory(src)
