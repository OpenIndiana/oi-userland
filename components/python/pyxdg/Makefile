#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2014 Alexander Pyhalov.  All rights reserved.
#

BUILD_STYLE=setup.py
BUILD_BITS=NO_ARCH

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pyxdg
COMPONENT_VERSION=	0.26
COMPONENT_PROJECT_URL=	http://freedesktop.org/wiki/Software/pyxdg/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:fe2928d3f532ed32b39c32a482b54136fe766d19936afc96c8f00645f9da1a06
COMPONENT_ARCHIVE_URL=	$(call pypi_url)

PYTHON_VERSIONS=	2.7 3.5

TEST_TARGET= $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-35
