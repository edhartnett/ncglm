# This is an automake file for the Using NetCDF sample code for the
# Geostationary Lightning Mapper (GLM).

# Ed Hartnett 10/10/2019
# Amsterdam

# Find the include files.
AM_CPPFLAGS = -I$(top_srcdir)/include

# This is a libtool library.
lib_LTLIBRARIES = libncglm.la
libncglm_la_LDFLAGS = -version-info 0:0:0
libncglm_la_SOURCES = glm_read.c glm_event.c glm_group.c glm_flash.c

# Include cmake build system.
EXTRA_DIST = CMakeLists.txt
