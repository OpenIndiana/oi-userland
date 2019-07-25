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
COMPONENT_REVISION=       3
COMPONENT_COMMIT=         b86085dfe2b048a2d37d587adf8ceba6fb8bc43c
COMPONENT_PROJECT_URL=    https://wiki.gnome.org/Apps/Dia
COMPONENT_SUMMARY=        Dia Diagram Editor
COMPONENT_SRC=            $(COMPONENT_NAME)-$(COMPONENT_COMMIT)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_HASH=        \
    sha256:447b6979829aa5f4989b8ac5c0685b25f8b8ec740e87853af113891b6e9c2738
COMPONENT_ARCHIVE_URL=        https://github.com/GNOME/$(COMPONENT_NAME)/archive/$(COMPONENT_COMMIT).zip
COMPONENT_FMRI=	editor/diagram/dia
COMPONENT_CLASSIFICATION=	Applications/Graphics and Imaging
COMPONENT_LICENSE = 	GPLv2
COMPONENT_LICENSE_FILE = COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION = (cd $(@D) && intltoolize --force --copy &&\
				autoreconf -fi)

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SCRIPT =	$(@D)/configure

CONFIGURE_OPTIONS +=        --sysconfdir=/etc
CONFIGURE_OPTIONS +=        --disable-gnome
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
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += text/intltool
