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
# Copyright 2014-2016 Alexander Pyhalov
# Copyright 2015 Ken Mays.  All rights reserved.
#

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME= nautilus
COMPONENT_VERSION= 2.32.2.1
COMPONENT_REVISION= 5
COMPONENT_SUMMARY= GNOME file manager
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:802dacc98c697afea2e6201dab1c8c800809f235fff39857983efb4340ecc303
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/2.32/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.gnome.org

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION =        ( cp $(COMPONENT_DIR)/files/*.png $(@D)/icons && cd $(@D)  && \
					libtoolize --copy --force &&\
					intltoolize --force --copy &&\
					gtkdocize &&\
					aclocal -I m4 &&\
					automake -c -f -a &&\
					autoconf )

COMPONENT_PRE_CONFIGURE_ACTION =        (chmod -R u+r $(SOURCE_DIR) && cp -rp $(SOURCE_DIR)/* $(@D) && \
                                        cp -r $(COMPONENT_DIR)/files/po-sun $(@D) && \
                                        cd $(@D)/po-sun && $(MAKE) all )

LDFLAGS += -lsecdb

CONFIGURE_OPTIONS+= --sysconfdir=/etc
CONFIGURE_OPTIONS+= --libexecdir=/usr/lib
CONFIGURE_OPTIONS+= --disable-update-mimedb
CONFIGURE_OPTIONS+= --localstatedir=/var/lib

CONFIGURE_ENV += EXTRA_CORE_MODULES="gnome-vfs-2.0 libgnomeui-2.0"

# CFLAGS are not passed to compiler when g-ir-scanner is used
COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

COMPONENT_INSTALL_ENV += GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

build: $(BUILD_32)

install: $(INSTALL_32)

REQUIRED_PACKAGES += gnome/config/gconf
REQUIRED_PACKAGES += image/library/libexif
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gnome-desktop
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/gnome-vfs
REQUIRED_PACKAGES += library/libunique
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/file-system/zfs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxrender
