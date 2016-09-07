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
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		websockify
COMPONENT_VERSION=	0.8.0
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:f080e40b3f429f39dc557c62c6d715a683100e7c10c557fa376b6dbde23358ce
COMPONENT_PROJECT_URL=	https://github.com/kanaka/websockify
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/archive/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	python-mod/websockify

TPNO=			27984

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

COMPONENT_POST_INSTALL_ACTION = \
	(cd $(PROTO_DIR)/usr/bin ; \
         $(MV) -f websockify websockify-$(PYTHON_VERSION))

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:		$(NO_TESTS)

system-test:    $(NO_TESTS)

REQUIRED_PACKAGES += library/python/setuptools-27
REQUIRED_PACKAGES += library/python/setuptools-34
REQUIRED_PACKAGES += library/python/setuptools-35
