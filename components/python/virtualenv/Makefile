#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2019 Tim Mooney
# Copyright (c) 2021 Andreas Wacknitz
#

BUILD_BITS= NO_ARCH
BUILD_STYLE= setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		virtualenv
COMPONENT_VERSION=	20.13.0
COMPONENT_FMRI=		library/python/virtualenv
COMPONENT_SUMMARY=	A tool to create isolated Python environments
COMPONENT_PROJECT_URL=	https://virtualenv.pypa.io/en/latest/
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:d8458cf8d59d0ea495ad9b34c2599487f8a7772d796f9910858376d1600dd2dd
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_LICENSE=	MIT

PYTHON_VERSIONS=	$(PYTHON3_VERSIONS)

include $(WS_MAKE_RULES)/common.mk

# Tests don't work successfully yet.
COMPONENT_TEST_DIR =	$(SOURCE_DIR)
COMPONENT_TEST_CMD=		tox-3.9

# Replace "#!/usr/bin/env ..." shebang lines with properly versioned ones.
COMPONENT_POST_INSTALL_ACTION += \
    $(FIND) $(PROTOUSRLIBDIR)/python$(PYTHON_VERSION) -name *.py \
        -exec $(GSED) -i -e 's|env python|python$(PYTHON_VERSION)|' "{}" \; ;

COMPONENT_POST_INSTALL_ACTION += \
        (cd $(PROTOUSRBINDIR); $(MV) virtualenv virtualenv-$(PYTHON_VERSION)) ;

# Manually added test dependencies
# Note that we still missing some test dependencies and have many failing tests.
REQUIRED_PACKAGES += library/python/coverage-35
REQUIRED_PACKAGES += library/python/coverage-37
REQUIRED_PACKAGES += library/python/coverage-39
#REQUIRED_PACKAGES += library/python/coverage-enable-subprocess-35
#REQUIRED_PACKAGES += library/python/coverage-enable-subprocess-37
#REQUIRED_PACKAGES += library/python/coverage-enable-subprocess-39
REQUIRED_PACKAGES += library/python/flaky-35
REQUIRED_PACKAGES += library/python/flaky-37
REQUIRED_PACKAGES += library/python/flaky-39
#REQUIRED_PACKAGES += library/python/freezegun-35
REQUIRED_PACKAGES += library/python/freezegun-37
REQUIRED_PACKAGES += library/python/freezegun-39
REQUIRED_PACKAGES += library/python/packaging-35
REQUIRED_PACKAGES += library/python/packaging-37
REQUIRED_PACKAGES += library/python/packaging-39
REQUIRED_PACKAGES += library/python/pytest-35
REQUIRED_PACKAGES += library/python/pytest-37
REQUIRED_PACKAGES += library/python/pytest-39
#REQUIRED_PACKAGES += library/python/pytest-env-35
#REQUIRED_PACKAGES += library/python/pytest-env-37
#REQUIRED_PACKAGES += library/python/pytest-env-39
#REQUIRED_PACKAGES += library/python/pytest-mock-35
REQUIRED_PACKAGES += library/python/pytest-mock-37
REQUIRED_PACKAGES += library/python/pytest-mock-39
#REQUIRED_PACKAGES += library/python/pytest-randomly-35
REQUIRED_PACKAGES += library/python/pytest-randomly-37
REQUIRED_PACKAGES += library/python/pytest-randomly-39
#REQUIRED_PACKAGES += library/python/pytest-timeout-35
REQUIRED_PACKAGES += library/python/pytest-timeout-37
REQUIRED_PACKAGES += library/python/pytest-timeout-39
REQUIRED_PACKAGES += library/python/tox-39
#REQUIRED_PACKAGES += library/python/wheel-35
REQUIRED_PACKAGES += library/python/wheel-37
REQUIRED_PACKAGES += library/python/wheel-39

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/setuptools-35
REQUIRED_PACKAGES += library/python/setuptools-37
REQUIRED_PACKAGES += library/python/setuptools-39
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
