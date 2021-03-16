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

# Does the user want the Fortran API?
if BUILD_FORTRAN
FSRC = fsrc
FTEST = ftest
endif

# Does the user want the Python API?
if BUILD_PYTHON
PSRC = psrc
PTEST = ptest
endif

SUBDIRS = cmake include src ${FSRC} test ${FTEST} ${DOCS} ${PSRC} ${PTEST}

EXTRA_DIST = test-driver-verbose LICENSE README.md CMakeLists.txt
