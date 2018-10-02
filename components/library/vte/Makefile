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
# Copyright 2016 Alexander Pyhalov
# Copyright 2018 Ken Mays
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		vte
COMPONENT_VERSION=	0.54.1
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://www.gnome.org
COMPONENT_SUMMARY=	Terminal emulation widget for GTK+
COMPONENT_FMRI=		library/desktop/vte
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:a724fa0543c689e30a3d0ff07e4195a86dc7c4fe57b469be97c7c87f27604e53
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/vte/$(COMPONENT_NAME)/0.54/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

CFLAGS+= -std=c99 $(CPP_XPG6MODE)

COMPONENT_PREP_ACTION = ( cd $(@D)  &&\
                          libtoolize --force &&\
                          gtkdocize &&\
                          aclocal -I . &&\
                          autoconf &&\
                          autoheader &&\
                          automake -c -f -a )

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--disable-scrollkeeper
CONFIGURE_OPTIONS+=	--libexecdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS+=	--localstatedir=/var/lib
CONFIGURE_OPTIONS+=	--disable-Bsymbolic

CFLAGS += $(CPP_XPG6MODE) -std=c99

CONFIGURE_ENV +=	PYTHON=$(PYTHON)

COMPONENT_POST_INSTALL_ACTION = ( mv -f $(PROTO_DIR)/usr/lib/python3.4/site-packages/gtk-3.0/vtemodule.so \
	$(PROTO_DIR)/usr/lib/python3.4/site-packages/gtk-3.0/vtemodule-$(BITS).so)

# common targets

$(INSTALL_32):	$(INSTALL_64)

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
