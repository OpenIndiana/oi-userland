# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016 Adam Stevko
#

BUILD_BITS=32_and_64
BUILD_STYLE=setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		scandir
COMPONENT_VERSION=	1.10.0
COMPONENT_SUMMARY=	Better directory iterator and faster os.walk(), now in the Python 3.5 stdlib
COMPONENT_PROJECT_URL=	https://github.com/benhoyt/scandir
COMPONENT_FMRI=		library/python/scandir
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/benhoyt/scandir/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:73a773c58432ce28f32286f2892217101f4cf61ff4bccd8829ebaa7af7c56620
COMPONENT_LICENSE=	BSD

PYTHON_VERSIONS= 2.7 3.5 3.7

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += system/library
