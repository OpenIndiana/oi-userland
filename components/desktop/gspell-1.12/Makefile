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
COMPONENT_VERSION=		$(COMPONENT_MAJOR_VERSION).2
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=      A flexible API to implement the spell checking in a GTK+ application
COMPONENT_PROJECT_URL=  https://gitlab.gnome.org/GNOME/gspell
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:b4e993bd827e4ceb6a770b1b5e8950fce3be9c8b2b0cbeb22fdf992808dd2139
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPONENT_MAJOR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/desktop/gspell
COMPONENT_CLASSIFICATION=	Applications/Accessories
COMPONENT_LICENSE=      LGPLv2.1
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += MAKE=gmake

# Disable everything provided by library/desktop/gspell-3:
# - message catalogs
# - introspection files
# - vala support
CONFIGURE_OPTIONS += --disable-nls
CONFIGURE_OPTIONS += --disable-introspection
CONFIGURE_OPTIONS += --disable-vala

# Drop everything provided by library/desktop/gspell-3:
# - binaries
# - include files
# - the so file
# - pkgconfig file
COMPONENT_POST_INSTALL_ACTION += \
	$(RM) -r $(PROTOUSRBINDIR) ; \
	$(RM) -r $(PROTOUSRINCDIR) ; \
	$(RM) -r $(PROTOUSRLIBDIR64)/libgspell-1.so ; \
	$(RM) -r $(PROTOUSRLIBDIR64)/pkgconfig ;

# Testing needs an X server
TEST_REQUIRED_PACKAGES += x11/server/xvfb
COMPONENT_PRE_TEST_ACTION += /usr/bin/Xvfb :0 >/dev/null 2>&1 &
COMPONENT_TEST_ENV += DISPLAY=:0
COMPONENT_POST_TEST_ACTION += /usr/bin/pkill -x Xvfb ;

# Manually added test dependencies
# According to the test sources aspell is deprecated and superceded by hunspell.
# One of the tests is failing with aspell which won't be fixed.
# We might want to replace aspell (used by enchant) with hunspell later.
#TEST_REQUIRED_PACKAGES += library/myspell/dictionary/en
TEST_REQUIRED_PACKAGES += text/aspell/en

# Auto-generated dependencies
REQUIRED_PACKAGES += $(ICU_LIBRARY_PKG)
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/spell-checking/enchant
REQUIRED_PACKAGES += system/library
