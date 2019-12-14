# This is an automake file for the Fortran ncglm library.

# Ed Hartnett 12/14/2019

# Find the include files.
AM_CPPFLAGS = -I$(top_srcdir)/include

# This is a libtool library.
lib_LTLIBRARIES = libncglmf.la
libncglmf_la_LDFLAGS = -version-info 0:0:0

# Link to our assembled C library.
AM_LDFLAGS = ${top_builddir}/src/libncglm.la
#LDADD = ${top_builddir}/src/libncglm.la ${top_builddir}/fsrc/libncglmf.la

# Each convenience library depends on its source.
libncglmf_la_SOURCES = ncglm.F90

# Each mod file depends on the .o file.
ncglm.mod: ncglm.$(OBJEXT)

# Mod files are built and then installed as headers.
MODFILES = ncglm.mod
include_HEADERS = $(MODFILES)
BUILT_SOURCES = $(MODFILES)

CLEANFILES = *.mod
