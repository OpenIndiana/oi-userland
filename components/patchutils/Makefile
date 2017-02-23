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
# Copyright (c) 2016, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		patchutils
COMPONENT_VERSION=	0.3.1
IPS_PKG_NAME=		text/patchutils
COMPONENT_PROJECT_URL=	http://cyberelk.net/tim/patchutils/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:48d28d4a6fd9922e15ecfd8a152ba5aef6673842c8303337fcaa6b3bb2d129a2
COMPONENT_ARCHIVE_URL=	http://cyberelk.net/tim/data/patchutils/stable/$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	2599

TPNO=			9269

include $(WS_MAKE_RULES)/common.mk

# A couple of tests dump core, and the message contains the pid
# A number of failing tests operate on randomly named files
# Remove the make garbage from the test output
COMPONENT_TEST_TRANSFORMS += \
	'-e "/coredump/s/[0-9]*: Abort/XXXX: Abort/"' \
	'-e "s,\(/var/tmp//.*diff-1\.\)......,\1XXXXXX,"' \
	'-e "1,/^for test in/{N;d}"' \
	'-e "/^===/{N;N;q}"'

# Note that the gendiff tests will fail on Solaris, because the gendiff utility
# is missing; this is delivered by rpm.

REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += text/gnu-diffutils
REQUIRED_PACKAGES += text/gnu-patch
