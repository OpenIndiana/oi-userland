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
# Copyright 2022 Daniel Chan
#

BUILD_STYLE=	cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=				md4c
COMPONENT_VERSION=			0.4.8
COMPONENT_REVISION=			2
COMPONENT_SUMMARY=			Markdown parser library in C, and md2html converter
COMPONENT_PROJECT_URL=		https://github.com/mity
COMPONENT_GIT_TAG=			release-$(COMPONENT_VERSION)
COMPONENT_SRC=				$(COMPONENT_NAME)-$(COMPONENT_GIT_TAG)
COMPONENT_ARCHIVE=      	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=  	$(COMPONENT_PROJECT_URL)/$(COMPONENT_NAME)/archive/refs/tags/$(COMPONENT_GIT_TAG).tar.gz
COMPONENT_ARCHIVE_HASH=		sha256:4a457df853425b6bb6e3457aa1d1a13bccec587a04c38c622b1013a0da41439f
COMPONENT_FMRI=				library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= 	Desktop (GNOME)/Libraries
COMPONENT_LICENSE=			MIT
COMPONENT_LICENSE_FILE=		LICENSE.md

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DCMAKE_INSTALL_LIBDIR=/usr/lib/$(MACH64)
CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
