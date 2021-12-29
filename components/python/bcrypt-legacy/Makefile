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
PYTHON3_SOABI= abi3
BUILD_BITS= 64_and_32
BUILD_STYLE= setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		bcrypt
COMPONENT_VERSION=	3.1.7
COMPONENT_SUMMARY=	Modern password hashing for your software and your servers
COMPONENT_PROJECT_URL=	https://github.com/pyca/bcrypt/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:0b0069c752ec14172c5f78208f1863d7ad6755a6fae6fe76ec2c80d13be41e42
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_FMRI=	library/python/bcrypt
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=	Apache-2.0
COMPONENT_LICENSE_FILE=	LICENSE

PYTHON_VERSIONS=	2.7 3.5

# We don't support tests for legacy python modules
TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += system/library
