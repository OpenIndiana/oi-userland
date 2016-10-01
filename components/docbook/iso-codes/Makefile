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
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS=		64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		iso-codes
COMPONENT_VERSION=	3.21
COMPONENT_PROJECT_URL=	https://pkg-isocodes.alioth.debian.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:2362169a9ee2f8940c52a76adf2564f59146103ecb895727a1c91aa6f0f5207d
COMPONENT_ARCHIVE_URL=	http://pkgs.fedoraproject.org/repo/pkgs/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)/fce56d7fc8c4af4e4ee9582c89f48eb8/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/docbook

TPNO=			9314

TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# Needed to successfully find iso2pot.py
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))
