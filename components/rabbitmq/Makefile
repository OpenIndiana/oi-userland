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
# Copyright (c) 2013, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 32
include ../../make-rules/shared-macros.mk

PATH=/usr/gnu/bin:/usr/bin:/usr/sbin

COMPONENT_NAME=		rabbitmq-server
COMPONENT_VERSION=	3.6.1
COMPONENT_PROJECT_URL=	http://www.rabbitmq.com/
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:c696134e863f99191a301288c12d69ff00b7e648107ee52c8686ae047dde1bee
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/releases/$(COMPONENT_NAME)/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	service/rabbitmq
COMPONENT_ANITYA_ID=	5585

TPNO=			27775

BUILD_STYLE= justmake
include $(WS_MAKE_RULES)/common.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

PKG_PROTO_DIRS += 	$(BUILD_DIR)/$(MACH32)

# rabbitmq doesn't like cloney
COMPONENT_PRE_BUILD_ACTION = ($(CP) -rp $(SOURCE_DIR)/. $(@D))

COMPONENT_BUILD_ACTION +=	/usr/bin/true

COMPONENT_INSTALL_TARGETS =	all
COMPONENT_INSTALL_TARGETS +=	install
COMPONENT_INSTALL_TARGETS +=	install-man
COMPONENT_INSTALL_ENV +=	DESTDIR=$(PROTO_DIR)
COMPONENT_INSTALL_ENV +=	MANDIR=/usr/share/man
COMPONENT_INSTALL_ENV +=	RMQ_ROOTDIR=/usr
COMPONENT_INSTALL_ENV +=	RMQ_BINDIR=/usr/lib/rabbitmq/bin
COMPONENT_INSTALL_ENV +=	RMQ_LIBDIR=/usr/lib
COMPONENT_INSTALL_ENV +=	RMQ_ERLAPP_DIR=/usr/lib/rabbitmq

# We delegate the running of the tests to a script because it's easier to find
# and use unique free ports in a single process, and it's easier to make sure
# that we don't leave any servers running if the tests themselves fail.
COMPONENT_TEST_DIR =		$(COMPONENT_DIR)
COMPONENT_TEST_CMD =		$(PYTHON)
COMPONENT_TEST_TARGETS =	test.py $(TEST_32)

# taken from justmake.mk but with the CLONEY line removed.
# build the configured source
$(BUILD_DIR)/%/.built:  $(SOURCE_DIR)/.prep
	$(RM) -r $(@D) ; $(MKDIR) $(@D)
	$(COMPONENT_PRE_BUILD_ACTION)
	($(COMPONENT_BUILD_ACTION))
	$(COMPONENT_POST_BUILD_ACTION)

REQUIRED_PACKAGES += runtime/erlang
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
