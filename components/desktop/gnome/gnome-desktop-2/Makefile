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
# Copyright (c) 2014 Ken Mays
#

BUILD_STYLE= configure
include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnome-desktop
COMPONENT_VERSION=	2.32.1
COMPONENT_REVISION=	0
COMPONENT_PROJECT_URL=	http://www.gnome.org
COMPONENT_SUMMARY=	Gnome Desktop Library
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:55cbecf67efe1fa1e57ac966520a7c46d799c8ba3c652a1219f60cafccb3739d
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/$(basename $(COMPONENT_VERSION))/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI= library/desktop/gnome-desktop-2
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE= COPYING

include $(WS_TOP)/make-rules/common.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION =        ( cd $(@D)  && \
					libtoolize --copy --force &&\
					intltoolize --force --copy &&\
					aclocal -I m4 -I /usr/share/gettext/m4 --install &&\
					autoconf &&\
					autoheader &&\
					automake -c -f -a )

COMPONENT_PRE_CONFIGURE_ACTION =        (chmod -R u+r $(SOURCE_DIR) && cp -rp $(SOURCE_DIR)/* $(@D) && \
                                        cp -r $(COMPONENT_DIR)/files/po-sun $(@D) && \
                                        cd $(@D)/po-sun && $(MAKE) all )

CFLAGS+= -Wno-error=incompatible-pointer-types
CFLAGS+= -Wno-error=deprecated-declarations

CONFIGURE_OPTIONS+=	--disable-static
CONFIGURE_OPTIONS+=	--disable-scrollkeeper
CONFIGURE_OPTIONS+=	--with-gnome-distributor="The OpenIndiana Project"
CONFIGURE_OPTIONS+=	--with-gnome-distributor-version="GNOME $(COMPONENT_VERSION) Desktop"
CONFIGURE_OPTIONS+=	--disable-desktop-docs

CONFIGURE_ENV+= PYTHON="$(PYTHON)"

# Auto-generated dependencies
REQUIRED_PACKAGES += gnome/config/gconf
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/startup-notification
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxrandr
