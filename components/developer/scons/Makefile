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
#

BUILD_BITS=NO_ARCH
BUILD_STYLE=setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		scons
COMPONENT_VERSION=	4.0.1
COMPONENT_PROJECT_URL=	http://scons.org/
COMPONENT_SUMMARY=	SConstruct, a software building tool
COMPONENT_SRC_NAME=	SCons
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:722ed104b5c624ecdc89bd4e02b094d2b14d99d47b5d0501961e47f579a2007c
COMPONENT_ARCHIVE_URL=	https://sourceforge.net/projects/scons/files/scons/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_FMRI=		developer/build/scons
COMPONENT_CLASSIFICATION=Development/Distribution Tools
COMPONENT_LICENSE_FILE=	LICENSE
COMPONENT_LICENSE=	MIT

PYTHON_VERSIONS=3.9

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PKG_MACROS += PYVER=$(PYTHON_VERSION)

# pkgdepend doesn't like the first line of a Python script to be:
# '#!/usr/bin/env python' so turn it into '#!/usr/bin/python$(PYTHON_VERSION)'
COMPONENT_POST_INSTALL_ACTION += \
	$(GSED) -i -e 's?env python?python$(PYTHON_VERSION)?' \
		$(PROTOUSRBINDIR)/*;

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/importlib-metadata-39
REQUIRED_PACKAGES += library/python/setuptools-39
REQUIRED_PACKAGES += runtime/python-39
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += SUNWcs
