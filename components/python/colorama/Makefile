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

COMPONENT_NAME=		colorama
COMPONENT_VERSION=	0.4.4
COMPONENT_SUMMARY=	Simple cross-platform colored terminal text in Python
COMPONENT_PROJECT_URL=	https://github.com/tartley/colorama
COMPONENT_FMRI=		library/python/colorama
COMPONENT_CLASSIFICATION= Development/Python 
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	$(call pypi_url)	
COMPONENT_ARCHIVE_HASH= \
	sha256:5941b2b48a20143d2267e95b1c2a7603ce057ee39fd88e7329b0c292aa16869b
COMPONENT_LICENSE=	BSD 3 Clause
COMPONENT_LICENSE_FILE=	LICENSE.txt

PYTHON_VERSIONS=	3.5

TEST_TARGET:	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
