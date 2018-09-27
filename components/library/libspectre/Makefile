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
# Copyright (c) 2013-2017, Aurelien Larcher. All rights reserved.
# Copyright 2014 Andrzej Szeszo.  All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libspectre
COMPONENT_VERSION=      0.2.8
COMPONENT_REVISION=	2
COMPONENT_FMRI=         library/libspectre
COMPONENT_SUMMARY=      libspectre - A small library for rendering Postscript documents
COMPONENT_PROJECT_URL=  https://www.freedesktop.org/wiki/Software/libspectre/
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
  sha256:65256af389823bbc4ee4d25bfd1cc19023ffc29ae9f9677f2d200fa6e98bc7a8
COMPONENT_ARCHIVE_URL=	\
  http://libspectre.freedesktop.org/releases/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      GPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION = ( $(CLONEY) $(SOURCE_DIR) $(@D) ) 

CONFIGURE_OPTIONS+=	--enable-shared
CONFIGURE_OPTIONS+=	--disable-static

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

REQUIRED_PACKAGES += print/filter/ghostscript
REQUIRED_PACKAGES += system/library
