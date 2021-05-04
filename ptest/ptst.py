# This is a test program for the ncglm python wrappers.

# Maximilian McClelland 1/29/21

# This works on my local machine but seemed not to on Ed's. Need to figure out why that is.
import psrc.ncglm
import time

EPSILON = 0.0001
NUM_VAL = 5
NC_MAX_INT = 2147483647


class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'


def main():
    print("\n\nTestingPythonWrapper\n")
    print(f"{bcolors.OKGREEN}Testing GLM event reads.{bcolors.ENDC}")
    glm_event()
    print(f"{bcolors.OKGREEN}Testing GLM flash reads.{bcolors.ENDC}")
    glm_flash()
    print(f"{bcolors.OKGREEN}Testing GLM group reads.{bcolors.ENDC}")
    glm_group()


def glm_event():
    global EPSILON
    global NUM_VAL
    total_err = 0
    err = 0
    print(f"{bcolors.WARNING}testing GLM event reads...{bcolors.ENDC}")
    x_time = [-0.475699, -0.475699, -0.444037, -0.332646, -0.330739]
    x_lat = [23.9904, 23.9945, 23.9904, 23.9904, 23.9904]
    x_lon = [-105.711212, -105.619804, -105.711212, -105.711212, -105.711212]
    x_energy = [1.37337e-14, 7.62985e-15, 3.05194e-15, 4.57791e-15, 4.57791e-15]
    x_parent_group_id = [467109464, 467109464, 467109465, 467109472, 467109473]

    i = 0
    ret = 0


def glm_flash():
    print(f"{bcolors.WARNING}testing GLM flash reads...{bcolors.ENDC}")
    total_err = 0
    err = 0
    ncid = 0
    ret = 0


def glm_read():
    global NC_MAX_INT
    print("Reading Geostationary Lightning Mapper data")
    c = 0
    verbose = 0
    timing = 0
    meta_read_us = 0
    meta_max_read_us = 0
    meta_min_read_us = NC_MAX_INT
    meta_tot_read_us = 0
    meta_avg_read_us = 0
    num_trials = 1
    t = 0


def glm_group():
    print(f"{bcolors.WARNING}testing GLM group reads...{bcolors.ENDC}")


def are_same(a, b):
    if fabs(a - b) < EPSILON:
        return 1
    else:
        return 0


def fabs(equation):
    return equation


def print_time(offset):
    print(time.asctime(time.localtime(time.time() + offset)))


def show_att(ncid, varid, name):
    value = ""

    ret = 0
    return 0


main()
