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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnutls
COMPONENT_VERSION=	3.5.14
COMPONENT_REVISION=	4
COMPONENT_PROJECT_URL=  ftp://ftp.gnutls.org/gcrypt/gnutls/v3.5
COMPONENT_SUMMARY=	GNU transport layer security library
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
    sha256:4aa12dec92f42a0434df794aca3d02f6f2a35b47b48c01252de65f355c051bda
COMPONENT_ARCHIVE_URL=  ftp://ftp.gnutls.org/gcrypt/gnutls/v3.5/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL= $(COMPONENT_ARCHIVE_URL).sig
COMPONENT_FMRI=	library/gnutls-3
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=	GPLv3, LGPLv2.1, FDLv1.3

# The GnuTLS API and ABI have incompatible changes between versions 2.x
# and 3.x; but the basic symlink name 'libgnutls.so' and pkg-config file
# name 'gnutls.pc' are unchanged.  As a result, it's not possible to have
# both versions installed at the same time in the default paths in a way
# that makes it possible to build programs that are only compatible with
# one version of the API.  As a result, GnuTLS version 3 delivered to a folder
# called gnutls-3 temporarily.  The plan is to integrate 3.4.1 and move all
# programs to 3.4.1; after all usage of 2.8.6  excised, move 3.4.1 to the
# default location.

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CFLAGS += -I$(USRINCDIR)/gmp
CFLAGS += -I$(USRINCDIR)/idn2

MCS = mcs
STRIP = strip

CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS += --mandir=$(USRSHAREDIR)/$(COMPONENT_NAME)-3/man
CONFIGURE_OPTIONS += --includedir=$(USRINCDIR)/$(COMPONENT_NAME)-3/
CONFIGURE_OPTIONS.32 += --libdir=$(USRLIBDIR)/$(COMPONENT_NAME)-3/
CONFIGURE_OPTIONS.64 += --libdir=$(USRLIBDIR64)/$(COMPONENT_NAME)-3/
CONFIGURE_OPTIONS.32 += --libexecdir=$(USRLIBDIR)/pkgconfig/$(COMPONENT_NAME)-3/
CONFIGURE_OPTIONS.64 += --libexecdir=$(USRLIBDIR64)/pkgconfig/$(COMPONENT_NAME)-3/
CONFIGURE_OPTIONS += --localedir=$(USRSHARELOCALEDIR)/$(COMPONENT_NAME)-3/
CONFIGURE_OPTIONS += --localstatedir=$(VARDIR)
CONFIGURE_OPTIONS += --disable-guile
CONFIGURE_OPTIONS += --with-included-libtasn1
CONFIGURE_OPTIONS += --with-included-unistring
#CONFIGURE_OPTIONS += --without-p11-kit
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

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

# Auto-generated dependencies: 
REQUIRED_PACKAGES += library/desktop/p11-kit
REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += library/libidn2
REQUIRED_PACKAGES += library/nettle
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
