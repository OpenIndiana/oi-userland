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
# Copyright 2022 Andreas Wacknitz
#

BUILD_BITS= 64_and_32
USE_OPENSSL11= yes
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		nettle
COMPONENT_VERSION=	3.9.1
COMPONENT_SUMMARY=	A low-level cryptographic library
COMPONENT_PROJECT_URL=	https://www.lysator.liu.se/~nisse/nettle/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:ccfeff981b0ca71bbd6fbcb054f407c60ffb644389a5be80d6716d5b550c6ce3
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/gnu/nettle/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/nettle
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=	LGPLv3, GPLv3, GPLv2

include $(WS_MAKE_RULES)/common.mk

PATH = $(PATH.gnu)

COMPONENT_PREP_ACTION = ( cd $(@D) && autoreconf -f -i )

LDFLAGS += -L$(OPENSSL_LIBDIR)

CONFIGURE_OPTIONS += --with-include-path=$(OPENSSL_INCDIR)
CONFIGURE_OPTIONS += --with-libs-path=$(OPENSSL_LIBDIR)
CONFIGURE_OPTIONS += --disable-static

COMPONENT_TEST_TRANSFORMS += \
    '-e "/=====/p" ' \
    '-e "/tests passed/p" '

# Manually added build dependencyies
REQUIRED_PACKAGES += library/security/openssl-11

# Auto-generated dependencies
REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += system/library
