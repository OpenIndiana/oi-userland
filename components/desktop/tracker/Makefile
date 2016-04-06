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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= tracker

COMPONENT_VERSION= 0.10.37
COMPONENT_REVISION= 3
COMPONENT_SUMMARY= Desktop search tool
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:33d9fe0aa58e2249d1907365676a8fba5686e3df0f127b499e18bf2ee170659d
COMPONENT_ARCHIVE_URL= \
  http://download.gnome.org/sources/$(COMPONENT_NAME)/0.10/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.tracker-project.org

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CFLAGS	+= -D__EXTENSIONS__
CFLAGS	+= -DO_NOATIME=0
# illumos-gate provides libuuid, but not uuid.pc
LDFLAGS += -luuid

COMPONENT_PREP_ACTION= ( cd $(@D) && \
                libtoolize --force &&\
                aclocal -I . &&\
                autoheader &&\
                automake -a -c -f &&\
                autoconf )

COMPONENT_PRE_CONFIGURE_ACTION =        ( $(CLONEY) $(SOURCE_DIR) $(@D) )

CONFIGURE_ENV    += PERL=$(PERL)

COMPONENT_BUILD_ENV += CC=$(CC)
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

COMPONENT_INSTALL_ENV+= GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

build: $(BUILD_32)

install: $(INSTALL_32)

REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += gnome/file-manager/nautilus
REQUIRED_PACKAGES += image/library/libexif
REQUIRED_PACKAGES += image/library/libjpeg6
REQUIRED_PACKAGES += image/library/libjpeg6-ijg
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/audio/gstreamer
REQUIRED_PACKAGES += library/audio/gstreamer/plugin/base
REQUIRED_PACKAGES += library/desktop/evolution-data-server
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/libgsf
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/search/tracker
REQUIRED_PACKAGES += library/giflib
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/gnome-keyring
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += library/libpoppler
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/media-player/totem-pl-parser
REQUIRED_PACKAGES += mail/evolution
REQUIRED_PACKAGES += service/hal
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += system/library/math
