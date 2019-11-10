cmake_minimum_required(VERSION 3.10)

# set the project name
project(ncglm VERSION 1.0)

configure_file(config.h.cmake.in config.h)

add_subdirectory(src)

# add the executable
#add_executable(Tutorial tutorial.cxx)
