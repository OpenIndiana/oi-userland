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
# Copyright 2019 Nona Hansel
#

BUILD_BITS=			NO_ARCH
BUILD_STYLE=		setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		texttable
COMPONENT_VERSION=	1.6.3
COMPONENT_SUMMARY=	'Python module for creating simple ASCII tables'
COMPONENT_PROJECT_URL=	https://github.com/foutaise/texttable
COMPONENT_FMRI=		library/python/texttable
COMPONENT_CLASSIFICATION= Development/Python 
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_ARCHIVE_HASH= \
	sha256:ce0faf21aa77d806bbff22b107cc22cce68dc9438f97a2df32c93e9afa4ce436
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	LICENSE

PYTHON_VERSIONS=	3.5

TEST_TARGET:		$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
