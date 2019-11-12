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
# Copyright 2017 Aurelien Larcher
#

BUILD_BITS = 32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= xf86-video-vbox
# Use version string from Xorg module
COMPONENT_VERSION= 1.0.1
COMPONENT_REVISION= 2
COMPONENT_SUMMARY= xf86-video-vbox - VirtualBox UMS driver for the Xorg X server
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_GIT_HASH)
COMPONENT_ARCHIVE= $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.xz
COMPONENT_GIT_HASH=  ab07f97612d045d8c0a376174b39a294d028fef2
COMPONENT_ARCHIVE_HASH= \
  sha256:0b89efa6830fbf65b76482a98c06a95c027f49266725a7d4cf98e1a95b8e9467
COMPONENT_ARCHIVE_URL= \
  https://cgit.freedesktop.org/xorg/driver/xf86-video-vbox/snapshot/$(COMPONENT_NAME)-$(COMPONENT_GIT_HASH).tar.xz
COMPONENT_PROJECT_URL = http://xorg.freedesktop.org
COMPONENT_CLASSIFICATION= Drivers/Display
COMPONENT_LICENSE = MIT
COMPONENT_LICENSE_FILE = COPYING
COMPONENT_FMRI = x11/server/xorg/driver/xorg-video-vboxvideo

TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = ( cd $(@D) && \
                          libtoolize --automake --copy --force && \
                          aclocal && \
                          autoheader && \
                          automake -a -f -c && \
                          autoconf )

CFLAGS+= -std=gnu99

# Paths to find libraries/modules to link with

SERVERMOD_SUBDIR.64=/$(MACH64)
SERVERMOD_SUBDIR=$(SERVERMOD_SUBDIR.$(BITS))
X11_SERVERMODS_DIR=/usr/lib/xorg/modules
MESA_XSERVERMODS_DIR=/usr/lib/mesa/modules
X11_SERVERLIBS_DIR=/usr/lib/xorg

LD_OPTIONS+= \
	     -L$(X11_SERVERMODS_DIR)$(SERVERMOD_SUBDIR) \
	     -L$(MESA_XSERVERMODS_DIR)/extensions$(SERVERMOD_SUBDIR) \
	     -L$(X11_SERVERMODS_DIR)/extensions$(SERVERMOD_SUBDIR) \
	     -L$(X11_SERVERLIBS_DIR)$(ARCHLIBSUBDIR) \
	     -R$(X11_SERVERMODS_DIR)$(SERVERMOD_SUBDIR) \
	     -R$(MESA_XSERVERMODS_DIR)/extensions$(SERVERMOD_SUBDIR) \
	     -R$(X11_SERVERMODS_DIR)/extensions$(SERVERMOD_SUBDIR) \
	     -R$(X11_SERVERLIBS_DIR)$(SERVERMOD_SUBDIR)

CONFIGURE_OPTIONS+= --with-xorg-module-dir=$(X11_SERVERMODS_DIR)$(SERVERMOD_SUBDIR)

# Build dependencies
REQUIRED_PACKAGES += x11/header/x11-protocols
REQUIRED_PACKAGES += system/header/header-drm

# Auto-generated dependencies
REQUIRED_PACKAGES += diagnostic/scanpci
REQUIRED_PACKAGES += library/graphics/pixman
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libdrm
REQUIRED_PACKAGES += x11/server/xorg
