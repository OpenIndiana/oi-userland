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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2020, Michal Nowak
# Copyright (c) 2020-2021, Nona Hansel
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		grep
COMPONENT_VERSION=	3.12
COMPONENT_SUMMARY= 	GNU grep utilities
COMPONENT_PROJECT_URL=	https://gnu.org/software/grep/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:2649b27c0e90e632eadcd757be06c6e9a4f48d941de51e7c0f83ff76408a07b9
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/gnu/grep/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		text/gnu-grep
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_LICENSE=	GPLv3, FDLv1.3

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION= ( \
	cd $(@D) && \
	aclocal -I m4 && \
	autoheader && \
	automake --add-missing --copy --force )

PATH= $(PATH.gnu)

# Testsuite requirements
TEST_REQUIRED_PACKAGES += developer/versioning/cvs
TEST_REQUIRED_PACKAGES += locale/tr
TEST_REQUIRED_PACKAGES += locale/ru-extra
TEST_REQUIRED_PACKAGES += locale/zh_cn-extra

# Auto-generated dependencies
REQUIRED_PACKAGES += library/pcre2
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
