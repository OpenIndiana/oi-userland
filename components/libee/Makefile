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
# Copyright (c) 2012, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		libee
COMPONENT_VERSION=	0.4.1
COMPONENT_PROJECT_URL=	http://www.libee.org/
COMPONENT_ARCHIVE_HASH=	sha256:c0dac01938593deee06c3d161e4eda4ecc0fd7317e1321bd96e301aceb7fb027
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)files/download/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	service/rsyslog
TPNO=			20532
COMPONENT_ANITYA_ID=	13310

# Tests are currently broken
TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Userland default includes -mt which links with libthread which we don't need.
studio_MT =

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

REQUIRED_PACKAGES += library/libestr
REQUIRED_PACKAGES += system/library/math
