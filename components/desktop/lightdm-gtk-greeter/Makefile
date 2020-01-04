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
# Copyright 2020 Michal Nowak
#

BUILD_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		lightdm-gtk-greeter
COMPONENT_VERSION=	2.0.7
COMPONENT_SUMMARY=	LightDM GTK+ Greeter
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:bae293f21286e93113ee7965a3a8734bbee6b94f3c74d8723dcae13dda60fcbc
COMPONENT_ARCHIVE_URL= \
	https://launchpad.net/lightdm-gtk-greeter/2.0/$(COMPONENT_VERSION)/+download/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://launchpad.net/lightdm-gtk-greeter/
COMPONENT_FMRI=		system/display-manager/lightdm/gtk-greeter
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Sessions
COMPONENT_LICENSE=		GPLv3
COMPONENT_LICENSE_FILE=		COPYING

EXO_COMMIT=accb025add4338618ea66f5dab67f51965e216f0
COMPONENT_ARCHIVE_1= exo-csource.c 
COMPONENT_ARCHIVE_URL_1= https://github.com/xfce-mirror/exo/raw/$(EXO_COMMIT)/exo-csource/main.c
COMPONENT_ARCHIVE_HASH_1= sha256:1942f5c2e649c83ad5739af7bb0de90bd9b874e9c5f300ff4551f9e8628a74aa

TEST_TARGET=	$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# We need exo-csource to regenerate headers from glade file,
# but we do not want to build all exo XFCE dependencies,
# so download and build local copy.
EXO_CSOURCE_CFLAGS += -DHAVE_LOCALE_H -DHAVE_LIBINTL_H -DHAVE_STDLIB_H -DHAVE_LOCALE_H -DGETTEXT_PACKAGE=\"exo-csource\"
EXO_CSOURCE_CFLAGS += -DPACKAGE_LOCALE_DIR=\"/usr/share/locale/\" -DPACKAGE_VERSION=\"0.10.7\"
EXO_CSOURCE_CFLAGS += -D PACKAGE_TARNAME=\"unspecified\"  -DPACKAGE_BUGREPORT=\"no\"
EXO_CSOURCE_CFLAGS += $(shell pkg-config --cflags glib-2.0)
EXO_CSOURCE_LDFLAGS += $(shell pkg-config --libs glib-2.0)

PATH=$(PATH.gnu):$(BUILD_DIR)/exo-csource

$(BUILD_DIR)/exo-csource/exo-csource: $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_1)
	$(MKDIR) $(@D)
	$(CC) $(EXO_CSOURCE_CFLAGS) $(EXO_CSOURCE_LDFLAGS) $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_1) -o $@

$(SOURCE_DIR)/.prep:	$(BUILD_DIR)/exo-csource/exo-csource

COMPONENT_PREP_ACTION = (cd $(@D) && autoreconf -fi)

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --localstatedir=/var
CONFIGURE_OPTIONS += --libexecdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS += --disable-indicator-services-command
CONFIGURE_OPTIONS += --disable-at-spi-command
CONFIGURE_OPTIONS += --enable-maintainer-mode

CONFIGURE_ENV += XGETTEXT=/usr/gnu/bin/xgettext

# gobject-introspection
COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/display-manager/lightdm
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
