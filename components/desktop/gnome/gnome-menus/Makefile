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
# Copyright 2026 isoriano1968
#

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnome-menus
HUMAN_VERSION=		3.36.0
COMPONENT_SUMMARY=	The GNOME Menu Library
COMPONENT_ARCHIVE_HASH=	\
	sha256:d9348f38bde956fc32753b28c1cde19c175bfdbf1f4d5b06003b3aa09153bb1f
COMPONENT_FMRI=		gnome/gnome-menus
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_LICENSE=	GPL-2.0-or-later
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# automake's dependency tracking needs GNU make as make
PATH=			$(PATH.gnu)

# per-thread errno
CFLAGS +=		-D_REENTRANT

# patches/01-gio-unix-gir.patch changes configure.ac and libmenu/Makefile.am
COMPONENT_PREP_ACTION +=	(cd $(@D) && $(AUTORECONF) -fi) ;

CONFIGURE_OPTIONS +=	--disable-static

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
