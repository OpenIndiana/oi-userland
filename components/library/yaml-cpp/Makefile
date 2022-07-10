#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#
# Copyright (c) 2013 David Hoeppner. All rights reserved.
#
BUILD_BITS=	64
BUILD_STYLE=	cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		yaml-cpp
COMPONENT_VERSION=	0.7.0
COMPONENT_FMRI=	library/yaml-cpp
COMPONENT_SUMMARY= A YAML parser and emitter in C++ matching the YAML 1.2 spec
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_PROJECT_URL=	https://github.com/jbeder/$(COMPONENT_SRC_NAME)
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:43e6a9fcb146ad871515f0d0873947e5d497a1c9c60c58cb102a97b47208b7c3
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE= 	MIT
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DCMAKE_INSTALL_PREFIX=/usr
CMAKE_OPTIONS += -DCMAKE_INSTALL_DATADIR=lib/amd64
CMAKE_OPTIONS += -DBUILD_SHARED_LIBS=ON
CMAKE_OPTIONS += -DYAML_BUILD_SHARED_LIBS=ON
CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
