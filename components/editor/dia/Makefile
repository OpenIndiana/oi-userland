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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           dia
COMPONENT_VERSION=        0.97.3
COMPONENT_REVISION=       1
COMPONENT_PROJECT_URL=    https://wiki.gnome.org/Apps/Dia
COMPONENT_SUMMARY=        Dia Diagram Editor
COMPONENT_SRC=            $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=        \
    sha256:22914e48ef48f894bb5143c5efc3d01ab96e0a0cde80de11058d3b4301377d34
COMPONENT_ARCHIVE_URL=        http://ftp.gnome.org/pub/GNOME/sources/dia/0.97/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin:/usr/perl5/bin

COMPONENT_PREP_ACTION = (cd $(@D) ; autoconf)

CONFIGURE_OPTIONS +=        --sysconfdir=/etc
CONFIGURE_OPTIONS +=        --enable-gnome
CONFIGURE_OPTIONS +=        --with-cairo
CONFIGURE_OPTIONS +=        --disable-static
CONFIGURE_OPTIONS +=        --enable-db2html

# common targets
build:		        $(BUILD_32)

install:     		$(INSTALL_32)

test:			$(NO_TESTS)

REQUIRED_PACKAGES += image/library/libart
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/libgnome
REQUIRED_PACKAGES += library/desktop/libgnomeui
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += text/intltool
