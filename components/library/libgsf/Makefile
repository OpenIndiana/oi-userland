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
# Copyright 2019 Jason Martin
# Copyright 2021 Andreas Wacknitz
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libgsf
COMPONENT_VERSION_MAJOR= 1.14
COMPONENT_VERSION= $(COMPONENT_VERSION_MAJOR).53
COMPONENT_SUMMARY= GNOME Structured File Library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:0eb59a86e0c50f97ac9cfe4d8cc1969f623f2ae8c5296f2414571ff0a9e8bcba
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPONENT_VERSION_MAJOR)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://www.gnome.org
COMPONENT_FMRI= library/desktop/libgsf
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Libraries
COMPONENT_LICENSE= LGPLv2.1
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_PREP_ACTION= ( \
	cd $(@D) && \
	libtoolize --copy --force && \
	aclocal -I m4 && \
	autoheader && \
	automake -c -f -a && \
	autoconf && \
	cp /usr/share/gettext/config.rpath . )

# Missing files in build dir without this.
COMPONENT_PRE_CONFIGURE_ACTION= ( $(CLONEY) $(SOURCE_DIR) $(@D) )

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --with-bz2
CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS += --with-zlib
CONFIGURE_OPTIONS += --enable-introspection

COMPONENT_TEST_ENV += CC=$(CC)
COMPONENT_TEST_ARGS= -k -i

# Manually added build dependencies
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
