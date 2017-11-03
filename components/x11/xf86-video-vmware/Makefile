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
COMPONENT_VERSION= 13.2.1
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= xf86-video-vmware - VMWare driver for the Xorg X server
COMPONENT_PROJECT_URL = http://xorg.freedesktop.org
COMPONENT_FMRI = x11/server/xorg/driver/xorg-video-vmware
COMPONENT_CLASSIFICATION= Drivers/Display
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_URL= \
  http://xorg.freedesktop.org/archive/individual/driver/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
  sha256:e2f7f7101fba7f53b268e7a25908babbf155b3984fb5268b3d244eb6c11bf62b
COMPONENT_LICENSE = MIT
COMPONENT_LICENSE_FILE = COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION = ( cd $(@D) && \
                          libtoolize --automake --copy --force && \
                          aclocal && \
                          autoheader && \
                          automake -a -f -c && \
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

# Build dependencies
REQUIRED_PACKAGES += x11/header/xproto
REQUIRED_PACKAGES += x11/header/fontsproto
REQUIRED_PACKAGES += system/header/header-drm

# Auto-generated dependencies
REQUIRED_PACKAGES += diagnostic/scanpci
REQUIRED_PACKAGES += library/graphics/pixman
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/server/xorg
