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
# Copyright 2018 Alexander Pyhalov
# Copyright 2021 Andreas Wacknitz
#

# Component uses ABI3 naming.
PYTHON3_SOABI= abi3
BUILD_BITS= 64
BUILD_STYLE= setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		bcrypt
COMPONENT_VERSION=	3.2.0
COMPONENT_SUMMARY=	Modern password hashing for your software and your servers
COMPONENT_PROJECT_URL=	https://github.com/pyca/bcrypt/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:5b93c1726e50a93a033c36e5ca7fdcd29a5c7395af50a6892f5d9e7c6cfbfb29
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_FMRI=	library/python/bcrypt
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=	Apache-2.0
COMPONENT_LICENSE_FILE=	LICENSE

PYTHON_VERSIONS=	3.7 3.9

include $(WS_MAKE_RULES)/common.mk

TEST_PYTHONPATH= $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages

COMPONENT_TEST_ENV=	PYTHONPATH=$(TEST_PYTHONPATH)
COMPONENT_TEST_DIR=	$(COMPONENT_SRC)/tests
COMPONENT_TEST_CMD=	$(PYTHON) /usr/bin/py.test-$(PYTHON_VERSION)
COMPONENT_TEST_ARGS=	test_bcrypt.py

# Test dependencies
REQUIRED_PACKAGES += library/python/flaky-37
REQUIRED_PACKAGES += library/python/flaky-39
REQUIRED_PACKAGES += library/python/hypothesis-37
REQUIRED_PACKAGES += library/python/hypothesis-39
REQUIRED_PACKAGES += library/python/py-37
REQUIRED_PACKAGES += library/python/py-39
REQUIRED_PACKAGES += library/python/pyparsing-37
REQUIRED_PACKAGES += library/python/pyparsing-39
REQUIRED_PACKAGES += library/python/pytest-37
REQUIRED_PACKAGES += library/python/pytest-39
REQUIRED_PACKAGES += library/python/pytest-benchmark-37
REQUIRED_PACKAGES += library/python/pytest-benchmark-39
REQUIRED_PACKAGES += library/python/pytest-reporter-37
REQUIRED_PACKAGES += library/python/pytest-reporter-39
REQUIRED_PACKAGES += library/python/sortedcontainers-37
REQUIRED_PACKAGES += library/python/sortedcontainers-39

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
REQUIRED_PACKAGES += system/library
