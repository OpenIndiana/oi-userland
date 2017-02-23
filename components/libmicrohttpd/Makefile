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
COMPONENT_VERSION = 0.9.37
COMPONENT_ARCHIVE_HASH = \
    sha256:a78cbcc050fb50f4ef4cf02709a3f8dd498e9230271b445fc3dbec4132b47cdc
COMPONENT_BUGDB=	library/libmicrohttpd
COMPONENT_ANITYA_ID=	1658

TPNO = 18422

include $(WS_MAKE_RULES)/gnu-component.mk

LINT_FLAGS += -I$(PROTOUSRINCDIR)

CPPFLAGS += $(CPP_LARGEFILES)

CONFIGURE_OPTIONS += --disable-https
CONFIGURE_OPTIONS += --disable-spdy
CONFIGURE_OPTIONS += --includedir=$(USRINCDIR)/microhttpd

COMPONENT_TEST_ENV +=	PATH="$(GNUBIN):$(PATH)"

# requires an older automake to reconfigure. 
COMPONENT_PREP_ACTION += \
	(cd $(@D); ACLOCAL=aclocal-1.11 AUTOMAKE=automake-1.11 autoreconf -fiv);
