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
# Copyright 2015 Alexander Pyhalov
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		nimbus
COMPONENT_VERSION=	0.1.9
COMPONENT_PROJECT_URL=	https://java.net/projects/solaris-desktop/pages/Home
COMPONENT_SUMMARY=	Engine for Sun Nimbus GTK2 Theme
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:6f26e3539f99ee172b6b768fb0f07bfc15ebb3ab91f687435ddbba7d36fb903b
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/schwer-q.u/files/nimbus/$(COMPONENT_ARCHIVE)/download
COMPONENT_FMRI=		gnome/theme/nimbus
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Theming
COMPONENT_LICENSE = LGPLv2
COMPONENT_LICENSE_FILE = COPYING

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

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

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)
