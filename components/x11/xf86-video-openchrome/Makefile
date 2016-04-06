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

COMPONENT_NAME= xf86-video-openchrome
COMPONENT_VERSION= 0.3.3
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= xf86-video-openchrome - OpenChrome driver for the Xorg X server
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:e49e2f1e5dac86408e5a74b87038cc4082d2c3fba4e0579823161991432412ed
COMPONENT_ARCHIVE_URL= \
  http://xorg.freedesktop.org/archive/individual/driver/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://xorg.freedesktop.org
COMPONENT_CLASSIFICATION= Drivers/Display
COMPONENT_LICENSE = MIT
COMPONENT_LICENSE_FILE = COPYING
COMPONENT_FMRI = x11/server/xorg/driver/xorg-video-openchrome

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
MESA_XSERVERMODS_DIR=/usr/lib/mesa/modules
X11_SERVERLIBS_DIR=/usr/lib/xorg

# Instead of allowing the default MODTYPE_LD_SHARED_OPTIONS to link all
# the libraries against the Xorg server binary, ldflags.patch adds
# $(openchrome_drv_la_LDFLAGS_add) to the link of just openchrome_drv.so,
# but not to the client side XvMC libs.
openchrome_drv_la_LDFLAGS_add = \
        -L$(X11_SERVERMODS_DIR)$(SERVERMOD_SUBDIR) \
        -L$(X11_SERVERLIBS_DIR)$(SERVERMOD_SUBDIR) \
        -R$(X11_SERVERMODS_DIR)$(SERVERMOD_SUBDIR) \
        -R$(X11_SERVERLIBS_DIR)$(SERVERMOD_SUBDIR) \
        -Wl,-M$(COMPONENT_DIR)/mapfile.externs \
        -lfb -lint10 -lpciaccess -lpixman-1 -lvbe \
        -lexa -lvgahw -lm -ldrm -lshadow

COMPONENT_BUILD_ENV += \
        openchrome_drv_la_LDFLAGS_add='$(openchrome_drv_la_LDFLAGS_add)'

# this is needed to set path for XvMC libraries
CONFIGURE_LIBDIR.$(BITS) =   $(X11_SERVERLIBS_DIR)$(SERVERMOD_SUBDIR)

CONFIGURE_OPTIONS += --disable-dri
CONFIGURE_OPTIONS += --disable-kms

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)
