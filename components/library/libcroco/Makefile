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
# Copyright 2017 Alexander Pyhalov
# Copyright 2021 Andreas Wacknitz
#

BUILD_BITS= 32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libcroco
COMPONENT_VERSION= 0.6.13
COMPONENT_SUMMARY= Cascading Style Sheet (CSS) parsing and manipulation toolkit
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:767ec234ae7aa684695b3a735548224888132e063f92db585759b422570621d4
COMPONENT_ARCHIVE_URL=	https://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/0.6/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://www.gnome.org
COMPONENT_LICENSE_FILE= COPYING
COMPONENT_LICENSE=		LGPLv2
COMPONENT_FMRI=			library/libcroco
COMPONENT_CLASSIFICATION = Desktop (GNOME)/Libraries

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --enable-static=no
CONFIGURE_OPTIONS += --disable-Bsymbolic
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-dependency-tracking

# Needed to make tests work
# Tests fail because of poor quality
COMPONENT_TEST_ENV += PATH="$(PATH.gnu)"
COMPONENT_TEST_TARGETS = test

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
