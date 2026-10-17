# Copyright (C) 2006 International Business Machines and others.
# All Rights Reserved.
# This file is distributed under the Eclipse Public License.

#############################################################################
#                       Names and other basic things                        #
#############################################################################

AC_INIT([Vol],[devel],[https://github.com/coin-or/Vol/issues/new],[coin-or-vol],[https://github.com/coin-or/Vol])

AC_COPYRIGHT([
Copyright 2006 International Business Machines and others.
All Rights Reserved.
This file is part of the open source package Coin which is distributed
under the Eclipse Public License.])

# List one file in the package so that the configure script can test
# whether the package is actually there
AC_CONFIG_SRCDIR(src/VolVolume.cpp)

# Do some initialization work (version numbers, change prefix default, ...)
AC_COIN_INITIALIZE

#############################################################################
#                         Standard build tool stuff                         #
#############################################################################

# Get the name of the C++ compiler and appropriate compiler options
AC_COIN_PROG_CXX

# This is a C++ package, set the language accordingly.
AC_LANG_PUSH(C++)

# Initialize libtool
AC_COIN_PROG_LIBTOOL

# set RPATH_FLAGS to the compiler link flags required to hardcode location
# of the shared objects (expanded_libdir is set somewhere in configure before)
# (used in the examples)
AC_COIN_RPATH_FLAGS([$expanded_libdir])

#############################################################################
#                              COIN-OR components                           #
#############################################################################

AC_COIN_CHK_PKG(CoinUtils,[VolLib OsiVolLib OsiVolUnitTest])
if test $coin_has_coinutils != yes ; then
  AC_MSG_ERROR([Required package CoinUtils not available.])
fi
AC_COIN_CHK_PKG(Osi,[OsiVolLib OsiVolUnitTest])
AC_COIN_CHK_PKG(OsiTests,[OsiVolUnitTest],[osi-unittests])
AC_COIN_CHK_PKG(Sample,,[coindatasample],[],dataonly)

##############################################################################
#                   VPATH links for example input files                      #
##############################################################################

# In case this is a VPATH configuration we need to make sure that the
# input files for the examples are available in the VPATH directory.

AC_COIN_VPATH_LINK(examples/VolUfl/ufl.par)
AC_COIN_VPATH_LINK(examples/VolUfl/data.gz)
AC_COIN_VPATH_LINK(examples/Volume-LP/data.mps.gz)
AC_COIN_VPATH_LINK(examples/Volume-LP/lp.par)

##############################################################################
#                   Finishing up by writing all the output                   #
##############################################################################

# Doxygen documentation
AC_COIN_DOXYGEN([CoinUtils Osi])

# Finalize libs and cflags.
AC_COIN_FINALIZE_FLAGS([VolLib OsiVolLib OsiVolUnitTest])

# OsiVol is built here, so it can't consult vol.pc to get Vol's flags
AC_COIN_CHK_HERE([VolLib],[OsiVolLib],[vol])

# Here list all the files that configure should create (except for the
# configuration header file)
AC_CONFIG_FILES([Makefile
                 examples/VolLp/Makefile
                 examples/VolUfl/Makefile
                 examples/Volume-LP/Makefile
                 src/Makefile
                 src/OsiVol/Makefile
                 test/Makefile
                 vol.pc])
if test $coin_has_osi = yes ; then
  AC_CONFIG_FILES([osi-vol.pc:src/OsiVol/osi-vol.pc.in])
fi

AC_CONFIG_FILES([doxydoc/doxygen.conf])

# Here put the location and name of the configuration header file
AC_CONFIG_HEADERS([src/config.h src/config_vol.h])
if test $coin_has_osi = yes ; then
  AC_CONFIG_HEADERS([src/OsiVol/config_osivol.h])
fi

# Finally, we let configure write all the output...
AC_COIN_FINALIZE
