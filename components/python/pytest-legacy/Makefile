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

BUILD_BITS= NO_ARCH
BUILD_STYLE= setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pytest
COMPONENT_VERSION=	6.1.2
COMPONENT_REVISION=	1
COMPONENT_FMRI=		library/python/pytest
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_SUMMARY=	pytest: simple powerful testing with Python
COMPONENT_PROJECT_URL=	https://docs.pytest.org/en/latest/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:c0a7e94a8cdbc5422a51ccdad8e6f1024795939cc89159a0ae7f0b316ad3823e
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_LICENSE=	MIT

PYTHON_VERSIONS= 3.5

# We don't support tests for this legacy version
TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# New version of pytest no longer generates -$(PYVER) script for
# each version.  Generate them now for backward compatibility.
COMPONENT_POST_INSTALL_ACTION += \
        ($(MV) $(PROTOUSRBINDIR)/py.test $(PROTOUSRBINDIR)/py.test-$(PYTHON_VERSION); \
         $(MV) $(PROTOUSRBINDIR)/pytest $(PROTOUSRBINDIR)/pytest-$(PYTHON_VERSION))

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# Manually added build dependencies according to setup.cfg
REQUIRED_PACKAGES += library/python/setuptools_scm-35

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/setuptools-35
REQUIRED_PACKAGES += runtime/python-35
