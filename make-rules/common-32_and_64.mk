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
# Copyright (c) 2015, Oracle and/or its affiliates. All rights reserved.
#

#
# This file sets up the default options and base requirements for components
# that should be built for 32-bit and 64-bit.
#
include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE= $(ASLR_ENABLE)

# common targets
build:          $(BUILD_32_and_64)
install:        $(INSTALL_32_and_64)
test:           $(TEST_32_and_64)
system-test:    $(SYSTEM_TEST_32_and_64)
