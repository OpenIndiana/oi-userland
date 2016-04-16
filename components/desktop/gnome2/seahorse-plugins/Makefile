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

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		seahorse-plugins
COMPONENT_VERSION=	2.30.1
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/action/show/Apps/Seahorse
COMPONENT_SUMMARY=	Plugins for gedit and nautilus
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:1fdfed1aef2c22a29a9abc00eae67752854e466a66cee2a8c1c278277e832d66
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/2.30/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION =        ( cd $(@D) && \
					libtoolize --automake --copy --force && \
					gnome-doc-prepare --force && \
					aclocal -Im4 && \
					autoheader && \
					automake -a -f -c &&\
					autoconf )

CPPFLAGS = -DMOZ_DEFAULT_TOOLKIT=\"cairo-gtk2\" -I/usr/include/firefox -I/usr/include/firefox/nspr

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--libexecdir=/usr/lib
CONFIGURE_OPTIONS+=	--disable-update-mime-database
CONFIGURE_ENV+= 	CPPFLAGS="$(CPPFLAGS)"

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)
