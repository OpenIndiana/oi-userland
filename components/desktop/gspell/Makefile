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
# Copyright 2022 Niklas Poslovski
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         gspell
COMPONENT_MAJOR_VERSION=      1.12
COMPONENT_VERSION=		$(COMPONENT_MAJOR_VERSION).1
COMPONENT_REVISION=		1
COMPONENT_SUMMARY=      A flexible API to implement the spell checking in a GTK+ application
COMPONENT_PROJECT_URL=  https://gitlab.gnome.org/GNOME/gspell
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:8ec44f32052e896fcdd4926eb814a326e39a5047e251eec7b9056fbd9444b0f1
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPONENT_MAJOR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/desktop/gspell
COMPONENT_CLASSIFICATION=	Applications/Accessories
COMPONENT_LICENSE=      LGPLv2.1
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += MAKE=gmake

# Manually added test dependencies
# According to the test sources aspell is deprecated and superceded by hunspell.
# One of the tests is failing with aspell which won't be fixed.
# We might want to replace aspell (used by enchant) with hunspell later.
#TEST_REQUIRED_PACKAGES += library/myspell/dictionary/en
TEST_REQUIRED_PACKAGES += text/aspell/en

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += library/spell-checking/enchant
REQUIRED_PACKAGES += system/library
