# This is the cmake file for the src directory of the ncglm library.

# Ed Hartnett 11/10/19

# Build the ncglm library.
add_library(ncglm glm_read.c glm_event.c glm_group.c glm_flash.c goes_glm.h glm_data.h)
