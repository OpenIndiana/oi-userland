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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2018, Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		patch
COMPONENT_VERSION=	2.7.6
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		The GNU Patch utility
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/patch/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:ac610bda97abe0d9f6b7c963255a11dcb196c25e337c61f94e4778d632f1d8fd
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/patch/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		text/gnu-patch
COMPONENT_CLASSIFICATION =	Development/GNU
COMPONENT_LICENSE =		GPLv2
COMPONENT_LICENSE_FILE =	patch.license

# Note: CVE-2019-20633 and CVE-2021-45261 are not fixed yet.

USE_DEFAULT_TEST_TRANSFORMS = yes

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_ENV_CMD = $(ENV) -i

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
