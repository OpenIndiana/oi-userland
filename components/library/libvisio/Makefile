#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.illumos.org/license/CDDL.
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
# Copyright (c) 2017, Aurelien Larcher. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libvisio
COMPONENT_VERSION=      0.1.5
COMPONENT_FMRI=         library/c++/libvisio
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_PROJECT_URL=  https://wiki.documentfoundation.org/DLP/Libraries/libvisio
COMPONENT_SUMMARY=      libvisio - library for reading Microsoft Visio documents
COMPONENT_SRC=    $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:430a067903660bb1b97daf4b045e408a1bb75ca45e615cf05fb1a4da65fc5a8c
COMPONENT_ARCHIVE_URL=  http://dev-www.libreoffice.org/src/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      MPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Fix threading detection issue with boost 1.64
CXXFLAGS+= -std=c++11 -pthread

CONFIGURE_OPTIONS+=  --enable-shared
CONFIGURE_OPTIONS+=  --disable-static

unexport SHELLOPTS

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/c++/librevenge
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-4-runtime
REQUIRED_PACKAGES += system/library/gcc-4-runtime
REQUIRED_PACKAGES += system/library/math
