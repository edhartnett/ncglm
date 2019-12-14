# This is an automake file for the Fortran ncglm library.

# Ed Hartnett 12/14/2019

# Find the include files.
AM_CPPFLAGS = -I$(top_srcdir)/include

# This is a libtool library.
lib_LTLIBRARIES = libncglmf.la
libncglmf_la_LDFLAGS = -version-info 0:0:0
libncglmf_la_SOURCES = ncglm.F90

# Include cmake build system.
#EXTRA_DIST = CMakeLists.txt
