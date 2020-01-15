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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2017, Aurelien Larcher.
# Copyright (c) 2020, Michal Nowak
#

BUILD_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		sed
COMPONENT_VERSION=	4.8
COMPONENT_FMRI=		text/gnu-sed
COMPONENT_SUMMARY=	GNU implementation of sed, the Unix stream editor
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/sed/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
	sha256:f79b0cfea71b37a8eeec8490db6c5f7ae7719c35587f21edb0617f370eeff633
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/pub/gnu/sed/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv3, FDLv1.3

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

CONFIGURE_BINDIR.64= $(GNUBIN)

CONFIGURE_OPTIONS  +=		--infodir=$(CONFIGURE_INFODIR)

# Needed for "gmake test" to work successfully.
# If SHELLOPTS is exported (as it is by the userland makefiles),
# then all shell options get exported to child invocations of bash,
# which results in test failures due to nounset and xtrace being
# set unexpectedly, and errors such as "$1: unbound variable" and
# diffs failing due to script tracing in output files.
unexport SHELLOPTS

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/TOTAL/p" ' \
	'-e "/SKIP/p" ' \
	'-e "/PASS/p" ' \
	'-e "/FAIL/p" ' \
	'-e "/ERROR/p" '

# Test dependencies
REQUIRED_PACKAGES += developer/debug/valgrind
REQUIRED_PACKAGES += developer/versioning/cvs
REQUIRED_PACKAGES += locale/de
REQUIRED_PACKAGES += locale/en
REQUIRED_PACKAGES += locale/fr
REQUIRED_PACKAGES += locale/fr-extra
REQUIRED_PACKAGES += locale/zh_cn-extra

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
