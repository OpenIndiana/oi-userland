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

COMPONENT_NAME=		libwnck3
COMPONENT_VERSION=	3.18.0
COMPONENT_PROJECT_URL=	http://www.gnome.org
COMPONENT_SUMMARY=	Window Navigator Construction Kit Library
COMPONENT_SRC=		libwnck-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:4dabf8f28fd140cbe1f27c0c466c1a787cbfd03621e45bd24fed62fa568106ac
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/libwnck/3.18/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	LGPLv2
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_FMRI=         library/desktop/libwnck


include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--disable-static
CONFIGURE_OPTIONS+=	--program-suffix=3

# 
COMPONENT_BUILD_ENV+=	CC="$(CC)"
COMPONENT_BUILD_ENV+=	CFLAGS="$(CFLAGS)"

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)
