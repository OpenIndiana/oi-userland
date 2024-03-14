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

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ccsm
COMPONENT_VERSION=	0.8.18
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://www.northfield.ws
COMPONENT_SUMMARY=	ccsm settings manager for the CompizConfig system
COMPONENT_CLASSIFICATION=	Applications/Graphics and Imaging
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
	sha256:341843735c03a55c3a37c9e542c897ea153fff020896f0980487a4c0e5c152fd
COMPONENT_ARCHIVE_URL=	http://www.northfield.ws/projects/compiz/releases/$(COMPONENT_VERSION)/$(COMPONENT_SRC).tar.xz
COMPONENT_FMRI=		desktop/compiz/ccsm
COMPONENT_LICENSE=	GPL-2.0-only
COMPONENT_LICENSE_FILE=	COPYING

TEST_STYLE = none

SINGLE_PYTHON_VERSION = yes

include $(WS_MAKE_RULES)/common.mk

# This project does not support --no-user-cfg global option for setup.py so we
# need to override default build and install commands.
COMPONENT_BUILD_CMD = $(PYTHON) setup.py build
COMPONENT_INSTALL_CMD = $(PYTHON) setup.py install

# Install common files to /usr
COMPONENT_INSTALL_ARGS += --prefix=/usr
PYTHON_DATA = /usr

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/pygobject-3
PYTHON_REQUIRED_PACKAGES += library/python/python-compizconfig
PYTHON_REQUIRED_PACKAGES += runtime/python
