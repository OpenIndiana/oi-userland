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
# Copyright 2016 Jim Klimov
# Copyright 2021 Aurelien Larcher
# Copyright 2023 Klaus Ziegler
#

BUILD_BITS= NO_ARCH
BUILD_STYLE= setup.py
SINGLE_PYTHON_VERSION= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		scons
COMPONENT_VERSION=	4.4.0
COMPONENT_SUMMARY=	SConstruct, a software building tool
COMPONENT_PROJECT_URL=	https://scons.org/
COMPONENT_SRC_NAME=	SCons
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:3d43b2303a924816ea0e1b345ff04c9b3e27b53eadf0f26012fc0c29b019685f
COMPONENT_ARCHIVE_URL=	https://downloads.sourceforge.net/scons/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		developer/build/scons
COMPONENT_CLASSIFICATION=Development/Distribution Tools
COMPONENT_LICENSE_FILE=	LICENSE
COMPONENT_LICENSE=	MIT

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/libxml2
PYTHON_REQUIRED_PACKAGES += library/python/libxslt
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += SUNWcs
