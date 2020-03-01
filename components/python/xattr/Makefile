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
# Copyright (c) 2014, 2020, Oracle and/or its affiliates. All rights reserved.
# Copyright 2020 Nona Hansel
#

# Component uses ABI3 naming.
PYTHON3_SOABI=abi3

BUILD_BITS=		64
BUILD_STYLE=		setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		xattr
COMPONENT_VERSION=	0.9.7
COMPONENT_SUMMARY=	'Extended attributes library wrapper for Python'
COMPONENT_PROJECT_URL=	https://github.com/xattr/xattr
COMPONENT_FMRI=		library/python/xattr
COMPONENT_CLASSIFICATION= Development/Python 
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	$(call pypi_url)	
COMPONENT_ARCHIVE_HASH= \
	sha256:b0bbca828e04ef2d484a6522ae7b3a7ccad5e43fa1c6f54d78e24bb870f49d44
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	LICENSE.txt

PYTHON_VERSIONS=	3.5

include $(WS_MAKE_RULES)/common.mk

CFFI = $(WS_COMPONENTS)/python/cffi/build/prototype/$(MACH)/$(PYTHON_LIB)

COMPONENT_BUILD_ENV +=		PYTHONPATH=$(CFFI)
COMPONENT_INSTALL_ENV +=	PYTHONPATH=$(CFFI):$(PROTO_DIR)/$(PYTHON_LIB)
COMPONENT_TEST_ENV +=		PYTHONPATH=$(CFFI):$(PROTO_DIR)/$(PYTHON_LIB)
# The test suite wants to use some unicode filenames, which don't work in the C
# locale.
COMPONENT_TEST_ENV +=	LC_ALL=en_US.UTF-8
COMPONENT_TEST_DIR =	$(@D)/tests
COMPONENT_TEST_CMD =	$(PYTHON) -m pytest
COMPONENT_TEST_ARGS =   -v

COMPONENT_POST_INSTALL_ACTION += \
    (cd $(PROTO_DIR)/usr/bin; $(MV) xattr xattr-$(PYTHON_VERSION))

# Tests run under setuptools work very hard to run in the source directory
# itself, and will thus blow up with an VerificationError (wrong ELF class)
# when running 64-bit tests after 32-bit or vice-versa.  So copy the source off
# to a target-specific directory and run the tests.  Note that this will also
# rebuild the package, since it doesn't want to use what it should already be
# finding in PYTHONPATH.
COMPONENT_PRE_TEST_ACTION = $(CP) -r $(SOURCE_DIR) $(@D)/tests

REQUIRED_PACKAGES += library/python/cffi
# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/setuptools-35
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += system/library
