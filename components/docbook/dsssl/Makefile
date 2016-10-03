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
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS=		NO_ARCH
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		docbook-dsssl
COMPONENT_VERSION=	1.79
COMPONENT_PROJECT_URL=	http://docbook.sourceforge.net/
COMPONENT_ARCHIVE_HASH= \
    sha256:d5a199024a5fe0862bfaff9e3533817cd8d08bddf3cdfb5bfe6088cbb2cd62b3
COMPONENT_ARCHIVE_URL=	http://prdownloads.sourceforge.net/docbook/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/docbook

TPNO=			9655

TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk

build:          $(SOURCE_DIR)/.prep

install:        $(SOURCE_DIR)/.prep

# Called in SMF method scripts:
REQUIRED_PACKAGES += data/sgml-common
REQUIRED_PACKAGES += shell/bash
# SMF manifest dependencies:
REQUIRED_PACKAGES += system/core-os
# Needed for collateindex.pl script:
REQUIRED_PACKAGES += $(PERL_PKG)
