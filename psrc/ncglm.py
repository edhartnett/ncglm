# This is the Python wrapper for the ncglm library.

# Maximilian McClelland 1/29/21

import ctypes

#Creating Libraries
glm_group = ctypes.CDLL("../src/glm_group.so")

#Specifying Functions
read_group_vars = glm_group.read_group_vars

#Specify inputs
# read_group_vars.argtypes = [ctypes.c_int, ctypes.]
