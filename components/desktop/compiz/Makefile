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
# Copyright (c) 2014 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		compiz
COMPONENT_VERSION=	0.8.10
COMPONENT_REVISION=	3
COMPONENT_FMRI=		desktop/compiz
COMPONENT_PROJECT_URL=	http://www.northfield.ws/
COMPONENT_SUMMARY=	OpenGL compositing window manager
COMPONENT_SRC_NAME=     core
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:6e70bcbc04143efade5e8d90acb9c75823887980da99499782a5a7c5c0eb0060
COMPONENT_ARCHIVE_URL=	http://www.northfield.ws/projects/compiz/releases/$(COMPONENT_VERSION)/$(COMPONENT_SRC_NAME).tar.gz
COMPONENT_CLASSIFICATION=Desktop (GNOME)/Window Managers
COMPONENT_LICENSE_FILE=	compiz.license
COMPONENT_LICENSE=	MIT, LGPLv2.1, GPLv2

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION =        ( cd $(@D) && \
					aclocal -I. && \
				        autoheader && \
			                libtoolize --automake --copy --force && \
					automake -a -f -c &&\
					autoconf &&\
                                        intltoolize )

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--disable-gconf
CONFIGURE_OPTIONS+=	--disable-gnome
CONFIGURE_OPTIONS+=	--disable-metacity
CONFIGURE_OPTIONS+=	--disable-kde
CONFIGURE_OPTIONS+=	--disable-kde4
CONFIGURE_OPTIONS+=	--disable-kconfig
CONFIGURE_OPTIONS+=	--with-default-plugins=core,dbus,move,place,png,regex,resize,svg,switcher,imgjpeg,resizeinfo,session,text,workarounds,decoration,animation,wall,fade,gnomecompat

CONFIGURE_ENV+=	INTLTOOL_PERL=$(PERL)
CONFIGURE_ENV+=	PYTHON=$(PYTHON)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += desktop/mate/marco
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/librsvg
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/libwnck
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/startup-notification
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/glu
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcomposite
REQUIRED_PACKAGES += x11/library/libxdamage
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxfixes
REQUIRED_PACKAGES += x11/library/libxinerama
REQUIRED_PACKAGES += x11/library/libxrandr
REQUIRED_PACKAGES += x11/library/libxrender
