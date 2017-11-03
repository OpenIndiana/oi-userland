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
# Copyright 2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		dmz-cursor-theme
COMPONENT_VERSION=	0.4.4
COMPONENT_PROJECT_URL=	http://jimmac.musichall.cz/
COMPONENT_SUMMARY=	DMZ cursor themes
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)_$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:46af4cf1356df799f9ee94451f05d0bdbb8d82e54bdeae3f32fa107602359981
COMPONENT_ARCHIVE_URL=	http://http.debian.net/debian/pool/main/d/dmz-cursor-theme/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		gnome/theme/cursor/dmz-cursor
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Theming
COMPONENT_LICENSE=	CC-BY-SA-3.0

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION =        ( cp $(COMPONENT_DIR)/files/Makefile $(@D))

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES+= image/xcursorgen
