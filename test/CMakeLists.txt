# This is the cmake build file for the test directory of the ncglm library.
#
# Ed Hartnett 11/10/19

enable_testing()
add_test(NAME tst_glm_read COMMAND tst_glm_read)
build_test(tst_glm_read)
add_sh_test(nc_test4 run_glm_tests)

# add the executable
#add_executable(Tutorial tutorial.cxx)
