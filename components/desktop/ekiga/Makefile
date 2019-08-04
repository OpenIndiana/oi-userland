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
# Copyright (c) 2014 Alexander Pyhalov
#

PREFERRED_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ekiga
COMPONENT_VERSION=	4.0.1
COMPONENT_REVISION=	3
COMPONENT_FMRI= communication/conferencing/ekiga
COMPONENT_CLASSIFICATION= Applications/Sound and Video
COMPONENT_PROJECT_URL=	http://www.ekiga.org
COMPONENT_SUMMARY=	A GNOME based H.323/SIP video conferencing application
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:5f4f491c9496cf65ba057a9345d6bb0278f4eca07bcda5baeecf50bfcd9a4a3b
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/ekiga/4.0/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE= GPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu):/usr/perl5/bin

COMPONENT_PREP_ACTION = ( cd $(@D) && \
          libtoolize --force && \
          aclocal -I. && \
          automake -a -f -c &&\
          autoconf )

COMPONENT_PRE_CONFIGURE_ACTION =        (cp -r $(SOURCE_DIR)/* $(@D) && \
					cp -r $(COMPONENT_DIR)/files/po-sun $(@D) && \
					cd $(@D)/po-sun && $(MAKE) all )
					
CFLAGS+=	-DSOLARIS -D__EXTENSIONS__
CXXFLAGS+=	-DSOLARIS -D__EXTENSIONS__

CONFIGURE_SCRIPT=       $(@D)/configure

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--disable-ldap
CONFIGURE_OPTIONS+=	--disable-notify
CONFIGURE_OPTIONS+=	--enable-xv
CONFIGURE_OPTIONS+=	--disable-gconf

COMPONENT_INSTALL_ENV+=	GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

# common targets
build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES += gnome/theme/gnome-icon-theme

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/evolution-data-server
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/ptlib
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libopal
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/boost
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxv
