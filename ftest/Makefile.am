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

# Link to our assembled libraries.
AM_LDFLAGS = ${top_builddir}/src/libncglm.la ${top_builddir}/fsrc/libncglmf.la
LDADD = ${top_builddir}/src/libncglm.la ${top_builddir}/fsrc/libncglmf.la

GLM_FTESTS = ftst_glm_read

# Build our test program.
check_PROGRAMS = ${GLM_FTESTS}

# Source code for the tests.
ftst_glm_read_SOURCES = ftst_glm_read.F90

# Run our test program.
TESTS = ${GLM_FTESTS}

# Make sure these files are included in distribution.
#EXTRA_DIST = CMakeLists.txt						\
#OR_GLM-L2-LCFA_G17_s20192692359400_e20192700000000_c20192700000028.nc

#CLEANFILES = ncdump2.nc
