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
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#

#
# This file sets up the standard, default options and base requirements for
# openfabrics userland components.
#
COMPONENT_PROJECT_URL ?=	http://www.openfabrics.org/
COMPONENT_ARCHIVE_URL ?=	https://www.openfabrics.org/downloads/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)

# component default overrides
TEST_TARGET=
SYSTEM_TEST_TARGET=
include $(WS_MAKE_RULES)/common.mk
include ../ofed.mk

ASLR_MODE= $(ASLR_ENABLE)

# Almost every component requires these before Solaris 12.  Those that do not
# can simply override.
ifeq ($(OS_VERSION),5.11)
LIBS +=	-lsocket -lnsl
endif

# common targets
test:		$(NO_TESTS)

system-test:    $(NO_TESTS)

