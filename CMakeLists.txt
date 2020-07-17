cmake_minimum_required(VERSION 3.16)
project(tlpi C)

set(CMAKE_C_STANDARD 99)

add_executable(tlpi copy.c seek_io.c lib/error_functions.c lib/get_num.c tee.c copy_w_holes.c ch5_2.c atomic_append.c tlpi.c v_dups.c v_dups.h)