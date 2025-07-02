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

BUILD_BITS= 64_and_32
include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME= gdm
COMPONENT_VERSION= 2.30.7
COMPONENT_SUMMARY= GNOME display manager
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:d8b258fb0b294cc6cd9715e7375578a6bcc28c829df8d10805d6cbf487af60f2
COMPONENT_ARCHIVE_URL= \
  http://download.gnome.org/sources/gdm/2.30/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://wiki.gnome.org/Projects/GDM
COMPONENT_FMRI= system/display-manager/gdm-2
COMPONENT_CLASSIFICATION=Desktop (GNOME)/Sessions
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	GPLv2

include $(WS_MAKE_RULES)/common.mk

# Missing files in build dir for configure without this.
COMPONENT_PREP_ACTION =        ( cp $(COMPONENT_DIR)/files/box-openindiana.png $(@D)/gui/simple-greeter/box.png &&\
				 cp $(COMPONENT_DIR)/files/logo-openindiana.png $(@D)/gui/simple-greeter/logo.png &&\
				 cp $(COMPONENT_DIR)/files/bottom-panel-image-openindiana.png $(@D)/gui/simple-greeter/bottom-panel-image-gdm.png &&\
				 cp $(COMPONENT_DIR)/files/bkg-openindiana.jpg $(@D)/gui/simple-greeter/bkg.jpg &&\
					$(MKDIR) $(@D)/m4 )

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION_32 =        ($(CLONEY) $(SOURCE_DIR) $(@D) ; \
					cd  $(@D) &&\
					rm aclocal.m4 && \
					> gnome-doc-utils.make && \
					mv Makefile.am Makefile.am.link &&\
					cp Makefile.am.link Makefile.am &&\
					$(GPATCH) -p1 -i $(COMPONENT_DIR)/$(PATCH_DIR)/gdm-build.patch32 &&\
					rm m4/gnome-doc-utils.m4 && \
					intltoolize --force --copy --automake &&\
					libtoolize --force &&\
					aclocal -I . -I ./m4 -I /usr/share/gettext/m4 &&\
					autoheader &&\
					automake -a -c -f &&\
					autoconf; \
				)
COMPONENT_PRE_CONFIGURE_ACTION_64 =        ($(CLONEY) $(SOURCE_DIR) $(@D) ; \
					cd  $(@D) &&\
					rm aclocal.m4 && \
					> gnome-doc-utils.make && \
					rm m4/gnome-doc-utils.m4 && \
					intltoolize --force --copy --automake &&\
					libtoolize --force &&\
					aclocal -I . -I ./m4 -I /usr/share/gettext/m4 &&\
					autoheader &&\
					automake -a -c -f &&\
					autoconf; \
				)
COMPONENT_PRE_CONFIGURE_ACTION = $(COMPONENT_PRE_CONFIGURE_ACTION_$(BITS))

LDFLAGS += -lsecdb
CFLAGS += -Wno-incompatible-pointer-types
CFLAGS += -Wno-unused-variable
CFLAGS += -Wno-unused-function
CFLAGS += -Wno-deprecated-declarations
CFLAGS += -Wno-stringop-truncation
CFLAGS += -Wno-return-type
CFLAGS += -Wno-maybe-uninitialized
CFLAGS += -Wno-int-conversion
CFLAGS += -Wno-implicit-function-declaration
CFLAGS += -Wno-discarded-qualifiers

CONFIGURE_SCRIPT=       $(@D)/configure

# CONFIGURE_LIBEXECDIR.64 = $(CONFIGURE_PREFIX)/libexec/$(MACH64)
# CONFIGURE_LIBEXECDIR.32 = $(CONFIGURE_PREFIX)/libexec/$(MACH32)
# CONFIGURE_LIBEXECDIR = $(CONFIGURE_LIBEXECDIR.$(BITS))

CONFIGURE_OPTIONS += --with-pam-prefix=/etc
CONFIGURE_OPTIONS += --disable-scrollkeeper
CONFIGURE_OPTIONS += --with-default-path=/usr/bin
CONFIGURE_OPTIONS += --enable-rbac-shutdown=solaris.system.shutdown
CONFIGURE_OPTIONS += --enable-ipv6
CONFIGURE_OPTIONS += --with-xauth-dir=/tmp
CONFIGURE_OPTIONS += --with-incomplete-locales
CONFIGURE_OPTIONS += --enable-debug
CONFIGURE_OPTIONS += --without-tcp-wrappers
# --enable-console-helper, --with-dmconfdir, --enable-schemas-install, --enable-authentication-scheme, --with-xinerama, --with-xdmcp,
# --with-console-kit, --with-at-spi-registryd-directory, --with-lang-file, --with-user=gdm
# ac_cv_header_stropts_h

CONFIGURE_ENV += XGETTEXT=/usr/gnu/bin/xgettext

# Auto-generated dependencies
REQUIRED_PACKAGES += gnome/config/gconf
REQUIRED_PACKAGES += gnome/gnome-session-2
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/libxklavier
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/xdg/libcanberra
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/glib2/32
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/dbus/dbus-x11
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxau
REQUIRED_PACKAGES += x11/library/libxdmcp
