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
# Copyright (c) 2010, 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnutls
COMPONENT_VERSION=	3.4.6
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  ftp://ftp.gnutls.org/gcrypt/gnutls/v3.4
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
    sha256:feb559ed7fffa24d5aa40527054fae5cb7f7b66e9f2bebc2383a781dfa4d20ec
COMPONENT_ARCHIVE_URL=  ftp://ftp.gnutls.org/gcrypt/gnutls/v3.4/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/gnutls

TPNO=			25396

COMPONENT_BUILD_TARGETS = all info

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# The GnuTLS API and ABI have incompatible changes between versions 2.8.6
# and 3.4.1; but the basic symlink name 'libgnutls.so' and pkg-config file
# name 'gnutls.pc' are unchanged.  As a result, it's not possible to have
# both versions installed at the same time in the default paths in a way
# that makes it possible to build programs that are only compatible with
# one version of the API.  As a result, GnuTLS version 3 delivered to a folder
# called gnutls-3 temporarily.  The plan is to integrate 3.4.1 and move all
# programs to 3.4.1; after all usage of 2.8.6  excised, move 3.4.1 to the
# default location.
CONFIGURE_OPTIONS += --sysconfdir=/etc 
CONFIGURE_OPTIONS += --infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS += --mandir=/usr/share/$(COMPONENT_NAME)-3/man
CONFIGURE_OPTIONS += --includedir=/usr/include/$(COMPONENT_NAME)-3/
CONFIGURE_OPTIONS.32 += --libdir=/usr/lib/$(COMPONENT_NAME)-3/
CONFIGURE_OPTIONS.64 += --libdir=/usr/lib/$(MACH64)/$(COMPONENT_NAME)-3/
CONFIGURE_OPTIONS.32 += --libexecdir=/usr/lib/pkgconfig/$(COMPONENT_NAME)-3/
CONFIGURE_OPTIONS.64 += --libexecdir=/usr/lib/$(MACH64)/pkgconfig/$(COMPONENT_NAME)-3/
CONFIGURE_OPTIONS += --localedir=/usr/share/locale/$(COMPONENT_NAME)-3/
CONFIGURE_OPTIONS += --localstatedir=/var 
CONFIGURE_OPTIONS += --enable-guile=no
CONFIGURE_OPTIONS += --with-included-libtasn1
CONFIGURE_OPTIONS += --without-p11-kit
CONFIGURE_OPTIONS += --disable-ecdhe
CONFIGURE_OPTIONS += --disable-openssl-compatibility
CONFIGURE_OPTIONS += --disable-tests
CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS) -I/usr/include/gmp -I/usr/include/idn $(CC_BITS)"
CONFIGURE_OPTIONS += CXX="$(CXX) -norunpath $(CC_BITS)"

CONFIGURE_ENV += LDFLAGS="$(LDFLAGS) $(CC_BITS)" 

ASLR_MODE = $(ASLR_ENABLE)

include ../../make-rules/shared-targets.mk

configure:      $(CONFIGURE_32_and_64)

build:          $(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += \
	'-n -e "/SKIP/p" ' \
	'-e "/PASS/p" ' \
	'-e "/FAIL/p" ' \
	'-e "/TOTAL/p" ' \
	'-e "/ERROR/p" '

test:		$(TEST_32_and_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)

REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += library/libidn
REQUIRED_PACKAGES += library/libtasn1
REQUIRED_PACKAGES += library/security/nettle
REQUIRED_PACKAGES += library/security/trousers
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/c++-runtime
