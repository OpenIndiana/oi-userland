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
# Copyright (c) 2015, Oracle and/or its affiliates. All rights reserved.
#

# Put
# $(SKIP_TEST_AT_TOP_LEVEL) 
# in your component Makefile if you want that component to skip its
# testing when "gmake test" is run at the top level.
# We assume shared_macros.mk is already included.
ifdef TOP_LEVEL_TEST
TEST_32 = $(SKIP_TEST)
TEST_64 = $(SKIP_TEST)
TEST_32_and_64 = $(SKIP_TEST)
TEST_NO_ARCH = $(SKIP_TEST)
endif
