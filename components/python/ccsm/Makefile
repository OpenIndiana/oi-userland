#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# This file was automatically generated using the following command:
#   $WS_TOOLS/python-integrate-project ccsm
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		ccsm
HUMAN_VERSION =			0.8.18
COMPONENT_REVISION =		2
COMPONENT_SUMMARY =		ccsm settings manager for the CompizConfig system
COMPONENT_PROJECT_URL =		http://www.northfield.ws
COMPONENT_ARCHIVE_URL =		\
	http://www.northfield.ws/projects/compiz/releases/$(HUMAN_VERSION)/ccsm-$(HUMAN_VERSION).tar.xz
COMPONENT_ARCHIVE_HASH =	\
	sha256:341843735c03a55c3a37c9e542c897ea153fff020896f0980487a4c0e5c152fd
COMPONENT_LICENSE =		GPL-2.0-only
COMPONENT_LICENSE_FILE =	COPYING

TEST_STYLE = none

COMPONENT_CLASSIFICATION =	Applications/Graphics and Imaging
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.xz
COMPONENT_FMRI =		desktop/compiz/ccsm

# This is a standalone application.  Since no other Python project depends on
# it we just provide single unversioned package.
SINGLE_PYTHON_VERSION = yes

include $(WS_MAKE_RULES)/common.mk

# This project does not support --no-user-cfg global option for setup.py so we
# need to override default build and install commands.
COMPONENT_BUILD_CMD = $(PYTHON) setup.py build
COMPONENT_INSTALL_CMD = $(PYTHON) setup.py install

# Install common files to /usr
COMPONENT_INSTALL_ARGS += --prefix=$(USRDIR)
PYTHON_DATA = $(USRDIR)

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/pygobject
PYTHON_REQUIRED_PACKAGES += library/python/python-compizconfig
PYTHON_REQUIRED_PACKAGES += runtime/python
