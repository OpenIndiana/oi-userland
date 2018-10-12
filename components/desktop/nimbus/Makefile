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

COMPONENT_NAME=		nimbus
COMPONENT_VERSION=	0.1.9
COMPONENT_REVISION=	15
COMPONENT_PROJECT_URL=	https://java.net/projects/solaris-desktop/pages/Home
COMPONENT_SUMMARY=	Engine for Sun Nimbus GTK2 Theme
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:aff6aef7a9c5fd8d05aa42da5dd79d8ff86c74730d5a200422e25f42a1430fae
COMPONENT_ARCHIVE_URL=	https://github.com/aszeszo/archives/raw/master/$(COMPONENT_ARCHIVE)

COMPONENT_SRC_1=	nimbus-gtk3-theme-4.2
COMPONENT_ARCHIVE_1=	164641-$(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_HASH_1= sha256:6483b4515165a6b00010587167f34c147808962406d37bc5dd7bac0cbb154d0e
COMPONENT_ARCHIVE_URL_1= https://dl.opendesktop.org/api/files/download/id/1460761469/$(COMPONENT_ARCHIVE_1)
CLEAN_PATHS += $(COMPONENT_SRC_1)

COMPONENT_FMRI=		gnome/theme/nimbus
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Theming
COMPONENT_LICENSE = LGPLv2
COMPONENT_LICENSE_FILE = COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

INSTALL_GTK3_THEME=$(BUILD_DIR)/.gtk3_theme_installed

COMPONENT_PREP_ACTION =        ( cp $(COMPONENT_DIR)/files/nimbus-media-play-rtl.png $(@D)/gtk-engine/gtk-2.0/media-play-rtl.png &&\
					cp -r $(COMPONENT_DIR)/files/icons $(@D) && \
				 	cd $(@D) && \
					libtoolize --copy --force &&\
					glib-gettextize -f &&\
					intltoolize --force --copy &&\
					aclocal -I . &&\
					automake -c -f -a &&\
					autoconf )

# Missing files in build dir without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SCRIPT=$(SOURCE_DIR)/autogen.sh

CONFIGURE_OPTIONS += --sysconfdir=/etc

$(INSTALL_GTK3_THEME):	$(INSTALL_32_and_64)
	cp -r $(COMPONENT_SRC_1)/*nimbus* $(PROTO_DIR)/usr/share/themes/
	cp -r $(COMPONENT_DIR)/files/css/* $(PROTO_DIR)/usr/share/themes/nimbus/
	$(TOUCH) $(INSTALL_GTK3_THEME)

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64) $(INSTALL_GTK3_THEME)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
