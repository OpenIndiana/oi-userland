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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		poppler
COMPONENT_VERSION=	0.32.0
COMPONENT_REVISION=	1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
    sha256:4963e31ba5e17530a87b16588e22928bc044e8d28d02303dded981bff6725b98
COMPONENT_ARCHIVE_URL= \
     http://poppler.freedesktop.org/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://poppler.freedesktop.org/
COMPONENT_FMRI=		library/libpoppler
COMPONENT_SUMMARY=	Poppler is a PDF rendering library based on the xpdf-3.0 code base
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries


include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

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

COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CXX="$(CXX)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

build:	$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)
