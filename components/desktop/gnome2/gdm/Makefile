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
# Copyright 2016 Alexander Pyhalov
#

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME= gdm
COMPONENT_VERSION= 2.30.7
COMPONENT_REVISION=7
COMPONENT_SUMMARY= GNOME display manager
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:d8b258fb0b294cc6cd9715e7375578a6bcc28c829df8d10805d6cbf487af60f2
COMPONENT_ARCHIVE_URL= \
  http://download.gnome.org/sources/gdm/2.30/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://wiki.gnome.org/Projects/GDM

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Missing files in build dir for configure without this.
COMPONENT_PREP_ACTION =        ( cp $(COMPONENT_DIR)/files/box-openindiana.png $(@D)/gui/simple-greeter/box.png &&\
				 cp $(COMPONENT_DIR)/files/logo-openindiana.png $(@D)/gui/simple-greeter/logo.png &&\
				 cp $(COMPONENT_DIR)/files/bottom-panel-image-openindiana.png $(@D)/gui/simple-greeter/bottom-panel-image-gdm.png &&\
				 cp $(COMPONENT_DIR)/files/bkg-openindiana.jpg $(@D)/gui/simple-greeter/bkg.jpg &&\
                                 	$(MKDIR) $(@D)/m4 &&\
					cd  $(@D) &&\
					glib-gettextize -f &&\
					intltoolize --force --copy --automake &&\
					libtoolize --force &&\
					aclocal -I . -I ./m4 &&\
					autoheader &&\
					gnome-doc-prepare --force &&\
					automake -a -c -f &&\
					autoconf )

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

LDFLAGS += -lsecdb
                                        
CONFIGURE_SCRIPT=       $(@D)/configure

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --localstatedir=/var
CONFIGURE_OPTIONS += --libexecdir=/usr/lib
CONFIGURE_OPTIONS += --with-pam-prefix=/etc
CONFIGURE_OPTIONS += --disable-scrollkeeper
CONFIGURE_OPTIONS += --with-default-path=/usr/bin
CONFIGURE_OPTIONS += --enable-rbac-shutdown=solaris.system.shutdown
CONFIGURE_OPTIONS += --enable-ipv6
CONFIGURE_OPTIONS += --with-xauth-dir=/tmp
CONFIGURE_OPTIONS += --with-incomplete-locales
CONFIGURE_OPTIONS += --enable-debug

CONFIGURE_ENV += XGETTEXT=/usr/gnu/bin/xgettext

build: $(BUILD_32)

install: $(INSTALL_32)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += gnome/config/gconf
REQUIRED_PACKAGES += gnome/gnome-panel
REQUIRED_PACKAGES += gnome/gnome-session
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/libbonoboui
REQUIRED_PACKAGES += library/desktop/libxklavier
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/xdg/libcanberra
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libbonobo
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/dbus/dbus-x11
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxau
REQUIRED_PACKAGES += x11/library/libxdmcp
