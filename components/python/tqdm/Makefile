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
# Copyright 2019-2020 Nona Hansel
#

BUILD_BITS=	NO_ARCH
BUILD_STYLE=	setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tqdm
COMPONENT_VERSION=	4.53.0
COMPONENT_SUMMARY=	'Fast, extensible progress bar for Python and CLI'
COMPONENT_PROJECT_URL=	https://github.com/tqdm/tqdm
COMPONENT_FMRI=		library/python/tqdm		
COMPONENT_CLASSIFICATION= Development/Python 
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_ARCHIVE_HASH= \
	sha256:3d3f1470d26642e88bd3f73353cb6ff4c51ef7d5d7efef763238f4bc1f7e4e81
COMPONENT_LICENSE=	MPLv2.0,MIT
COMPONENT_LICENSE_FILE=	LICENCE

PYTHON_VERSIONS=	3.5

TEST_TARGET:	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/setuptools-35
REQUIRED_PACKAGES += runtime/python-35
