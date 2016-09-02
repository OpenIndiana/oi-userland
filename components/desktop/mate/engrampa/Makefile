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

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		engrampa
COMPONENT_VERSION=	1.14.1
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://www.mate-desktop.org
COMPONENT_SUMMARY=	MATE archive manager
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:43d882e772c53d13856f02e44454927e3bab4c5d77094057572be6972e0310d8
COMPONENT_ARCHIVE_URL=	http://pub.mate-desktop.org/releases/1.14/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	desktop/archive-manager/engrampa
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/File Managers
COMPONENT_LICENSE= GPLv3
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION=  cd $(@D)  && NOCONFIGURE=1 ./autogen.sh

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--libexecdir=/usr/lib/mate
CONFIGURE_OPTIONS+=	--disable-static

CONFIGURE_ENV+= PYTHON="$(PYTHON)"

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)
