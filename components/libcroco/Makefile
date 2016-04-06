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

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= libcroco
COMPONENT_VERSION= 0.6.8
COMPONENT_SUMMARY= Cascading Style Sheet (CSS) parsing and manipulation toolkit
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:ea6e1b858c55219cefd7109756bff5bc1a774ba7a55f7d3ccd734d6b871b8570
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/0.6/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.gnome.org
COMPONENT_LICENSE_FILE = COPYING
COMPONENT_LICENSE = LGPLv2
COMPONENT_FMRI = library/libcroco
COMPONENT_CLASSIFICATION = Desktop (GNOME)/Libraries

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_SCRIPT = $(SOURCE_DIR)/autogen.sh

CONFIGURE_OPTIONS += --enable-static=no
CONFIGURE_OPTIONS += --disable-Bsymbolic

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)
