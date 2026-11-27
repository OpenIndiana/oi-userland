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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mikmod
COMPONENT_VERSION=	3.2.10
COMPONENT_SUMMARY=	MikMod module player (MOD, S3M, XM, IT and more)
COMPONENT_CLASSIFICATION=	Applications/Sound and Video
COMPONENT_PROJECT_URL=	https://mikmod.sourceforge.net/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:465e99d89d762608b7d0c0a103a58eec68c8c28ae6bbd196354c13433e40d20a
COMPONENT_ARCHIVE_URL=	https://sourceforge.net/projects/mikmod/files/mikmod/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download/
COMPONENT_FMRI=		media/mikmod
COMPONENT_LICENSE=	GPL-2.0-or-later
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

# ncurses.h is in /usr/include/ncurses
CONFIGURE_ENV +=	CPPFLAGS="-I$(USRINCDIR)/ncurses"

# Upstream ships no desktop file
COMPONENT_POST_INSTALL_ACTION += \
	$(INSTALL) -D -m 0444 $(COMPONENT_DIR)/files/mikmod.desktop \
	    $(PROTOUSRSHAREDIR)/applications/mikmod.desktop

# Auto-generated dependencies
REQUIRED_PACKAGES += library/audio/libmikmod
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library
