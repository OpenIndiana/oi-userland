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
# Copyright 2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= nettle
COMPONENT_VERSION= 2.7
COMPONENT_SUMMARY= Library for desktop notifications
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:c294ea133c05382cc2effb1734d49f4abeb1ad8515543a333de49a11422cd4d6
COMPONENT_ARCHIVE_URL= \
  https://ftp.gnu.org/gnu/nettle/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://www.lysator.liu.se/~nisse/nettle/
COMPONENT_FMRI=	library/nettle
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE = LGPLv2
COMPONENT_LICENSE_FILE = COPYING.LIB

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION = ( cd $(@D) && autoreconf -f -i )

CPPFLAGS += -I/usr/include/gmp

# Can't properly link library without this
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SCRIPT=       $(@D)/configure

CONFIGURE_OPTIONS += --disable-assembler

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)
