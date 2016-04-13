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
# Copyright 2015 Ken Mays
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= xf86-video-vmware
COMPONENT_VERSION= 13.1.0
COMPONENT_SUMMARY= xf86-video-vmware - VMWare driver for the Xorg X server
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:3c1d244e4b1b77e92126957965cdc9fb82de4c215c0706a3a8aaff6939e4a0cc
COMPONENT_ARCHIVE_URL= \
  http://xorg.freedesktop.org/archive/individual/driver/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://xorg.freedesktop.org
COMPONENT_CLASSIFICATION= Drivers/Display
COMPONENT_LICENSE = MIT
COMPONENT_LICENSE_FILE = COPYING
COMPONENT_FMRI = x11/server/xorg/driver/xorg-video-vmware

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_PREP_ACTION =        ( cd $(@D) && \
                                        libtoolize --automake --copy --force && \
                                        aclocal && \
                                        autoheader && \
                                        automake -a -f -c &&\
                                        autoconf )

# Paths to find libraries/modules to link with 

SERVERMOD_SUBDIR.64=/$(MACH64)
SERVERMOD_SUBDIR=$(SERVERMOD_SUBDIR.$(BITS))
X11_SERVERMODS_DIR=/usr/lib/xorg/modules
X11_SERVERLIBS_DIR=/usr/lib/xorg

LD_OPTIONS= \
        -L$(X11_SERVERMODS_DIR)$(SERVERMOD_SUBDIR) \
        -R$(X11_SERVERMODS_DIR)$(SERVERMOD_SUBDIR) \
        -lfb -lpixman-1 -lshadowfb -lvgahw -lpciaccess

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)
