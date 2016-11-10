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
# Copyright (c) 2013, 2016, Oracle and/or its affiliates. All rights reserved.
#
# Prefer 32-bit as only "binary" delivered is a script with embedded paths.
BUILD_BITS= 32_and_64
include ../../make-rules/shared-macros.mk
COMPONENT_NAME=		daq
COMPONENT_VERSION=	2.0.6
COMPONENT_PROJECT_URL=	http://www.snort.org/
COMPONENT_ARCHIVE_HASH=	\
    sha256:b40e1d1273e08aaeaa86e69d4f28d535b7e53bdb3898adf539266b63137be7cb
COMPONENT_ARCHIVE_URL=	https://www.snort.org/downloads/snort/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/daq

TPNO=			32523

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Solaris should really define these. See CR #15431883 and 15537286.
CFLAGS +=	-Du_int8_t=uint8_t
CFLAGS +=	-Du_int16_t=uint16_t
CFLAGS +=	-Du_int32_t=uint32_t

CONFIGURE_OPTIONS +=	--disable-ipfw-module
CONFIGURE_OPTIONS +=    --enable-static=no

# cheesy, but if we turn off visibility then it doesn't
# save the CFLAGS right and then nulls them.
CONFIGURE_OPTIONS +=	"gl_cv_cc_visibility=no"
CONFIGURE_OPTIONS +=	gl_save_CFLAGS="$(CFLAGS)"

REQUIRED_PACKAGES += developer/lexer/flex
REQUIRED_PACKAGES += developer/parser/bison
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library/libpcap
