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

COMPONENT_NAME=		gnome-session
HUMAN_VERSION=		45.0
# revision 1: the session entries moved to gnome/gnome-session/sessions,
# which requires gnome-shell
COMPONENT_SUMMARY=	GNOME session manager
COMPONENT_ARCHIVE_HASH=	\
	sha256:706d2ffcacac38553a3c0185793f5a2b4aac940bb5e789d953c9808163bef2f1
COMPONENT_FMRI=		gnome/gnome-session
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Sessions
COMPONENT_LICENSE=	GPL-2.0-or-later
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# GNU msgfmt is expected
PATH=			$(PATH.gnu)

CONFIGURE_OPTIONS +=	-Dsystemd_session=disable
CONFIGURE_OPTIONS +=	-Dsystemd=false
CONFIGURE_OPTIONS +=	-Dsystemd_journal=false
CONFIGURE_OPTIONS +=	-Dconsolekit=true
CONFIGURE_OPTIONS +=	-Dsession_selector=true
CONFIGURE_OPTIONS +=	-Ddocbook=false
CONFIGURE_OPTIONS +=	-Dman=false

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/gnome-desktop
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/json-glib
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += service/opengl/ogl-select
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libepoxy
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcomposite
