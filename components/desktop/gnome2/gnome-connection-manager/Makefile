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
# Copyright (c) 2015-2021 Jim Klimov
#

BUILD_STYLE = justmake

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME_LONG=	gnome-connection-manager
COMPONENT_NAME_SHORT=	gcm
# The value below should match the .p5m and .license filenames, in particular:
COMPONENT_NAME=  		$(COMPONENT_NAME_LONG)
COMPONENT_VERSION=	1.2.1
COMPONENT_REVISION=	1
# Currently the latest release is a bit behind the Git HEAD on features
# Comment away when switching to future "vanilla" release
COMPONENT_GIT_ORG=	kuthulux
COMPONENT_GIT_REV=	d2f66e3
COMPONENT_GIT_DATE=	20210420
COMPONENT_PROJECT_URL=	http://kuthulu.com/gcm

ifeq (,$(COMPONENT_GIT_REV))
### How the source dir is named in the archive:
COMPONENT_SRC=		$(COMPONENT_NAME_LONG)-$(COMPONENT_VERSION)
### How the original sites name the archive:
COMPONENT_ARCHIVE_ORIG=	v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/$(COMPONENT_GIT_ORG)/$(COMPONENT_NAME_LONG)/archive/$(COMPONENT_ARCHIVE_ORIG)
### How we name the archive to store on build hosts:
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
else
### How the source dir is named in the archive:
COMPONENT_SRC=		$(COMPONENT_GIT_ORG)-$(COMPONENT_NAME_LONG)-$(COMPONENT_GIT_REV)
### How the original sites name the archive:
#COMPONENT_ARCHIVE_ORIG=	v$(COMPONENT_VERSION)-$(COMPONENT_GIT_REV).tar.gz
COMPONENT_ARCHIVE_URL=	https://codeload.github.com/$(COMPONENT_GIT_ORG)/$(COMPONENT_NAME_LONG)/legacy.tar.gz/$(COMPONENT_GIT_REV)
### How we name the archive to store on build hosts:
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION)-$(COMPONENT_GIT_REV).tar.gz
endif

COMPONENT_ARCHIVE_HASH=	\
    sha256:9ab00a8ea22a32e77ad6f225b6da65652c60e097dd125a5e27a07cb5c3dcb659

COMPONENT_SUMMARY=	GCM - an Advanced SSH connections manager for X/Windows
COMPONENT_FMRI=		terminal/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# rules are very simple, because the project is a script - just deliver and run
# unpacked directory is among search paths for the p5m installation anyway

COMPONENT_PRE_BUILD_ACTION =	find $(@D) -name '*.pyc' -exec rm -f '{}' \;
COMPONENT_BUILD_ACTION =	$(PYTHON) -m compileall $(@D)

COMPONENT_INSTALL_ACTION =	true

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/pycairo
PYTHON_REQUIRED_PACKAGES += library/python/pygobject-3
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += shell/expect
REQUIRED_PACKAGES += shell/ksh93
