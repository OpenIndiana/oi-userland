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

BUILD_STYLE=		meson

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tinysparql
HUMAN_VERSION=		3.8.2
COMPONENT_SUMMARY=	TinySPARQL (Tracker 3) - SPARQL triple store library
COMPONENT_ARCHIVE_HASH=	\
	sha256:bb8643386c8edc591a03205d4a0eda661dcdd2094473bffb9bbdb94e93589cb2
COMPONENT_FMRI=		library/desktop/search/tinysparql
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_LICENSE=	LGPL-2.1-or-later AND GPL-2.0-or-later
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# memmem()
CFLAGS +=		-D__EXTENSIONS__
# bzero() is in <strings.h> on illumos
CFLAGS +=		-include strings.h
# per-thread errno
CFLAGS +=		-D_REENTRANT

CONFIGURE_OPTIONS +=	-Ddocs=false
CONFIGURE_OPTIONS +=	-Dman=false
CONFIGURE_OPTIONS +=	-Dtests=false
CONFIGURE_OPTIONS +=	-Dbash_completion=false
CONFIGURE_OPTIONS +=	-Davahi=disabled
CONFIGURE_OPTIONS +=	-Dsystemd_user_services=false
CONFIGURE_OPTIONS +=	-Dstemmer=disabled
CONFIGURE_OPTIONS +=	-Dunicode_support=icu
CONFIGURE_OPTIONS +=	-Dvapi=disabled

# Auto-generated dependencies
REQUIRED_PACKAGES += $(ICU_LIBRARY_PKG)
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += developer/icu
REQUIRED_PACKAGES += library/desktop/json-glib
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libsoup3
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
