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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		paramiko
COMPONENT_VERSION=	2.4.2
COMPONENT_SUMMARY=	'Library for making SSH2 connections'
COMPONENT_PROJECT_URL=	https://github.com/pyca/paramiko/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:a8975a7df3560c9f1e2b43dc54ebd40fd00a7017392ca5445ce7df409f900fcb
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_FMRI=	library/python/paramiko
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE=	LICENSE

PYTHON_VERSIONS=	2.7 3.4 3.5

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_TEST_DIR =    $(COMPONENT_SRC)/tests
COMPONENT_TEST_CMD =    $(PYTHON) /usr/bin/py.test-$(PYTHON_VERSION)
COMPONENT_TEST_ARGS =

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

# Tests fail - depend on pytest-relaxed and pytest > 3
test:           $(TEST_NO_ARCH)

# Test dependencies
REQUIRED_PACKAGES += library/python/pytest-27
REQUIRED_PACKAGES += library/python/pytest-34
REQUIRED_PACKAGES += library/python/pytest-35
REQUIRED_PACKAGES += library/python/bcrypt
REQUIRED_PACKAGES += library/python/cryptography
REQUIRED_PACKAGES += library/python/pynacl
REQUIRED_PACKAGES += library/python/six

# Build dependencies
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-34
REQUIRED_PACKAGES += runtime/python-35
