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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		prompt-toolkit
COMPONENT_VERSION=	1.0.7
COMPONENT_SUMMARY=	Library for building powerful interactive command lines in Python
COMPONENT_PROJECT_URL=	https://github.com/jonathanslenders/python-prompt-toolkit
COMPONENT_FMRI=		library/python/$(COMPONENT_NAME)-$(PYVER)
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_SRC=          python-$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/jonathanslenders/python-prompt-toolkit/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:6969e90c0ca460ab8ca9d12f784d1f88970ee925ca2968f758c233991bc7017e
COMPONENT_LICENSE=	BSD

PYTHON_VERSIONS=	2.7 3.4

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

build:          $(BUILD_NO_ARCH)

install:        $(INSTALL_NO_ARCH)

test:           $(NO_TESTS)

REQUIRED_PACKAGES+= runtime/python-27
REQUIRED_PACKAGES+= runtime/python-34
