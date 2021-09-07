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
# copyright 2021 Andreas Wacknitz
#

BUILD_BITS=	NO_ARCH
BUILD_STYLE= setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pyasn1
COMPONENT_VERSION=	0.4.8
COMPONENT_SUMMARY=	ASN.1 types and DER/BER/CER codecs (X.208)
COMPONENT_PROJECT_URL=	https://github.com/etingof/pyasn1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:aef77c9fb94a3ac588e87841208bdec464471d9871bd5050a287cc9a475cd0ba
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_FMRI=	library/python/pyasn1
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	LICENSE.rst

PYTHON_VERSIONS=	$(PYTHON3_VERSIONS)

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_DIR =    $(COMPONENT_SRC)/tests
COMPONENT_TEST_CMD =    $(PYTHON) /usr/bin/py.test-$(PYTHON_VERSION)
COMPONENT_TEST_ARGS =   

# Manually added test dependencies
REQUIRED_PACKAGES += library/python/pytest-35
REQUIRED_PACKAGES += library/python/pytest-37
REQUIRED_PACKAGES += library/python/pytest-39
