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
# Copyright (c) 2015, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME = libmicrohttpd
COMPONENT_VERSION = 0.9.52
COMPONENT_ARCHIVE_HASH = \
    sha256:54797f6e763d417627f89f60e4ae0a431dab0523f92f83def23ea02d0defafea
COMPONENT_BUGDB=	library/libmicrohttpd
COMPONENT_ANITYA_ID=	1658

TPNO = 32330

# Use the compiler default 'xc99=all,no_lib' (specifically we want to prevent
# autoconf from finding and using C11 Annex K bounds checking interfaces because
# ON then won't be able to link with this library).
studio_C99MODE=-xc99=all,no_lib

# Needed for "gmake test" to work successfully.
unexport SHELLOPTS

include $(WS_MAKE_RULES)/gnu-component.mk

LINT_FLAGS += -I$(PROTOUSRINCDIR)

CPPFLAGS += $(CPP_LARGEFILES)

CONFIGURE_OPTIONS += --includedir=$(USRINCDIR)/microhttpd
PKG_CONFIG_PATHS.32 += /usr/lib/pkgconfig/gnutls-3
PKG_CONFIG_PATHS.64 += /usr/lib/$(MACH64)/pkgconfig/gnutls-3
PKG_CONFIG_PATHS += $(PKG_CONFIG_PATHS.$(BITS))

COMPONENT_TEST_ENV +=	PATH="$(GNUBIN):$(PATH)"

COMPONENT_PREP_ACTION += \
	(cd $(@D); ACLOCAL=aclocal-1.15 AUTOMAKE=automake-1.15 autoreconf -fiv);

REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += system/library/security/libgcrypt
