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
# Copyright (c) 2022 Jake Goerzen

PREFERRED_BITS=	64
BUILD_STYLE=	cmake

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		OpenSceneGraph
COMPONENT_VERSION=	3.6.5
COMPONENT_PROJECT_URL=	http://www.openscenegraph.com
COMPONENT_SUMMARY=	OpenSceneGraph - High performance 3D graphics toolkit.
COMPONENT_SRC=		OpenSceneGraph-$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).zip
COMPONENT_ARCHIVE_HASH=	\
	sha256:0e9e3e4cc6f463f21a901934a95e9264b231a1d5db90f72dcb4b8cc94b0d1b3b
COMPONENT_ARCHIVE_URL=  https://github.com/openscenegraph/OpenSceneGraph/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI =	library/openscenegraph
COMPONENT_LICENSE=	OSGPL
COMPONENT_LICENSE_FILE=	LICENSE.txt
COMPONENT_CLASSIFICATION =	System/Libraries

include $(WS_MAKE_RULES)/common.mk

CMAKE_CXX_FLAGS += -std=c++11

# Auto-generated dependencies
