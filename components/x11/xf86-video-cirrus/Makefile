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
# Copyright 2017 Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= xf86-video-cirrus
COMPONENT_VERSION= 1.5.3
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= xf86-video-cirrus - Cirrus Logic video driver for the Xorg X server
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:edc87b20a55259126b5239b5c1ef913419eab7ded0ed12ae9ae989460d7351ab
COMPONENT_ARCHIVE_URL= \
  http://xorg.freedesktop.org/archive/individual/driver/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://xorg.freedesktop.org
COMPONENT_CLASSIFICATION= Drivers/Display
COMPONENT_LICENSE = MIT
COMPONENT_LICENSE_FILE = COPYING
COMPONENT_FMRI = x11/server/xorg/driver/xorg-video-cirrus

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
        -L$(X11_SERVERLIBS_DIR)$(SERVERMOD_SUBDIR) \
        -R$(X11_SERVERMODS_DIR)$(SERVERMOD_SUBDIR) \
        -R$(X11_SERVERLIBS_DIR)$(SERVERMOD_SUBDIR)

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

REQUIRED_PACKAGES += developer/build/autoconf/xorg-macros
REQUIRED_PACKAGES += developer/build/pkg-config
REQUIRED_PACKAGES += x11/server/xorg
REQUIRED_PACKAGES += x11/header/fontsproto
REQUIRED_PACKAGES += x11/header/randrproto
REQUIRED_PACKAGES += x11/header/renderproto
REQUIRED_PACKAGES += x11/header/videoproto
REQUIRED_PACKAGES += x11/header/xextproto
REQUIRED_PACKAGES += x11/header/xproto
REQUIRED_PACKAGES += diagnostic/scanpci
