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
# Copyright 2017 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		sound-juicer
COMPONENT_VERSION=	2.32.0
COMPONENT_REVISION=	2
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/SoundJuicer
COMPONENT_SUMMARY=	CD ripping tool
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:f6040e19e50094daff9699dea3e9884ce3226a61f28acbe9ad3a0458975a305a
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/2.32/$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.bz2
COMPONENT_CLASSIFICATION= Applications/Sound and Video
COMPONENT_FMRI= desktop/cd-ripping/sound-juicer
COMPONENT_LICENSE=      GPLv2
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin:/usr/perl5/bin

COMPONENT_PRE_CONFIGURE_ACTION =        (cp -r $(SOURCE_DIR)/* $(@D) && \
					cp -r $(COMPONENT_DIR)/files/po-sun $(@D) && \
					cd $(@D)/po-sun && $(MAKE) all &&\
					cd $(@D) && intltoolize --force --copy --automake &&\
					aclocal -I ./m4 &&\
					autoheader &&\
					automake -a -f -c --gnu &&\
					autoconf )
					
CONFIGURE_SCRIPT=       $(@D)/configure

gcc_OPT		= -O2

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--localstatedir=/var
CONFIGURE_OPTIONS+=	--disable-scrollkeeper
CONFIGURE_OPTIONS+=	--with-gtk=3.0

COMPONENT_INSTALL_ENV+=	GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += desktop/cd-burning/brasero
REQUIRED_PACKAGES += gnome/config/gconf
REQUIRED_PACKAGES += library/audio/gstreamer
REQUIRED_PACKAGES += library/audio/gstreamer/plugin/base
REQUIRED_PACKAGES += library/audio/libcdio
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/xdg/libcanberra
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/musicbrainz/libmusicbrainz-3
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/libdbus-glib
