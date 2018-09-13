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

COMPONENT_NAME=		wcwidth
COMPONENT_VERSION=	0.1.7
COMPONENT_REVISION=	3
COMPONENT_SUMMARY=	Measures number of Terminal column cells of wide-character codes
COMPONENT_PROJECT_URL=	https://github.com/jquast/wcwidth
COMPONENT_FMRI=		library/python/wcwidth
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/jquast/wcwidth/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:c0122eb9a4ef7ab6489d0ef7c72db4143387b9466e27385cd5201950f49583b3
COMPONENT_LICENSE=	MIT

PYTHON_VERSIONS=	2.7 3.4 3.5

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

build:          $(BUILD_NO_ARCH)

install:        $(INSTALL_NO_ARCH)

test:           $(NO_TESTS)

REQUIRED_PACKAGES+= runtime/python-27
REQUIRED_PACKAGES+= runtime/python-34
REQUIRED_PACKAGES+= runtime/python-35
