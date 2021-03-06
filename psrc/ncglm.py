# This is the Python wrapper for the ncglm library.

# Maximilian McClelland 1/29/21

import ctypes
import os

# Full path is necessiary for cytpes function.
temp = os.path.abspath(__file__)
temp = os.path.realpath(temp)
temp = os.path.dirname(temp)
end = len(temp) - 4
path = temp[:end] + "src"
lib = os.path.join(path, "libncglm.so")

# Checks that path is correct. Will also be removed later.
path = "\nPath: \n" + lib + "\n"

# Creating Libraries
try:
    lib_ncglm = ctypes.CDLL(lib)
except Exception as err:
    err = "Could not load NCGLM Library:\n" + str(err)
    print(err)
    exit()

# Specifying Functions
read_group_vars = lib_ncglm.read_group_vars
glm_read_group_structs = lib_ncglm.glm_read_group_structs
glm_read_group_arrays = lib_ncglm.glm_read_group_arrays

read_event_vars = lib_ncglm.read_event_vars
glm_read_event_structs = lib_ncglm.glm_read_event_structs
glm_read_event_arrays = lib_ncglm.glm_read_event_arrays

read_flash_vars = lib_ncglm.read_flash_vars
glm_read_flash_structs = lib_ncglm.glm_read_flash_structs
glm_read_flash_arrays = lib_ncglm.glm_read_flash_arrays

glm_read_dims = lib_ncglm.glm_read_dims
read_scalars = lib_ncglm.read_scalars
glm_read_file = lib_ncglm.glm_read_file
glm_read_file_arrays = lib_ncglm.glm_read_file_arrays

# Specify inputs
# read_group_vars.argtypes = [ctypes.c_int, ctypes.]

