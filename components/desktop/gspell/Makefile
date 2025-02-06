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
# Copyright 2024 Marcel Telka
#

BUILD_STYLE = meson
USE_DEFAULT_TEST_TRANSFORMS = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			gspell
HUMAN_VERSION=			1.14.0
COMPONENT_SUMMARY=		Flexible API to add spell-checking to a GTK application
COMPONENT_ARCHIVE_HASH=		sha256:64ea1d8e9edc1c25b45a920e80daf67559d1866ffcd7f8432fecfea6d0fe8897
COMPONENT_FMRI=			library/desktop/gspell-3
COMPONENT_CLASSIFICATION=	Applications/Accessories
COMPONENT_LICENSE=		LGPL-2.1-or-later
COMPONENT_LICENSE_FILE=		LICENSES/LGPL-2.1-or-later.txt

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# GNU msgfmt is needed
PATH = $(PATH.gnu)

# We do not need installed tests (yet)
CONFIGURE_OPTIONS += -Dinstall_tests=false

# Testing needs an X server
TEST_REQUIRED_PACKAGES += x11/server/xvfb
COMPONENT_PRE_TEST_ACTION += /usr/bin/Xvfb :0 >/dev/null 2>&1 &
COMPONENT_TEST_ENV += DISPLAY=:0
COMPONENT_POST_TEST_ACTION += /usr/bin/pkill -x Xvfb ;

# Replace ABI version number by ABIVER
#GENERATE_EXTRA_CMD += | $(GSED) -e 's/\(gtksourceview-\)$(ABIVER)/\1$$(ABIVER)/' \
	-e 's/\(GtkSource-\)$(ABIVER)/\1$$(ABIVER)/'

# ABIVER is needed for manifest processing
#PKG_MACROS += ABIVER=$(ABIVER)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(ICU_LIBRARY_PKG)
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/spell-checking/enchant
REQUIRED_PACKAGES += system/library
