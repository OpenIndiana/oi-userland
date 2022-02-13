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
# Copyright (c) 2022 Andreas Wacknitz
#

BUILD_BITS= NO_ARCH
BUILD_STYLE= setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		wheel
COMPONENT_VERSION=	0.37.1
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	The reference implementation of the Python wheel packaging standard, as defined in PEP 427
COMPONENT_PROJECT_URL=	https://github.com/pypa/wheel
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_ARCHIVE_HASH= sha256:e9a504e793efbca1b8e0e9cb979a249cf4a0a7b5b8c9e8b65a5e39d49529c1c4
COMPONENT_FMRI=		library/python/wheel
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=	MIT

PYTHON_VERSIONS=	3.7 3.9

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_DIR=	$(SOURCE_DIR)
COMPONENT_TEST_CMD=	tox -e py$(PYV)

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# Manually added test dependencies
# Tests don't work
REQUIRED_PACKAGES += library/python/pluggy-37
REQUIRED_PACKAGES += library/python/pluggy-39
REQUIRED_PACKAGES += library/python/py-37
REQUIRED_PACKAGES += library/python/py-39
REQUIRED_PACKAGES += library/python/pytest-37
REQUIRED_PACKAGES += library/python/pytest-39
REQUIRED_PACKAGES += library/python/pytest-cov-37
REQUIRED_PACKAGES += library/python/pytest-cov-39
REQUIRED_PACKAGES += library/python/tox

COMPONENT_POST_INSTALL_ACTION += \
        (cd $(PROTOUSRBINDIR); $(MV) wheel wheel-$(PYTHON_VERSION)) ;

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/setuptools-37
REQUIRED_PACKAGES += library/python/setuptools-39
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
