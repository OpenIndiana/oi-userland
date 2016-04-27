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
# Copyright (c) 2012, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		libestr
COMPONENT_VERSION=	0.1.10
COMPONENT_PROJECT_URL=	http://libestr.adiscon.com/
COMPONENT_ARCHIVE_HASH=	sha256:bd655e126e750edd18544b88eb1568d200a424a0c23f665eb14bbece07ac703c
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)files/download/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	service/rsyslog
TPNO=			27081

# No longer seems to have tests
TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Userland default includes -mt which links with libthread which we don't need.
studio_MT =

ASLR_MODE = $(ASLR_NOT_APPLICABLE)
