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

BUILD_BITS = 32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= xf86-video-openchrome
COMPONENT_VERSION= 0.6.0
COMPONENT_REVISION= 2
COMPONENT_SUMMARY= xf86-video-openchrome - OpenChrome driver for the Xorg X server
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:da2975c6379358de52c1257710c67eb59139a7f0a1cd28d00cc64cc3e1c02f75
COMPONENT_ARCHIVE_URL= \
  http://xorg.freedesktop.org/archive/individual/driver/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://xorg.freedesktop.org
COMPONENT_CLASSIFICATION= Drivers/Display
COMPONENT_LICENSE = MIT
COMPONENT_LICENSE_FILE = COPYING
COMPONENT_FMRI = x11/server/xorg/driver/xorg-video-openchrome

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
# Disable as 32bit module is not installed in the right directory. 
#CONFIGURE_LIBDIR.$(BITS) =   $(X11_SERVERLIBS_DIR)$(SERVERMOD_SUBDIR)

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
