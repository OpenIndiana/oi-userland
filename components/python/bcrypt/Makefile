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

COMPONENT_NAME=		bcrypt
COMPONENT_VERSION=	3.1.5
COMPONENT_SUMMARY=	'Modern password hashing for your software and your servers'
COMPONENT_PROJECT_URL=	https://github.com/pyca/bcrypt/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:136243dc44e5bab9b61206bd46fff3018bd80980b1a1dfbab64a22ff5745957f
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_FMRI=	library/python/bcrypt
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=	Apache-2.0
COMPONENT_LICENSE_FILE=	LICENSE

PYTHON_VERSIONS=	2.7 3.4 3.5

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

TEST_PYTHONPATH = $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages

COMPONENT_TEST_ENV = PYTHONPATH=$(TEST_PYTHONPATH)
COMPONENT_TEST_DIR =    $(COMPONENT_SRC)/tests
COMPONENT_TEST_CMD =    $(PYTHON) /usr/bin/py.test-$(PYTHON_VERSION)
COMPONENT_TEST_ARGS =   test_bcrypt.py

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:           $(TEST_32_and_64)

# Test dependencies
REQUIRED_PACKAGES += library/python/pytest-27
REQUIRED_PACKAGES += library/python/pytest-34
REQUIRED_PACKAGES += library/python/pytest-35

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += system/library
