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
# Copyright (c) 2017 Dariusz Sendkowski
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         babeltrace
COMPONENT_VERSION=      1.5.11
COMPONENT_SUMMARY=      Provides CTF trace read and write libraries, as well as a trace converter.
COMPONENT_PROJECT_URL=  https://www.efficios.com/babeltrace	
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:67b43aaaef5c951fa7af1a557cf7201a11fe89876b7c22ba0a03cbc316db5a9c
COMPONENT_ARCHIVE_URL=  https://www.efficios.com/files/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         developer/babeltrace
COMPONENT_CLASSIFICATION=Development/Editors
COMPONENT_LICENSE=      MIT
COMPONENT_LICENSE_FILE= LICENSE

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --disable-static

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/popt
REQUIRED_PACKAGES += system/library
