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

COMPONENT_NAME= xf86-video-mga
COMPONENT_VERSION= 1.6.4
COMPONENT_SUMMARY= xf86-video-mga - Matrox MGA driver for the Xorg X server
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:48c6690b6751c76f53de64f8dbeaa9d6c62dbcfe890c768fd87167951247d44f
COMPONENT_ARCHIVE_URL= \
  http://xorg.freedesktop.org/archive/individual/driver/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://xorg.freedesktop.org
COMPONENT_CLASSIFICATION= Drivers/Display
COMPONENT_LICENSE = MIT
COMPONENT_LICENSE_FILE = COPYING
COMPONENT_FMRI = x11/server/xorg/driver/xorg-video-mga

include $(WS_MAKE_RULES)/prep.mk

include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

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

# Extra flags to link mga_drv.so, but not util/stormdwg binary with
DRIVER_LD_FLAGS = \
        -L$(X11_SERVERMODS_DIR)$(SERVERMOD_SUBDIR) \
        -R$(X11_SERVERMODS_DIR)$(SERVERMOD_SUBDIR)

# - Disable DRI since the kernel module isn't ported
CONFIGURE_OPTIONS += --disable-dri

CONFIGURE_OPTIONS += XORG_LIBS="$(DRIVER_LD_FLAGS)"

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)
