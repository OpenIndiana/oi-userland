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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
COMPILER= gcc
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		snort
COMPONENT_VERSION=	2.9.9.0
COMPONENT_ARCHIVE_HASH=	\
    sha256:71b147125e96390a12f3d55796ed5073df77206bd3563d84d3e5a1f19e7d7a56
COMPONENT_PROJECT_URL=	http://www.snort.org/
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)downloads/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)

TPNO=			33599

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# snort 2.9.8.3 (and later) requires automake/autoconf >= 1.14, but Userland
# default is older than what is needed. So hard-coding to the next available,
# 1.15: "--add-missing" needed to use default "compile" script.
AUTOMAKE=/usr/bin/automake-1.15 --add-missing
ACLOCAL=/usr/bin/aclocal-1.15

# Need to recreate the configure script for gethrtime checks.
COMPONENT_PREP_ACTION +=	(cd $(@D); autoreconf -fiv);

CONFIGURE_OPTIONS +=	--with-libpcre-libraries="$(USRLIBDIR64)"
CONFIGURE_OPTIONS +=	--with-dnet-libraries="$(USRLIBDIR64)"
CONFIGURE_OPTIONS +=	--disable-static-daq

REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += developer/lexer/flex
REQUIRED_PACKAGES += developer/parser/bison
REQUIRED_PACKAGES += library/nghttp2
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/security/openssl/openssl-fips-140
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library/libdaq
REQUIRED_PACKAGES += system/library/libdnet
REQUIRED_PACKAGES += system/library/libpcap
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/network
