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
COMPONENT_VERSION=      1.5.2
COMPONENT_PROJECT_URL=  http://www.efficios.com/babeltrace	
COMPONENT_SUMMARY=      Provides CTF trace read and write libraries, as well as a trace converter.
COMPONENT_FMRI=         developer/babeltrace
COMPONENT_CLASSIFICATION=Development/Editors
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:696ee46e5750ab57a258663e73915d2901b7cd4fc53b06eb3f7a0d7b1012fa56
COMPONENT_ARCHIVE_URL=  http://www.efficios.com/files/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      MIT
COMPONENT_LICENSE_FILE= LICENSE

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS += --disable-static



build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TEST)

REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/popt
REQUIRED_PACKAGES += system/library
