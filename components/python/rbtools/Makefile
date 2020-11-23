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
# Copyright 2019 Michal Nowak
# Copyright 2019-2020 Nona Hansel
#

BUILD_BITS=	NO_ARCH
BUILD_STYLE=	setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		RBTools
COMPONENT_VERSION=	1.0.3
COMPONENT_SUMMARY=	'RBTools is a set of command line tools and a rich Python API for use with Review Board'
COMPONENT_PROJECT_URL=	https://www.reviewboard.org/downloads/rbtools/
COMPONENT_FMRI=		library/python/rbtools
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_ARCHIVE_HASH= \
	sha256:ff4cea3ad7b2d1b1666b811021cf5047f1fbe9417428fb5133a40ede81e3e83c
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	COPYING

PYTHON_VERSIONS=	3.5

TEST_TARGET:	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_DIR =    $(SOURCE_DIR)
COMPONENT_TEST_CMD =    nosetests-$(PYTHON_VERSION)
COMPONENT_TEST_ARGS =  -v

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/setuptools-35
REQUIRED_PACKAGES += runtime/python-35
