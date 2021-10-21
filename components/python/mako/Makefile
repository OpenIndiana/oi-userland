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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright 2015, PALO Richard.
# Copyright 2017 Gary Mills
# Copyright 2021 Andreas Wacknitz
#

BUILD_BITS=NO_ARCH
BUILD_STYLE=setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		Mako
COMPONENT_VERSION=	1.1.5
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	A template library written in Python
COMPONENT_PROJECT_URL=	https://www.makotemplates.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:169fa52af22a91900d852e937400e79f535496191c63712e3b9fda5a9bed6fc3
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_FMRI=		library/python/mako
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=	MIT

PYTHON_VERSIONS=	$(PYTHON_ALL_VERSIONS)

# We don't support tests because we don't have tox:
TEST_TARGET=		$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_POST_INSTALL_ACTION = \
	(cd $(PROTO_DIR)/usr/bin ; \
         $(MV) -f mako-render mako-render-$(PYTHON_VERSION))

COMPONENT_TEST_DIR=	$(COMPONENT_SRC)
COMPONENT_TEST_ARGS=	./setup.py test

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
