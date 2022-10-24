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
# Copyright (c) 2011, 2014, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2019, Nona Hansel
# Copyright (c) 2022, Andreas Wacknitz
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		hexedit
COMPONENT_VERSION=	1.6
COMPONENT_SUMMARY=	Hexedit - a command-line binary file editor
COMPONENT_PROJECT_URL=	https://github.com/pixel/$(COMPONENT_NAME)
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:598906131934f88003a6a937fab10542686ce5f661134bc336053e978c4baae3
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=	editor/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE=	GPLv2

TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = ( cd $(@D) && NOCONFIGURE=1 ./autogen.sh )

COMPONENT_PRE_CONFIGURE_ACTION =  \
        ($(CLONEY) $(SOURCE_DIR) $(@D))

CFLAGS += -I/usr/include/ncurses

ASLR_MODE = $(ASLR_ENABLE)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
