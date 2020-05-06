#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2010, 2016, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2019, Michal Nowak
#

BUILD_BITS=		32_and_64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnutls
COMPONENT_VERSION=	3.5.19
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=  ftp://ftp.gnutls.org/gcrypt/gnutls/v3.5
COMPONENT_SUMMARY=	GNU transport layer security library
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:1936eb64f03aaefd6eb16cef0567457777618573826b94d03376bb6a4afadc44
COMPONENT_ARCHIVE_URL=  ftp://ftp.gnutls.org/gcrypt/gnutls/v3.5/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).sig
COMPONENT_FMRI=		library/gnutls-3
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=	GPLv3, LGPLv2.1, FDLv1.3

include $(WS_MAKE_RULES)/common.mk

CFLAGS += -I$(USRINCDIR)/gmp
CFLAGS += -I$(USRINCDIR)/idn2

MCS = mcs
STRIP = strip

CONFIGURE_OPTIONS += --disable-guile
CONFIGURE_OPTIONS += --disable-ecdhe
CONFIGURE_OPTIONS += --disable-openssl-compatibility
CONFIGURE_OPTIONS += --disable-tests

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += \
	'-n -e "/SKIP/p" ' \
	'-e "/PASS/p" ' \
	'-e "/FAIL/p" ' \
	'-e "/TOTAL/p" ' \
	'-e "/ERROR/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += developer/build/autogen
REQUIRED_PACKAGES += library/desktop/p11-kit
REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += library/libidn2
REQUIRED_PACKAGES += library/libtasn1
REQUIRED_PACKAGES += library/libunistring
REQUIRED_PACKAGES += library/nettle
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
