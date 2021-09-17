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
# Copyright (c) 2013 David Hoeppner. All rights reserved.
# Copyright 2021, Andreas Wacknitz
#
BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		teseq
COMPONENT_VERSION=	1.1.1
COMPONENT_SUMMARY=	teseq - terminal control sequences analyzer
COMPONENT_DESCRIPTION=	A tool for analyzing files that contain control characters and terminal control sequences
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/teseq/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:32fbd22bc1e16796a02a3915ac6c29015607a19b00a50de570c747860b009622
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/gnu/teseq/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_FMRI=	text/teseq
COMPONENT_LICENSE=	GPLv3

include $(WS_MAKE_RULES)/common.mk

CFLAGS	+= -std=c99

COMPONENT_TEST_TRANSFORMS += \
	'-ne "/^\# TOTAL:/ p" ' \
	'-ne "/^\# PASS:/ p" ' \
	'-ne "/^\# XPASS:/ p" ' \
	'-ne "/^\# SKIP:/ p" ' \
	'-ne "/^\# FAIL:/ p" ' \
	'-ne "/^\# XFAIL:/ p" ' \
	'-ne "/^\# ERROR:/ p" ' \
	'-ne "/Result/ p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
