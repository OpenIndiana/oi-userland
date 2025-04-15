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

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnome-settings-daemon
COMPONENT_VERSION=	2.32.1
COMPONENT_REVISION=	0
COMPONENT_PROJECT_URL=	http://www.gnome.org
COMPONENT_SUMMARY=	The GNOME settings daemon
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:0074b3fec3ad6e3ab91a05dc20906b06101ea8bca0cd2caf394a5cc141b05e86
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/$(basename $(COMPONENT_VERSION))/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_FMRI= gnome/gnome-settings-daemon-2
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE= 	GPLv2

include $(WS_TOP)/make-rules/common.mk

PATH=/usr/gnu/bin:/usr/bin

LDFLAGS.32 += -L/usr/lib/mps -R/usr/lib/mps
LDFLAGS += $(LDFLAGS.$(BITS))

COMPONENT_PREP_ACTION =        ( cd $(@D) && \
                                        aclocal -I. -I /usr/share/gettext/m4 && \
                                        autoheader && \
                                        libtoolize --automake --copy --force && \
                                        automake -a -f -c &&\
                                        autoconf )

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =	($(CLONEY) $(SOURCE_DIR) $(@D))

CFLAGS += -DDBUS_API_SUBJECT_TO_CHANGE -DGNOME_DESKTOP_USE_UNSTABLE_API -I/usr/X11/share/include
CFLAGS += -Wno-error=incompatible-pointer-types
CFLAGS += -Wno-error=implicit-function-declaration
CFLAGS += -Wno-error=int-conversion

LDFLAGS += -L/usr/X11/lib -R/usr/X11/lib -lfreetype -lresolv -lgthread-2.0

CONFIGURE_OPTIONS+=	--disable-static
CONFIGURE_OPTIONS+=	--disable-aboutme
CONFIGURE_OPTIONS+=	--disable-pulse
CONFIGURE_OPTIONS+=	--disable-gstreamer
CONFIGURE_OPTIONS+=	--disable-cups

CONFIGURE_OPTIONS+=	--enable-debug
CONFIGURE_OPTIONS+=	--disable-silent-rules

COMPONENT_INSTALL_ENV+= GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

# Auto-generated dependencies
REQUIRED_PACKAGES += gnome/config/gconf
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gnome-desktop-2
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/libxklavier
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/libgnomekbd
REQUIRED_PACKAGES += library/libnotify
REQUIRED_PACKAGES += library/nspr
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/mozilla-nss
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxi
