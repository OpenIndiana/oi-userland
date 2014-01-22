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
# Copyright (c) 2014, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		zendopcache
COMPONENT_VERSION=	7.0.2
COMPONENT_PROJECT_URL=	http://pecl.php.net/package/ZendOpcache
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	\
    sha256:4aea4f0242dc50a5a68e7a170c3c537716e5da03b2a7b322349f211c09d90f44
COMPONENT_ARCHIVE_URL=	http://pecl.php.net/get/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/php

PATCH_DIR = ../zendopcache/patches

include ../extensions-zts.mk
include ../cleancr.mk

COMPONENT_PREP_ACTION += $(call cleancr,$(SOURCE_DIR)/Optimizer/zend_optimizer_internal.h)
COMPONENT_PREP_ACTION += $(call cleancr,$(SOURCE_DIR)/Optimizer/zend_optimizer.c)
COMPONENT_PREP_ACTION += $(call cleancr,$(SOURCE_DIR)/Optimizer/zend_optimizer.h)
