##############################################################################
# Edit the following options for your local environment:
##############################################################################

# Static or shared libraries should be built (STATIC or SHARED)?
LibType := SHARED

# Select optimization (-O or -g). -O will be automatically bumped up to the 
# highest level of optimization the compiler supports. If want something in
# between then specify the exact level you want, e.g., -O1 or -O2
OptLevel := -O

# The path to the root of the install directory structure.
# include files will be installed in ${InstallDir}/include, libraries in 
# ${InstallDir}/lib, executables in ${InstallDir}/bin.
InstallDir := ..

##############################################################################
# You should not need to edit below this line.
##############################################################################

# The location of the customized Makefiles
MakefileDir := ../Common/make

include ${MakefileDir}/Makefile.coin

###############################################################################

include ${MakefileDir}/Makefile.rules

##############################################################################

CXXFLAGS += $(OPTFLAG)
CXXFLAGS += -Iinclude

###############################################################################

space:= $(empty) $(empty)
OptVersion := $(subst $(space),_,$(OptLevel))

TARGETDIR := $(UNAME)$(OptVersion)
DEPDIR := dep

VPATH := . : include : Junk : ${TARGETDIR} : ${DEPDIR}

###############################################################################

LIBSRC := VolVolume.cpp
LIBOBJ := $(addprefix $(TARGETDIR)/, $(LIBSRC:.cpp=.o))
LIBDEP := $(addprefix $(DEPDIR)/, $(LIBSRC:.cpp=.d))

###############################################################################

.DELETE_ON_ERROR:

.PHONY: default install all libvol clean doc

default: install
all:     libvol

install: libvol
	@echo "Installing include files..."
	@mkdir -p ${InstallDir}/include
	@${CP} include/VolVolume.hpp ${InstallDir}/include
	@echo "Installing libraries..."
	@mkdir -p ${InstallDir}/lib
	@${CP} $(TARGETDIR)/libvol$(OptVersion)$(LIBEXT) ${InstallDir}/lib
	@rm -f ${InstallDir}/lib/libvol$(LIBEXT)
	@cd ${InstallDir}/lib; \
		ln -s libvol$(OptVersion)$(LIBEXT) libvol$(LIBEXT)

###############################################################################

libvol : $(TARGETDIR)/libvol$(OptVersion)$(LIBEXT)

$(TARGETDIR)/libvol$(OptVersion)$(LIBEXT): $(LIBOBJ)
	@rm -rf Junk
	@echo ""
	@echo Creating library $(notdir $@)
	@mkdir -p $(TARGETDIR)
	@rm -f $@
	$(LD) $@ $(LIBLDFLAGS) $(LIBOBJ)

###############################################################################

doc :
	doxygen $(MakefileDir)/doxygen.conf

clean : 
	rm -rf Junk
	rm -rf $(DEPDIR)
	rm -rf $(TARGETDIR)

###############################################################################

%::
	@mkdir -p Junk
	touch Junk/$(notdir $@)

###############################################################################

-include $(LIBDEP)
