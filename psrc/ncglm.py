# This is the Python wrapper for the ncglm library.

# Maximilian McClelland 1/29/21

import ctypes

#Creating Libraries
glm_group = ctypes.CDLL("../src/glm_group.so")
glm_event = ctypes.CDLL("../src/glm_event.so")
glm_read = ctypes.CDLL("../src/glmread_.so")
glm_flash = ctypes.CDLL("../src/glm_flash.so")

#Specifying Functions
read_group_vars = glm_group.read_group_vars
glm_read_group_structs = glm_group.glm_read_group_structs
glm_read_group_arrays = glm_group.glm_read_group_arrays

read_event_vars = glm_event.read_event_vars
glm_read_event_structs = glm_event.glm_read_event_structs
glm_read_event_arrays = glm_event.glm_read_event_arrays

read_flash_vars = glm_flash.read_flash_vars
glm_read_flash_structs = glm_flash.glm_read_flash_structs
glm_read_flash_arrays = glm_flash.glm_read_flash_arrays

glm_read_dims = glm_read.glm_read_dims
read_scalars = glm_read.read_scalars
glm_read_file = glm_read.glm_read_file
glm_read_file_arrays = glm_read.glm_read_file_arrays

#Specify inputs
# read_group_vars.argtypes = [ctypes.c_int, ctypes.]
