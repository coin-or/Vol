# Static or shared libraries should be built (STATIC or SHARED)?
LibType := SHARED

# Select optimization (-O or -g). -O will be automatically bumped up to the 
# highest level of optimization the compiler supports. If want something in
# between then specify the exact level you want, e.g., -O1 or -O2
OptLevel := -O

LIBNAME := Vol
LIBSRC :=
LIBSRC += VolVolume.cpp

##############################################################################
# You should not need to edit below this line.
##############################################################################
# The location of the customized Makefiles
export MakefileDir := ../Common/make
include ${MakefileDir}/Makefile.coin
include ${MakefileDir}/Makefile.location

export ExtraIncDir := 
export ExtraLibDir := 
export ExtraLibName :=
export ExtraDefine := 

export LibType OptLevel LIBNAME LIBSRC

###############################################################################

.DELETE_ON_ERROR:

.PHONY: default install libosi library clean doc

default: install

install clean doc library: % :
	$(MAKE) -f ${MakefileDir}/Makefile.lib $*

libvol:
	$(MAKE) -f ${MakefileDir}/Makefile.lib library
