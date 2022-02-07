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

COMPONENT_NAME=         wv
COMPONENT_VERSION=      1.2.9
#COMPONENT_REVISION=     1
COMPONENT_PROJECT_URL=  http://wvware.sourceforge.net
COMPONENT_SUMMARY=      MSWord library can load and parse Word 2000, 97, 95 and 6 file formats
COMPONENT_FMRI=         library/wv
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:4c730d3b325c0785450dd3a043eeb53e1518598c4f41f155558385dd2635c19d
COMPONENT_ARCHIVE_URL=  http://abiword.com/downloads/$(COMPONENT_NAME)/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=       Applications/System Utilities
COMPONENT_LICENSE=      GPLv2
COMPONENT_LICENSE_FILE= wv.license

TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/libgsf
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
