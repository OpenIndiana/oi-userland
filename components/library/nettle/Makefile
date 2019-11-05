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
# Copyright 2019 Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		nettle
COMPONENT_VERSION=	3.5.1
COMPONENT_SUMMARY=	A low-level cryptographic library
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:75cca1998761b02e16f2db56da52992aef622bf55a3b45ec538bc2eedadc9419
COMPONENT_ARCHIVE_URL= \
	https://ftp.gnu.org/gnu/nettle/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://www.lysator.liu.se/~nisse/nettle/
COMPONENT_FMRI=		library/nettle
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=	LGPLv3, GPLv3, GPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION = ( cd $(@D) && autoreconf -f -i )

CPPFLAGS += -I/usr/include/gmp

CONFIGURE_OPTIONS += --disable-assembler

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += system/library
