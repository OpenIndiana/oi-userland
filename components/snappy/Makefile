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
# Copyright (c) 2017, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS= 64_and_32
COMPILER  = gcc
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=         snappy
COMPONENT_VERSION=      1.1.3
COMPONENT_ARCHIVE_HASH= \
    sha256:2f1e82adf0868c9e26a5a7a3115111b6da7e432ddbac268a7ca2fae2a247eef3
COMPONENT_ARCHIVE_URL=  https://github.com/google/snappy/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  http://google.github.io/snappy/

TPNO = 31969

CONFIGURE_OPTIONS.64 +=    --prefix=$(USRLIBDIR64)
CONFIGURE_OPTIONS    +=    --prefix=$(USRLIBDIR)

include $(WS_MAKE_RULES)/common.mk

REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
