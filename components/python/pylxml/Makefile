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
BUILD_BITS=32_and_64
BUILD_STYLE=setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pylxml
COMPONENT_VERSION=	4.6.1
COMPONENT_FMRI=		library/python/lxml
COMPONENT_SUMMARY=	Pythonic $(PYVER) binding for the libxml2 and libxslt libraries
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_PROJECT_URL=	http://lxml.de/
COMPONENT_SRC_NAME=	lxml
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	\
    sha256:c152b2e93b639d1f36ec5a8ca24cde4a8eefb2b6b83668fcd8e83a67badcb367
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)files/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	BSD, PSF, GPL

PYTHON_VERSIONS=	$(PYTHON_VERSIONS_ALL)

include $(WS_TOP)/make-rules/common.mk

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

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
REQUIRED_PACKAGES += system/library
