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

BUILD_BITS=NO_ARCH
BUILD_STYLE=setup.py
SINGLE_PYTHON_VERSION=yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		scons
COMPONENT_VERSION=	4.3.0
COMPONENT_PROJECT_URL=	http://scons.org/
COMPONENT_SUMMARY=	SConstruct, a software building tool
COMPONENT_SRC_NAME=	SCons
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:2efc81754a4491299c0c64a6230715dfe33f7a3a42a0834a4ce1756af117bdec
COMPONENT_ARCHIVE_URL=	https://downloads.sourceforge.net/scons/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		developer/build/scons
COMPONENT_CLASSIFICATION=Development/Distribution Tools
COMPONENT_LICENSE_FILE=	LICENSE
COMPONENT_LICENSE=	MIT

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += shell/bash
