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
BUILD_BITS= 64_and_32
BUILD_STYLE= setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		PyNaCl
COMPONENT_VERSION=	1.4.0
COMPONENT_SUMMARY=	Python binding to libsodium
COMPONENT_PROJECT_URL=	https://github.com/pyca/pynacl/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:54e9a2c849c742006516ad56a88f5c74bf2ce92c9f67435187c3c5953b346505
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_FMRI=	library/python/pynacl
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=	Apache-2.0
COMPONENT_LICENSE_FILE=	LICENSE

# This is the list of pythons versions we support tests for.
# So, if you want to run tests activate this and deactivate the other PYTHON_VERSIONS definition:
#PYTHON_VERSIONS=	$(PYTHON3_VERSIONS)
PYTHON_VERSIONS=	$(PYTHON_ALL_VERSIONS)

include $(WS_MAKE_RULES)/common.mk

COMPONENT_BUILD_ENV += SODIUM_INSTALL=system
COMPONENT_INSTALL_ENV += SODIUM_INSTALL=system

TEST_PYTHONPATH = $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages

COMPONENT_TEST_ENV = PYTHONPATH=$(TEST_PYTHONPATH)
COMPONENT_TEST_DIR =    $(COMPONENT_SRC)/tests
COMPONENT_TEST_CMD =    $(PYTHON) /usr/bin/py.test-$(PYTHON_VERSION)
COMPONENT_TEST_ARGS =

# Test dependencies
REQUIRED_PACKAGES += library/python/flaky-35
REQUIRED_PACKAGES += library/python/flaky-37
REQUIRED_PACKAGES += library/python/flaky-39
REQUIRED_PACKAGES += library/python/hypothesis-35
REQUIRED_PACKAGES += library/python/hypothesis-37
REQUIRED_PACKAGES += library/python/hypothesis-39
REQUIRED_PACKAGES += library/python/py-35
REQUIRED_PACKAGES += library/python/py-37
REQUIRED_PACKAGES += library/python/py-39
REQUIRED_PACKAGES += library/python/pyparsing-35
REQUIRED_PACKAGES += library/python/pyparsing-37
REQUIRED_PACKAGES += library/python/pyparsing-39
REQUIRED_PACKAGES += library/python/pytest-35
REQUIRED_PACKAGES += library/python/pytest-37
REQUIRED_PACKAGES += library/python/pytest-39
REQUIRED_PACKAGES += library/python/pytest-benchmark-35
REQUIRED_PACKAGES += library/python/pytest-benchmark-37
REQUIRED_PACKAGES += library/python/pytest-benchmark-39
REQUIRED_PACKAGES += library/python/pytest-reporter-35
REQUIRED_PACKAGES += library/python/pytest-reporter-37
REQUIRED_PACKAGES += library/python/pytest-reporter-39
REQUIRED_PACKAGES += library/python/sortedcontainers-35
REQUIRED_PACKAGES += library/python/sortedcontainers-37
REQUIRED_PACKAGES += library/python/sortedcontainers-39

# Auto-generated dependencies
REQUIRED_PACKAGES += library/security/libsodium
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
REQUIRED_PACKAGES += system/library
