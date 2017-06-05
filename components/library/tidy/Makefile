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

#
# Copyright 2017, Aurelien Larcher
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tidy
COMPONENT_VERSION=	5.4.0
COMPONENT_FMRI=	text/tidy
COMPONENT_SUMMARY=	The HTML Tidy Library
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_PROJECT_URL=	http://www.html-tidy.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-html5-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
  sha256:a2d754b7349982e33f12d798780316c047a3b264240dc6bbd4641542e57a0b7a
COMPONENT_ARCHIVE_URL= \
  https://github.com/htacg/tidy-html5/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	W3C

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk

# Install 64-bit binaries only
CMAKE_OPTIONS+= -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS+= -DLIB_SUFFIX=/$(ARCHLIBSUBDIR$(BITS))
CMAKE_OPTIONS+= -DBUILD_TAB2SPACE=ON

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)
	$(INSTALL) -v -m755 $(BUILD_DIR_64)/tab2space $(PROTOUSRBINDIR)

test:		$(NO_TESTS)

