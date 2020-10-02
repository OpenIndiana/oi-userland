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
# Copyright 2016 Alexander Pyhalov
# Copyright 2018 Michal Nowak
#

BUILD_BITS = 64
BUILD_STYLE = setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ccsm
COMPONENT_VERSION=	0.8.18
COMPONENT_PROJECT_URL=	http://www.northfield.ws
COMPONENT_SUMMARY=	ccsm settings manager for the CompizConfig system
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
	sha256:341843735c03a55c3a37c9e542c897ea153fff020896f0980487a4c0e5c152fd
COMPONENT_ARCHIVE_URL=	http://www.northfield.ws/projects/compiz/releases/$(COMPONENT_VERSION)/$(COMPONENT_SRC).tar.xz
COMPONENT_FMRI=		desktop/compiz/ccsm

PYTHON_VERSION = 3.5
PYTHON_VERSIONS = 3.5

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

COMPONENT_BUILD_ARGS += --prefix=/usr

COMPONENT_INSTALL_ARGS =	--prefix=/usr
COMPONENT_INSTALL_ARGS +=	--root=$(PROTO_DIR)
COMPONENT_INSTALL_ARGS +=	--install-lib=$(PYTHON_LIB)
COMPONENT_INSTALL_ARGS +=	--install-purelib=$(PYTHON_LIB)
COMPONENT_INSTALL_ARGS +=	--install-platlib=$(PYTHON_LIB)
COMPONENT_INSTALL_ARGS +=	--force

COMPONENT_POST_BUILD_ACTION = \
		(cd $(SOURCE_DIR);\
		$(GSED) -i -e '1 i\#!$(PYTHON)' ccm/*.py{,.in} )

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/pycairo-35
REQUIRED_PACKAGES += library/python/pygobject-3-35
REQUIRED_PACKAGES += library/python/python-compizconfig-35
REQUIRED_PACKAGES += library/python/python-xlib-35
REQUIRED_PACKAGES += runtime/python-35
