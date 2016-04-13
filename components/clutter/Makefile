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
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		clutter
COMPONENT_VERSION=	1.6.20
COMPONENT_SUMMARY= clutter - a library for creating fast, visually rich and animated graphical user interfaces
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Projects/Clutter
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
  sha256:c5508856e51343ef0f5cf5a8526e4372ac96d31b740d6b09d37e890c653b4273
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/1.6/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION += ( $(CLONEY) $(SOURCE_DIR) $(@D) && \
					mkdir -p $(@D)/mesa/GL && \
					ln -s /usr/include/mesa/*.h $(@D)/mesa/GL )

PATH=/usr/gnu/bin:/usr/bin

CONFIGURE_SCRIPT=	$(@D)/configure

CFLAGS+=	-I$(@D)/mesa
CXXFLAGS+=	-I$(@D)/mesa
LDFLAGS.32 =	-L/usr/lib/mesa -L/usr/X11/lib -R/usr/X11/lib -lX11
LDFLAGS.64 =	-L/usr/lib/mesa/$(MACH64) -L/usr/X11/lib/$(MACH64) -R/usr/X11/lib/$(MACH64) -lX11

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--disable-static
CONFIGURE_OPTIONS+=	--enable-gtk-doc

# Tell g-ir-scanner about compiler
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += CC="$(CC)"

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)
