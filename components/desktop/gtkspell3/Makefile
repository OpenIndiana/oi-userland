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

BUILD_BITS=64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         gtkspell3
COMPONENT_VERSION=      3.0.10
#COMPONENT_REVISION=     1
COMPONENT_PROJECT_URL=  http://gtkspell.sourceforge.net
COMPONENT_SUMMARY=      Provides word-processor-style highlighting and replacement of misspelled words in a GtkTextView widget
COMPONENT_FMRI=         library/desktop/gtkspell3
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
    sha256:b040f63836b347eb344f5542443dc254621805072f7141d49c067ecb5a375732
COMPONENT_ARCHIVE_URL=	https://sourceforge.net/projects/gtkspell/files/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_CLASSIFICATION=	Applications/Accessories
COMPONENT_LICENSE=      GPLv2
COMPONENT_LICENSE_FILE= gtkspell3.license

CONFIGURE_OPTIONS += MAKE=gmake
CONFIGURE_OPTIONS += XGETTEXT=/bin/gxgettext
CONFIGURE_OPTIONS += MSGFMT=/bin/gmsgfmt

TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/spell-checking/enchant
REQUIRED_PACKAGES += system/library
