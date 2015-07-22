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

COMPONENT_NAME= freetype
COMPONENT_VERSION= 2.5.5
COMPONENT_SUMMARY=  FreeType 2 font engine
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:387bcc4b780b12484aa2ec9f7db1a55d8286eb5639f45fbc0fbba7a4e5a1afb9
COMPONENT_ARCHIVE_URL= \
  http://download.savannah.gnu.org/releases/freetype/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://freetype.org/
COMPONENT_FMRI= system/library/freetype-2
COMPONENT_LICENSE= FreeType
COMPONENT_LICENSE_FILE= docs/FTL.TXT
COMPONENT_CLASSIFICATION= System/Libraries

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

gcc_OPT=-O2

CONFIGURE_OPTIONS+= --enable-biarch-config
CONFIGURE_OPTIONS+= --with-zlib
CONFIGURE_OPTIONS+= --with-pic

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)
