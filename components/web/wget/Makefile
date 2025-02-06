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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2018, Michal Nowak
# Copyright (c) 2021, Nona Hansel
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         wget
COMPONENT_VERSION=      1.25.0
COMPONENT_REVISION=     1
COMPONENT_SUMMARY=	GNU wget - a utility to retrieve files from the World Wide Web
COMPONENT_PROJECT_URL=  https://www.gnu.org/software/wget/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.lz
COMPONENT_ARCHIVE_HASH= sha256:19225cc756b0a088fc81148dc6a40a0c8f329af7fd8483f1c7b2fe50f4e08a1f
COMPONENT_ARCHIVE_URL=  https://ftp.gnu.org/gnu/wget/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		web/wget
COMPONENT_CLASSIFICATION= Applications/Internet
COMPONENT_LICENSE=	GPLv3, FDLv1.2

include $(WS_MAKE_RULES)/common.mk

# wget doesn't detect libidn2 include directory
CPPFLAGS +=	-I/usr/include/idn2

# Enforce openssl (--with-ssl=openssl) instead of default gnutls
# (--with-ssl) as wget doesn't work for secure connections with gnutls. 
CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --with-ssl=openssl
CONFIGURE_OPTIONS += --infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS += --enable-iri

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

# Some tests fail, see http://savannah.gnu.org/bugs/?48281
# Keep just the final test report
COMPONENT_TEST_TRANSFORMS += '-ne "/^PASS/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^FAIL/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^===/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^\# /p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^See/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^Please/p" '

# For the test suite
TEST_REQUIRED_PACKAGES += library/perl-5/http-daemon
TEST_REQUIRED_PACKAGES += library/perl-5/http-message

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += library/libidn2
REQUIRED_PACKAGES += library/libpsl
REQUIRED_PACKAGES += library/pcre2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
