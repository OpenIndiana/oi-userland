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
# Copyright 2019 Tim Mooney.  All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		cogl
COMPONENT_VERSION=	1.22.4
COMPONENT_FMRI=		library/desktop/cogl
COMPONENT_SUMMARY=	a library for using 3D graphics hardware for rendering
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_PROJECT_URL=	https://developer.gnome.org/cogl/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
  sha256:5217bf94cbca3df63268a3b79d017725382b9e592b891d1e7dc6212590ce0de0
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/1.22/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	MIT, SGI Free Software License B version 2.0, 3-clause BSD, public domain
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION += ( $(CLONEY) $(SOURCE_DIR) $(@D) && \
					mkdir -p $(@D)/mesa/GL && \
					ln -s /usr/include/mesa/*.h $(@D)/mesa/GL )

PATH=$(PATH.gnu)

CONFIGURE_SCRIPT=	$(@D)/configure

CFLAGS+=	-I$(@D)/mesa
CXXFLAGS+=	-I$(@D)/mesa
LDFLAGS.32 =	-L/usr/lib/mesa -L/usr/X11/lib -R/usr/X11/lib -lX11
LDFLAGS.64 =	-L/usr/lib/mesa/$(MACH64) -L/usr/X11/lib/$(MACH64) -R/usr/X11/lib/$(MACH64) -lX11

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--disable-static
CONFIGURE_OPTIONS+=	--enable-gtk-doc
CONFIGURE_OPTIONS+=	--enable-xlib-egl-platform=yes
CONFIGURE_OPTIONS+=	--enable-cogl-gst=yes

# Tell g-ir-scanner about compiler
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += CC="$(CC)"

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

# build dependency
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc

# Auto-generated dependencies
REQUIRED_PACKAGES += library/audio/gstreamer1
REQUIRED_PACKAGES += library/audio/gstreamer1/plugin/base
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxdamage
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxfixes
REQUIRED_PACKAGES += x11/library/libxrandr
