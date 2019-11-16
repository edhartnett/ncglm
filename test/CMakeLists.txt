# This is the cmake build file for the test directory of the ncglm library.
#
# Ed Hartnett 11/10/19

enable_testing()
include_directories(${NETCDF_INCLUDES})
include_directories(${CMAKE_SOURCE_DIR}/src)
link_directories(${CMAKE_SOURCE_DIR}/src)
add_executable(tst_glm_read tst_glm_read.c un_test.h tst_utils.c)
target_link_libraries(tst_glm_read PRIVATE ${NETCDF_LIBRARIES}/libnetcdf.so)
target_link_libraries(tst_glm_read PRIVATE ${CMAKE_BINARY_DIR}/src/libncglm.a)

# Copy some test files from current source dir to out-of-tree build dir.
#FILE(GLOB COPY_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.sh)
#FILE(COPY ${COPY_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

#add_sh_test(test run_glm_tests)
