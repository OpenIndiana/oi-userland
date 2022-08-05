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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2018, Michal Nowak
#

BUILD_STYLE = justmake

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		convmv
HUMAN_VERSION =		2.05
COMPONENT_VERSION =	2.5
COMPONENT_REVISION =	1
COMPONENT_SUMMARY=	Filename Encoding Conversion Tool
COMPONENT_DESCRIPTION=	Convmv helps convert a single filename,\
 a directory tree and the contained files or a whole filesystem\
 into a different encoding.
COMPONENT_PROJECT_URL=	http://www.j3e.de/linux/convmv/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:53b6ac8ae4f9beaee5bc5628f6a5382bfd14f42a5bed3d881b829d7b52d81ca6
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		text/convmv
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	GPL2

include $(WS_MAKE_RULES)/common.mk

PATCH_LEVEL=0

COMPONENT_TEST_TARGETS = test
COMPONENT_TEST_TRANSFORMS += '-e "/^make\[/d"'			# delete make logs
COMPONENT_TEST_TRANSFORMS += '-e "/^unimplemented function:/d"'	# delete lines changing with every run
COMPONENT_TEST_TRANSFORMS += '-e "s/ in [0-9]* seconds//g"'	# delete timing info

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl
