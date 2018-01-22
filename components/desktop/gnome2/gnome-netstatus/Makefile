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
# Copyright 2017 Gary Mills
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
#

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME= gnome-netstatus
COMPONENT_VERSION= 2.28.2
COMPONENT_SUMMARY= GNOME Network Monitor Applet
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:d1ad0a668a1344898d4f47b5591adddc7791edb6c2e92136ebcf8d278d959119
COMPONENT_ARCHIVE_URL= \
  http://download.gnome.org/sources/$(COMPONENT_NAME)/2.28/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.gnome.org

COMPONENT_ARCHIVE_1= gnome-netstatus-wireless-icons-0.2.tar.gz
COMPONENT_ARCHIVE_HASH_1= \
  sha256:6deec433ea1a34278b6538e8765f0b58fbc861e2befd119f8a0d54bd6a95d5f7
COMPONENT_ARCHIVE_URL_1= http://dlc.openindiana.org/oi/jds/downloads/sources/$(COMPONENT_ARCHIVE_1)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH = $(PATH.gnu)

COMPONENT_PRE_CONFIGURE_ACTION =        ($(CHMOD) -R u+r  $(SOURCE_DIR) && \
                                        cp -r $(SOURCE_DIR)/* $(@D) && \
                                        cp -r $(COMPONENT_DIR)/files/po-sun $(@D) && \
                                        cd $(@D)/po-sun && $(MAKE) all &&\
                                        cd $(@D) && gnome-doc-common &&\
					gnome-doc-prepare --force &&\
					libtoolize --force &&\
                                        intltoolize --force --copy --automake &&\
                                        aclocal -I . &&\
                                        autoheader &&\
                                        automake -Wno-portability -a -f -c &&\
                                        autoconf )

CONFIGURE_SCRIPT=       $(@D)/configure

COMPONENT_POST_UNPACK_ACTION += (cd $(COMPONENT_SRC)/icons && $(UNPACK) $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_1))

CONFIGURE_ENV	+= LIBS="-lm"

CONFIGURE_OPTIONS+= --sysconfdir=/etc
CONFIGURE_OPTIONS+= --libexecdir=/usr/lib
CONFIGURE_OPTIONS+= --disable-scrollkeeper

COMPONENT_INSTALL_ENV += GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

build: $(BUILD_32)

install: $(INSTALL_32)

# Auto-generated dependencies
REQUIRED_PACKAGES += gnome/config/gconf
REQUIRED_PACKAGES += gnome/gnome-panel
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libbonobo
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
