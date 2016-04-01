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
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= gobject-introspection

COMPONENT_VERSION= 1.34.2
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= Introspection for GObject libraries
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:bc7948a35ce2218922dfb0806679cad21060715cc0c340cf7823eb633cc03429
COMPONENT_ARCHIVE_URL= \
  ftp://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/1.34/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://live.gnome.org/GObjectIntrospection

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_POST_UNPACK_ACTION = \
        /usr/bin/find $(SOURCE_DIR) -name *.py \
                -exec $(GSED) -i -e 's:/usr/bin/env python:$(PYTHON):' "{}" \; ;

COMPONENT_PREP_ACTION += ( cd $(@D)&& \
					aclocal -I ./m4 &&\
                                        autoheader &&\
                                        automake -a -f -c --gnu &&\
                                        autoconf )

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --disable-tests

CONFIGURE_ENV += PYTHON=$(PYTHON)

COMPONENT_BUILD_ENV += CC="$(CC)"

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)
