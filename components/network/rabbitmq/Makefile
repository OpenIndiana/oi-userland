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
# Copyright (c) 2013, 2023, Oracle and/or its affiliates.
#
BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

PATH=$(PATH.gnu)

COMPONENT_NAME=		rabbitmq-server
COMPONENT_VERSION=	4.1.2
COMPONENT_SUMMARY=	RabbitMQ is message broker software written in Erlang that implements the Advanced Message Queuing Protocol (AMQP) standard.
COMPONENT_SRC_NAME=	rabbitmq-server
COMPONENT_PROJECT_URL=	https://www.rabbitmq.com/
COMPONENT_SRC= $(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= ${COMPONENT_SRC}.tar.xz
COMPONENT_ARCHIVE_HASH= sha256:86a4672a9c57a69ee6b84aba0cf1005e27c86c920a14fe42a1dac84576e982b6
COMPONENT_ARCHIVE_URL= https://github.com/rabbitmq/rabbitmq-server/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).asc
COMPONENT_FMRI=		network/rabbitmq
COMPONENT_CLASSIFICATION= Applications/Internet
COMPONENT_LICENSE= MPLv1.1, MPLv2.0, EPLv1.1, Apache 2.0, MIT, ISC, BSD, BSD-like
COMPONENT_LICENSE_FILE= LICENSE

BUILD_STYLE= justmake

include $(WS_MAKE_RULES)/common.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# Use a simple copy instead of cloney.
CLONEY_MODE = copy

# replace !/bin/sh to !/bin/bash
COMPONENT_PRE_BUILD_ACTION = ( \
    cd $(@D); \
	sed -i 's:^\#!/bin/sh:\#!/bin/bash:' $(@D)/deps/rabbit/scripts/*; \
)

COMPONENT_BUILD_ACTION +=	/usr/bin/true
COMPONENT_BUILD_TARGETS =	all
COMPONENT_BUILD_ENV += LC_ALL=en_US.UTF-8
COMPONENT_BUILD_ENV += PROJECT_VERSION=$(COMPONENT_VERSION)
COMPONENT_BUILD_ENV += HOME=/tmp

COMPONENT_INSTALL_TARGETS = install install-man
COMPONENT_INSTALL_ENV +=	DESTDIR=$(PROTO_DIR)
COMPONENT_INSTALL_ENV +=	MANDIR=/usr/share/man
COMPONENT_INSTALL_ENV +=	RMQ_ROOTDIR=/usr
COMPONENT_INSTALL_ENV +=	RMQ_BINDIR=/usr/lib/rabbitmq/bin
COMPONENT_INSTALL_ENV +=	RMQ_LIBDIR=/usr/lib
COMPONENT_INSTALL_ENV +=	RMQ_ERLAPP_DIR=/usr/lib/rabbitmq
COMPONENT_INSTALL_ENV +=	LC_ALL=en_US.UTF-8
COMPONENT_INSTALL_ENV += PROJECT_VERSION=$(COMPONENT_VERSION)
COMPONENT_INSTALL_ENV += HOME=/tmp

# We need to create and install plugins before the tests.
$(TEST_TARGET): $(INSTALL_TARGET)

# Execute a quick test to verify RabbitMQ installation.
# RabbitMQ service has to be disabled before the testing.
COMPONENT_TEST_DIR =		$(COMPONENT_DIR)
COMPONENT_TEST_CMD =		$(SHELL)
COMPONENT_TEST_ENV += 	LC_ALL=en_US.UTF-8
COMPONENT_TEST_ENV += HOME=/tmp
COMPONENT_TEST_TARGETS =	test.sh $(BUILD_DIR_64) $(BUILD_DIR_64)/test-rabbit
COMPONENT_TEST_TRANSFORMS +=	'-e "/is updated to a safe effective value of/d"'


REQUIRED_PACKAGES += runtime/elixir

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += runtime/erlang
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
