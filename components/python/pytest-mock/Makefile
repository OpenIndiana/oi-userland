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

COMPONENT_NAME=		pytest-mock
COMPONENT_VERSION=	3.6.1
COMPONENT_SUMMARY=	Thin-wrapper around the mock package for easier use with pytest
COMPONENT_PROJECT_URL=	https://github.com/pytest-dev/$(COMPONENT_NAME)
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:40217a058c52a63f1042f0784f62009e976ba824c418cced42e88d5f40ab0e62
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_FMRI=		library/python/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_LICENSE=	MIT

PYTHON_VERSIONS= 3.7 3.9

include $(WS_MAKE_RULES)/common.mk

# Tests don't work yet as we miss many dependent packages.
COMPONENT_TEST_DIR =	$(SOURCE_DIR)
COMPONENT_TEST_CMD=		tox-3.9 -e py$(PYV)

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# Manually added test dependencies
REQUIRED_PACKAGES += library/python/pluggy-37
REQUIRED_PACKAGES += library/python/pluggy-39
REQUIRED_PACKAGES += library/python/py-37
REQUIRED_PACKAGES += library/python/py-39
REQUIRED_PACKAGES += library/python/pytest-37
REQUIRED_PACKAGES += library/python/pytest-39
REQUIRED_PACKAGES += library/python/pytest-asyncio-37
REQUIRED_PACKAGES += library/python/pytest-asyncio-39
REQUIRED_PACKAGES += library/python/tox-39

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
