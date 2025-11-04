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
# Copyright 2015 Alexander Pyhalov
#
include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME= gnome-session
COMPONENT_VERSION= 2.32.1
COMPONENT_REVISION= 0
COMPONENT_SUMMARY= GNOME session manager
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:22d93ce433fcf9c7ce6b5f36dd81f64e692ea0e41faaa0f61159ddac28c3686a
COMPONENT_ARCHIVE_URL= \
  http://download.gnome.org/sources/gnome-session/2.32/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.gnome.org
COMPONENT_FMRI = gnome/gnome-session-2
COMPONENT_CLASSIFICATION = Desktop (GNOME)/Sessions
COMPONENT_LICENSE = GPLv2, LGPLv2
COMPONENT_LICENSE_FILE = COPYING

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION = 	( cd  $(@D) &&\
					libtoolize --force &&\
					intltoolize -c -f --automake &&\
					aclocal -I . -I /usr/share/gettext/m4/ &&\
					autoheader &&\
					automake -a -c -f &&\
					autoupdate && \
					autoconf )

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))
                                        
CFLAGS += -Wno-error=incompatible-pointer-types
CFLAGS += -Wno-error=implicit-function-declaration

LDFLAGS += -lsecdb  -lsocket  -lnsl

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --libexecdir=/usr/lib

COMPONENT_INSTALL_ENV += GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

# Auto-generated dependencies
REQUIRED_PACKAGES += gnome/config/gconf
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxau
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxrender
REQUIRED_PACKAGES += x11/library/libxtst
