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

COMPONENT_NAME= xf86-video-radeonhd
COMPONENT_VERSION= 1.3.0
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= xf86-video-radeonhd - ATI Radeon HD video driver for the Xorg X server
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:5adad675e60e973f2e3522a01457d9214157fbb5005090fe48092e6e5e698ad5
COMPONENT_ARCHIVE_URL= \
  http://xorg.freedesktop.org/archive/individual/driver/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://xorg.freedesktop.org

include $(WS_TOP)/make-rules/prep.mk

CONFIGURE_DEFAULT_DIRS = no

include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_PREP_ACTION =        ( cd $(@D) && \
					aclocal -I. && \
					autoheader && \
					libtoolize --automake --copy --force && \
					automake -a -f -c &&\
					autoconf )

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

CPPFLAGS += -DXF86DRI

CONFIGURE_OPTIONS += --with-xorg-module-dir=$(X11_SERVERMODS_DIR)$(SERVERMOD_SUBDIR)

CONFIGURE_ENV += CPPFLAGS=$(CPPFLAGS)

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)
