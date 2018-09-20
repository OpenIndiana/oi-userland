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
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pylxml
COMPONENT_VERSION=	4.2.5
COMPONENT_PROJECT_URL=	http://lxml.de/
COMPONENT_SRC_NAME=	lxml
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	\
    sha256:36720698c29e7a9626a0dc802ef8885f8f0239bfd1689628ecd459a061f2807f

COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)files/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	python-mod/lxml

PYTHON_VERSIONS=	2.7 3.4 3.5

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

COMPONENT_TEST_ARGS=	test
COMPONENT_TEST_CMD=	$(MAKE)
COMPONENT_TEST_DIR=	$(COMPONENT_SRC)
COMPONENT_TEST_ENV+=	PYTHON=$(PYTHON)
COMPONENT_TEST_ENV+=	LC_ALL=en_US.UTF-8

# Prevent errors like: OSError: Error reading file 'http://127.0.0.1:59951/':
# failed to load HTTP resource
COMPONENT_TEST_ENV+=    http_proxy=
COMPONENT_TEST_ENV+=    https_proxy=
COMPONENT_TEST_ENV+=    HTTP_PROXY=
COMPONENT_TEST_ENV+=    HTTPS_PROXY=

COMPONENT_TEST_TRANSFORMER = $(GSED) -E
COMPONENT_TEST_TRANSFORMS += \
	'-e "s/micro=[0-9]*/micro=/" ' \
	'-e "s/^Ran.*/Ran/" ' \
	'-ne "/^(Ran|FAIL)/,\\$$p" '

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

# Tests fail with
# ERROR: test_xmlschema_parse_fixed_attributes (lxml.tests.test_xmlschema.ETreeXMLSchemaTestCase)
# lxml.etree.XMLSyntaxError: Element 'b', attribute 'hardy': The value '(null)' does not match the fixed value constraint 'hey'.
# https://bugs.launchpad.net/lxml/+bug/1608479
test:		$(TEST_32_and_64)

REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-34
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += system/library
