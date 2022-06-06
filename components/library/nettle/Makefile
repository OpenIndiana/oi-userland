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
# Alas it's not yet possible to convince nettle to use newer OpeenSSL.
#USE_OPENSSL11= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		nettle
COMPONENT_VERSION=	3.8
COMPONENT_SUMMARY=	A low-level cryptographic library
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:7576c68481c198f644b08c160d1a4850ba9449e308069455b5213319f234e8e6
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/gnu/nettle/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://www.lysator.liu.se/~nisse/nettle/
COMPONENT_FMRI=		library/nettle
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=	LGPLv3, GPLv3, GPLv2

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION = ( cd $(@D) && autoreconf -f -i )

#CONFIGURE_OPTIONS += --with-include-path=$(OPENSSL_INCDIR)
#CONFIGURE_OPTIONS += --with-libs-path=$(OPENSSL_LIBDIR).$(BITS)

COMPONENT_TEST_TRANSFORMS += \
    '-n ' \
    '-e "/=========/p" ' \
    '-e "/tests passed/p" ' \
    '-e "/TOTAL/p" ' \
    '-e "/PASS/p" ' \
    '-e "/SKIP/p" ' \
    '-e "/XFAIL/p" ' \
    '-e "/FAIL/p" ' \
    '-e "/XPASS/p" ' \
    '-e "/ERROR/p" '

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

# Manually added build dependencyies
REQUIRED_PACKAGES += library/security/openssl

# Auto-generated dependencies
REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += system/library
