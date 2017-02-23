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
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		patch
COMPONENT_VERSION=	2.7.5
COMPONENT_ARCHIVE_HASH=	\
    sha256:7436f5a19f93c3ca83153ce9c5cbe4847e97c5d956e57a220121e741f6e7968f
COMPONENT_BUGDB=	utility/gpatch
COMPONENT_ANITYA_ID=	2597

TPNO=			22293

# Although system-test doesn't run against the built bits, the tests
# require the bits are built.  Using build as a pre-requisite
# to system-test separates the compilation output from the
# test output, so the master test results will be consistent between
# test and system-test targets.
SYSTEM_TEST_TARGET= build $(SYSTEM_TEST_64)
include $(WS_MAKE_RULES)/gnu-component.mk

# Needed for "gmake test" to work successfully.
# If SHELLOPTS is exported (as it is by the userland makefiles),
# then all shell options get exported to child invocations of bash,
# which results in test failures due to nounset being
# set unexpectedly, and errors such as "$1: unbound variable"
unexport SHELLOPTS

COMPONENT_INSTALL_ARGS += bindir=$(USRBINDIR)

COMPONENT_SYSTEM_TEST_ENV += PATCH=$(GPATCH)
