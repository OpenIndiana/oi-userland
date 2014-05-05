#! /usr/bin/sh
#
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
# Copyright 2014 Andrzej Szeszo.  All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		poppler
COMPONENT_VERSION=	0.14.5
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:c805317c4c1a7080098ae8c7c2a1c1b8e2c784858fc2e04941878eeb8164814c
COMPONENT_ARCHIVE_URL= \
     http://poppler.freedesktop.org/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://poppler.freedesktop.org/
COMPONENT_AUTOGEN_MANIFEST=	yes
COMPONENT_FMRI=		library/libpoppler
COMPONENT_SUMMARY=	Poppler is a PDF rendering library based on the xpdf-3.0 code base
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING


include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

COMPONENT_PREP_ACTION += \
    cd $(@D); autoreconf --install --force

COMPONENT_POST_INSTALL_ACTION += \
	$(RM) $(PROTO_DIR)$(CONFIGURE_LIBDIR.$(BITS))/*.{a,la}

CFLAGS += $($(COMPILER)_C99_ENABLE)

CONFIGURE_OPTIONS += CPPFLAGS="$(CPP_XPG6MODE) $(CPP_LARGEFILES)"
CONFIGURE_OPTIONS += CXX="$(CXX) $($(COMPILER)_NORUNPATH)"
CONFIGURE_OPTIONS += --enable-poppler-glib
CONFIGURE_OPTIONS += --disable-poppler-qt
CONFIGURE_OPTIONS += --disable-poppler-qt4
CONFIGURE_OPTIONS += --enable-zlib
CONFIGURE_OPTIONS += --enable-xpdf-headers

build:	$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)
