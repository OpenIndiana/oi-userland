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

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnome-games
COMPONENT_VERSION=	2.32.1
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/action/show/Apps/Games
COMPONENT_SUMMARY=	GNOME games
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:1a3b2e82102eed3780f05db4378111c475456678deed82fd4ca379da1c5593d9
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/$(COMPONENT_NAME)/2.32/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION =        ( cd $(@D) && \
					libtoolize --automake --copy --force && \
					aclocal -I./m4 && \
					autoheader && \
					automake -a -f -c &&\
					autoconf )

CONFIGURE_OPTIONS+=	--with-sound=gstreamer
CONFIGURE_OPTIONS+=	--disable-setgid
CONFIGURE_OPTIONS+=	--disable-scrollkeeper
CONFIGURE_OPTIONS+=	--enable-omitgames=aisleriot,gnometris
CONFIGURE_OPTIONS+=	--enable-introspection=no

CONFIGURE_ENV+= PERL=$(PERL)
CONFIGURE_ENV+= PYTHON=$(PYTHON)

COMPONENT_INSTALL_ENV+= GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)
