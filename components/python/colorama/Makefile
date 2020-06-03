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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		colorama
COMPONENT_VERSION=	0.4.1
COMPONENT_SUMMARY=	Simple cross-platform colored terminal text in Python
COMPONENT_PROJECT_URL=	https://github.com/tartley/colorama
COMPONENT_FMRI=		library/python/colorama
COMPONENT_CLASSIFICATION= Development/Python 
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	$(call pypi_url)	
COMPONENT_ARCHIVE_HASH= \
	sha256:05eed71e2e327246ad6b38c540c4a3117230b19679b875190486ddd2d721422d
COMPONENT_LICENSE=	BSD 3 Clause
COMPONENT_LICENSE_FILE=	LICENSE.txt

PYTHON_VERSIONS=	3.5

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

build:          $(BUILD_NO_ARCH)

install:        $(INSTALL_NO_ARCH)

test:           $(NO_TESTS)

# Auto-generated dependencies
