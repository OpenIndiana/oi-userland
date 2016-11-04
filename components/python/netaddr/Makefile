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
# Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		netaddr
COMPONENT_VERSION=	0.7.10
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:9b79763141a855079b0589717696a4ccb5c56c0b807b6e584bfe12333399e0b7
COMPONENT_PROJECT_URL=  http://github.com/drkjam/netaddr/
COMPONENT_ARCHIVE_URL=	https://pypi.python.org/packages/source/n/netaddr/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	python-mod/netaddr

PYTHON_VERSIONS=2.7

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_POST_INSTALL_ACTION = \
	(cd $(PROTOUSRBINDIR) ; $(MV) netaddr netaddr-$(PYTHON_VERSION))

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

COMPONENT_TEST_DIR=	$(@D)/lib/netaddr
COMPONENT_TEST_ARGS=	tests/__init__.py
COMPONENT_PRE_TEST_ACTION= \
	( cd $(COMPONENT_TEST_DIR)/tests ; \
	  ln -s $(SOURCE_DIR)/netaddr/tests/2.x ; \
	  ln -s $(SOURCE_DIR)/netaddr/tests/3.x )

test:		$(TEST_NO_ARCH)

REQUIRED_PACKAGES += library/python/ipython-27
REQUIRED_PACKAGES += runtime/python-27
