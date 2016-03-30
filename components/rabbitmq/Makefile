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
# Copyright (c) 2013, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 32
include ../../make-rules/shared-macros.mk

PATH=/usr/gnu/bin:/usr/bin:/usr/sbin

COMPONENT_NAME=		rabbitmq-server
COMPONENT_VERSION=	3.5.6
COMPONENT_PROJECT_URL=	http://www.rabbitmq.com/
COMPONENT_ARCHIVE_HASH=	\
    sha256:24be1433234112db391e0c5ef32bfb2ca111e51b2e57998cc0f3d97ba361671f
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/releases/$(COMPONENT_NAME)/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	service/rabbitmq

TPNO=			25764

BUILD_STYLE= justmake
include $(WS_MAKE_RULES)/common.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

PKG_PROTO_DIRS += $(BUILD_DIR)/$(MACH32)

COMPONENT_INSTALL_ENV +=	TARGET_DIR=$(PROTO_DIR)
COMPONENT_INSTALL_ENV +=	SBIN_DIR=$(PROTO_DIR)/usr/sbin
COMPONENT_INSTALL_ENV +=	MAN_DIR=$(PROTO_DIR)/usr/share/man

# We delegate the running of the tests to a script because it's easier to find
# and use unique free ports in a single process, and it's easier to make sure
# that we don't leave any servers running if the tests themselves fail.
COMPONENT_TEST_DIR =		$(COMPONENT_DIR)
COMPONENT_TEST_CMD =		$(PYTHON)
COMPONENT_TEST_TARGETS =	test.py $(TEST_32)

PKG_PROTO_DIRS +=	$(COMPONENT_DIR)/files


REQUIRED_PACKAGES += runtime/erlang
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
