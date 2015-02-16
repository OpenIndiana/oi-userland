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
# Copyright (c) 2013, 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		rabbitmq-server
COMPONENT_VERSION=	3.1.3
COMPONENT_PROJECT_URL=	http://www.rabbitmq.com/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:ebb8b0dba8ef82e5523194072f465f2abe451783e09255bf1474c560667a67a5
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/releases/$(COMPONENT_NAME)/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	service/rabbitmq

TPNO=			14503

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

PKG_PROTO_DIRS += $(BUILD_DIR)/$(MACH32)

# We delegate the running of the tests to a script because it's easier to find
# and use unique free ports in a single process, and it's easier to make sure
# that we don't leave any servers running if the tests themselves fail.
COMPONENT_TEST_DIR =		$(COMPONENT_DIR)
COMPONENT_TEST_CMD =		$(PYTHON)
COMPONENT_TEST_TARGETS =	test.py $(TEST_32)

# common targets
build:		$(BUILD_32)

# The install target in the rabbitmq makefile isn't useful to us.
install:

test:		$(TEST_32)

PKG_PROTO_DIRS +=	$(COMPONENT_DIR)/files


REQUIRED_PACKAGES += runtime/erlang
REQUIRED_PACKAGES += shell/ksh93
