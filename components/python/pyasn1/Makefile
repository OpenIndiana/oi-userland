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

COMPONENT_NAME=		pyasn1
COMPONENT_VERSION=	0.4.4
COMPONENT_SUMMARY=	'ASN.1 types and DER/BER/CER codecs (X.208)'
COMPONENT_PROJECT_URL=	https://github.com/etingof/pyasn1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:f58f2a3d12fd754aa123e9fa74fb7345333000a035f3921dbdaa08597aa53137
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_FMRI=	library/python/pyasn1
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	LICENSE.rst

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

test:           $(TEST_NO_ARCH)

# Test dependencies
REQUIRED_PACKAGES += library/python/pytest-27
REQUIRED_PACKAGES += library/python/pytest-34
REQUIRED_PACKAGES += library/python/pytest-35
