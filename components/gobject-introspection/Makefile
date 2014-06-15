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

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= gobject-introspection

COMPONENT_VERSION= 0.9.12
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= Introspection for GObject libraries
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:9c0060d66d14a060057a1fc005be73675a1b8a00d4968ce8e78ff2d6b9f84e81
COMPONENT_ARCHIVE_URL= \
  ftp://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/0.9/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://live.gnome.org/GObjectIntrospection

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

gcc_OPT = -O2

COMPONENT_POST_UNPACK_ACTION = \
        /usr/bin/find $(SOURCE_DIR) -name *.py \
                -exec $(GSED) -i -e 's:/usr/bin/env python:$(PYTHON):' "{}" \; ;

COMPONENT_PREP_ACTION += ( cd $(@D)&& \
					aclocal -I ./m4 &&\
                                        autoheader &&\
                                        automake -a -f -c --gnu &&\
                                        autoconf )

CONFIGURE_OPTIONS += --sysconfdir=/etc

CONFIGURE_ENV += PYTHON=$(PYTHON)

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)
