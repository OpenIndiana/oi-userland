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
# Copyright (c) 2013 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnome-python-desktop
COMPONENT_VERSION=	2.32.0
COMPONENT_REVISION=	3
COMPONENT_PROJECT_URL=	http://www.gnome.org
COMPONENT_SUMMARY=	Python bindings for various GNOME desktop libraries
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:09dbd580bf3b0ef60f91b090eafe6d08ddcc50a609e2b425a7f8eca46d4e0ee9
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/2.32/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

gcc_OPT		= -O2

CONFIGURE_OPTIONS+=	--disable-gnomeprint
CONFIGURE_OPTIONS+=	--disable-gnomeprintui
CONFIGURE_OPTIONS+=	--disable-gtksourceview
CONFIGURE_ENV+=		PYTHON=$(PYTHON)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

include $(WS_MAKE_RULES)/depend.mk
