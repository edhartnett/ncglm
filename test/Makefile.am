# This is an automake file for the Geostationary Lightning Mapper
# (GLM) test code.

# Ed Hartnett 10/10/2019
# Amsterdam

# Un comment to use a more verbose test driver
SH_LOG_DRIVER = $(SHELL) $(top_srcdir)/test-driver-verbose
LOG_DRIVER = $(SHELL) $(top_srcdir)/test-driver-verbose

TEST_EXTENSIONS = .sh

# Find the include files.
AM_CPPFLAGS = -I$(top_srcdir)/include

# Link to our assembled library.
AM_LDFLAGS = ${top_builddir}/src/libncglm.la
LDADD = ${top_builddir}/src/libncglm.la

GLM_TESTS = tst_glm_read tst_glm_read_arrays tst_glm_ncgen_write	\
tst_events tst_group tst_flash

# Build our test program.
check_PROGRAMS = ${GLM_TESTS}

# Source code for the tests.
tst_glm_read_SOURCES = tst_glm_read.c un_test.h tst_utils.c
tst_glm_read_arrays_SOURCES = tst_glm_read_arrays.c un_test.h tst_utils.c
tst_events_SOURCES = tst_events.c un_test.h
tst_group_SOURCES = tst_group.c un_test.h
tst_flash_SOURCES = tst_flash.c un_test.h

# Run our test program.
TESTS = ${GLM_TESTS}

# Make sure these files are included in distribution.
EXTRA_DIST = CMakeLists.txt						\
OR_GLM-L2-LCFA_G17_s20192692359400_e20192700000000_c20192700000028.nc

# Clean data files for distclean target.
DISTCLEANFILES = *.nc
