# This is an automake file for the Using NetCDF sample code for the
# Geostationary Lightning Mapper.

# Ed Hartnett 10/10/2019
# Amsterdam

# This directory stores libtool macros, put there by aclocal.
ACLOCAL_AMFLAGS = -I m4

# Does the user want to build documentation?
if BUILD_DOCS
DOCS = docs
endif

SUBDIRS = cmake include src fsrc test ftest ${DOCS}

EXTRA_DIST = test-driver-verbose LICENSE README.md CMakeLists.txt
