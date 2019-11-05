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
#

# Component uses ABI3 naming.
PYTHON3_SOABI=abi3

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		PyNaCl
COMPONENT_VERSION=	1.3.0
COMPONENT_SUMMARY=	'Python binding to libsodium'
COMPONENT_PROJECT_URL=	https://github.com/pyca/pynacl/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:0c6100edd16fefd1557da078c7a31e7b7d7a52ce39fdca2bec29d4f7b6e7600c
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_FMRI=	library/python/pynacl
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=	Apache-2.0
COMPONENT_LICENSE_FILE=	LICENSE

PYTHON_VERSIONS=	2.7 3.4 3.5

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_BUILD_ENV += SODIUM_INSTALL=system
COMPONENT_INSTALL_ENV += SODIUM_INSTALL=system

TEST_PYTHONPATH = $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages

COMPONENT_TEST_ENV = PYTHONPATH=$(TEST_PYTHONPATH)
COMPONENT_TEST_DIR =    $(COMPONENT_SRC)/tests
COMPONENT_TEST_CMD =    $(PYTHON) /usr/bin/py.test-$(PYTHON_VERSION)
COMPONENT_TEST_ARGS =

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

# Tests do not pass.
# They require hypothesis which we don't ship.
test:           $(TEST_32_and_64)

# Test dependencies
REQUIRED_PACKAGES += library/python/pytest-27
REQUIRED_PACKAGES += library/python/pytest-34
REQUIRED_PACKAGES += library/python/pytest-35

# Auto-generated dependencies
REQUIRED_PACKAGES += library/security/libsodium
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-34
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += system/library
