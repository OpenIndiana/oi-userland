#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2014 Josef 'Jeff' Sipek <jeffpc@josefsipek.net>
# Copyright 2020 Andreas Waknitz
#

BUILD_BITS=64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		xcowsay
COMPONENT_VERSION=	1.6
COMPONENT_PROJECT_URL=	https://www.doof.me.uk/xcowsay/
COMPONENT_FMRI=		desktop/xcowsay
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:46ace864ff28d2d21f4b7058f0295e18d0041a120c1078a951fa43c4e0f5c8c5
COMPONENT_ARCHIVE_URL=	https://www.nickg.me.uk/files/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv3
COMPONENT_SUMMARY=	xcowsay - displays a cute cow and message

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = (cd $(@D) && autoreconf -vfi )

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
