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
# Copyright 2019 Nona Hansel
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		RBTools
COMPONENT_VERSION=	1.0.2
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	'RBTools is a set of command line tools and a rich Python API for use with Review Board'
COMPONENT_PROJECT_URL=	https://www.reviewboard.org/downloads/rbtools/
COMPONENT_FMRI=		library/python/rbtools
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_ARCHIVE_HASH= \
	sha256:577c2f8bbf88f77bda84ee95af0310b59111c156f48a5aab56ca481e2f77eaf4
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	COPYING

PYTHON_VERSIONS=	3.5

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_TEST_DIR =    $(SOURCE_DIR)
COMPONENT_TEST_CMD =    nosetests-$(PYTHON_VERSION)
COMPONENT_TEST_ARGS =	-v

build:          $(BUILD_NO_ARCH)

install:        $(INSTALL_NO_ARCH)

test:           $(TEST_NO_ARCH)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/setuptools-35
REQUIRED_PACKAGES += runtime/python-35
