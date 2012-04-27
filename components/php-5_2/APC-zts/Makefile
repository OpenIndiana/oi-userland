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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		APC
COMPONENT_VERSION=	3.0.19
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	\
    sha256:a02677a7884361d64fbf3745c402f2a6ff313e817b0d0a2010acb64cd05247b0
COMPONENT_ARCHIVE_URL=	http://pecl.php.net/get/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://pecl.php.net/package/APC/

PATCH_DIR = ../APC/patches

include ../extensions-zts.mk

CONFIGURE_OPTIONS += \
	--enable-apc \
	--enable-apc-mmap
