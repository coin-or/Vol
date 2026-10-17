# Copyright (C) 2006 International Business Machines and others.
# All Rights Reserved.
# This file is distributed under the Eclipse Public License.

include $(top_srcdir)/BuildTools/Makemain.inc

########################################################################
#                         unitTest for OsiVol                          #
########################################################################

if COIN_HAS_OSITESTS

noinst_PROGRAMS = osiUnitTest

osiUnitTest_SOURCES = osiUnitTest.cpp OsiVolSolverInterfaceTest.cpp

osiUnitTest_LDADD = ../src/OsiVol/libOsiVol.la ../src/libVol.la \
	$(OSIVOLUNITTEST_LFLAGS)

AM_CPPFLAGS = -I$(srcdir)/../src -I$(srcdir)/../src/OsiVol \
	-I../src -I../src/OsiVol $(OSIVOLUNITTEST_CFLAGS)
AM_LDFLAGS = $(LT_LDFLAGS)

osiunittestflags =
if COIN_HAS_SAMPLE
  osiunittestflags += -mpsDir=`$(CYGPATH_W) $(SAMPLE_DATA)`
endif

test: osiUnitTest$(EXEEXT)
	./osiUnitTest$(EXEEXT) $(osiunittestflags)

else

test:
	@echo "********************* No test for Vol implemented *************************"

endif

.PHONY: test

DISTCLEANFILES = yy.mps xx.mps
