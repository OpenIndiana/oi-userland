#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2015 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= mesa
COMPONENT_VERSION= 7.4.4
COMPONENT_SUMMARY= The Mesa 3-D Graphics Library
COMPONENT_SRC= Mesa-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= MesaLib-$(COMPONENT_VERSION).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:eaf73d7a3a2dc959ddc0753abaa18160c64bec00b35bf4a0c96040b2072918ec
COMPONENT_ARCHIVE_URL= \
  http://sourceforge.net/projects/mesa3d/files/MesaLib/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_PROJECT_URL = http://www.mesa3d.org/

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATCH_LEVEL=0

ARCHLIBSUBDIR.64=/$(MACH64)
ARCHLIBSUBDIR=$(ARCHLIBSUBDIR.$(BITS))

SERVERMOD_SUBDIR.64=/$(MACH64)
SERVERMOD_SUBDIR=$(SERVERMOD_SUBDIR.$(BITS))
X11_SERVERMODS_DIR=/usr/lib/xorg/modules
X11_SERVERLIBS_DIR=/usr/lib/xorg

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =        (cp -a $(SOURCE_DIR)/* $(@D) && cp -r $(COMPONENT_DIR)/srcs/* $(@D))

# Add include paths and linker paths needed for DRM modules
CPPFLAGS = -I/usr/X11/include/drm

LDFLAGS= -L$(PROTODIR)$(X11_SERVERLIBS_DIR)$(ARCHLIBSUBDIR) \
                -R$(X11_SERVERLIBS_DIR)$(ARCHLIBSUBDIR) 

DRI_DRIVER_LIST=i915 i965 r200 r300 radeon swrast

# Command line options to GNU autoconf configure script
CONFIGURE_OPTIONS += --with-dri-driverdir='$(X11_SERVERMODS_DIR)/dri$(SERVERMOD_SUBDIR)'
CONFIGURE_OPTIONS += --with-driver=dri
CONFIGURE_OPTIONS += --with-dri-drivers='$(DRI_DRIVER_LIST)'

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)
