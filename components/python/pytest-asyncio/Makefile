#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2022 Andreas Wacknitz
#

BUILD_BITS= NO_ARCH
BUILD_STYLE= setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pytest-asyncio
COMPONENT_VERSION=	0.18.1
COMPONENT_SUMMARY=	Pytest support for asyncio
COMPONENT_PROJECT_URL=	https://github.com/pytest-dev/$(COMPONENT_NAME)
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:c43fcdfea2335dd82ffe0f2774e40285ddfea78a8e81e56118d47b6a90fbb09e
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_FMRI=		library/python/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_LICENSE=	MIT

PYTHON_VERSIONS= 3.7 3.9

include $(WS_MAKE_RULES)/common.mk

# Tests don't work yet as we miss many dependent packages.
COMPONENT_TEST_DIR =	$(SOURCE_DIR)
COMPONENT_TEST_CMD=		tox -e py$(PYV)

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# Manually added build dependencies
REQUIRED_PACKAGES += library/python/setuptools_scm-37
REQUIRED_PACKAGES += library/python/setuptools_scm-39

# Manually added test dependencies
# We are still missing mypy
REQUIRED_PACKAGES += library/python/coverage-37
REQUIRED_PACKAGES += library/python/coverage-39
REQUIRED_PACKAGES += library/python/flaky-37
REQUIRED_PACKAGES += library/python/flaky-39
REQUIRED_PACKAGES += library/python/hypothesis-37
REQUIRED_PACKAGES += library/python/hypothesis-39
REQUIRED_PACKAGES += library/python/pytest-37
REQUIRED_PACKAGES += library/python/pytest-39
REQUIRED_PACKAGES += library/python/tox
REQUIRED_PACKAGES += library/python/zipp-37
REQUIRED_PACKAGES += library/python/zipp-39

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
