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
# Copyright 2013 Alexander Pyhalov.  All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= gegl

COMPONENT_VERSION= 0.1.2
COMPONENT_SUMMARY= GEGL (Generic Graphics Library) is a graph based image processing framework
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:b64e619b460c4f4a746596b219d0bcb722068e3c4a00a30cc03201ca2118e113
COMPONENT_ARCHIVE_URL= \
  ftp://ftp.gimp.org/pub/gegl/0.1/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.gegl.org/

GEGLDOCDIR = $(PROTO_DIR)/usr/share/doc/$(COMPONENT_NAME)

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk


CONFIGURE_OPTIONS+= --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS+= --datadir=$(USRSHAREDIR)
CONFIGURE_OPTIONS+= --infodir=$(USRSHAREDIR)/info
CONFIGURE_OPTIONS+= --without-libspiro
CONFIGURE_OPTIONS+= --without-libavformat
CONFIGURE_OPTIONS+= --without-libv4l
CONFIGURE_OPTIONS+= --enable-workshop
CONFIGURE_OPTIONS+= --enable-mmx=no
CONFIGURE_OPTIONS+= --enable-sse=no

CONFIGURE_ENV.64 += SDL_CONFIG=/usr/bin/$(MACH64)/sdl-config

COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR)  -p $(GEGLDOCDIR) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP)  $(COMPONENT_SRC)/{AUTHORS,README,ChangeLog,COPYING,NEWS,COPYING.LESSER} $(GEGLDOCDIR) ;

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)
