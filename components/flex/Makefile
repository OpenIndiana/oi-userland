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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		flex
COMPONENT_VERSION=	2.5.35
COMPONENT_PROJECT_URL=	http://flex.sourceforge.net/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:0becbd4b2b36b99c67f8c22ab98f7f80c9860aec70f0350a0018f29a88704e7b
COMPONENT_ARCHIVE_URL=	http://softlayer.dl.sourceforge.net/project/flex/flex/flex-2.5.35/flex-2.5.35.tar.bz2

TPNO=			14883

SONAME=libfl.so.1
LDFLAGS += $(CC_BITS)

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS  +=		--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  +=		M4="$(GNUBIN)/m4"

COMPONENT_BUILD_ENV +=		SONAME="$(SONAME)"
COMPONENT_INSTALL_ENV +=	SONAME="$(SONAME)"

COMPONENT_TEST_ENV +=		PATH=$(GNUBIN):$(USRBINDIR)

COMPONENT_BUILD_TARGETS += $(SONAME)
COMPONENT_INSTALL_TARGETS += $(SONAME)

REQUIRED_PACKAGES += developer/macro/gnu-m4
REQUIRED_PACKAGES += system/library/math
