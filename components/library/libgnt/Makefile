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

BUILD_BITS= 64
BUILD_STYLE= meson
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libgnt
COMPONENT_VERSION=	2.14.4
COMPONENT_SUMMARY=	The GLib Ncurses Toolkit
COMPONENT_PROJECT_URL=	https://keep.imfreedom.org/libgnt/libgnt/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)-dev
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:195933a9a731d3575791b881ba5cc0ad2a715e1e9c4c23ccaaa2a17e164c96ec
COMPONENT_ARCHIVE_URL=	https://sourceforge.net/projects/pidgin/files/$(COMPONENT_NAME)/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_FMRI=		library/libgnt
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

LDFLAGS += -L/usr/gnu/lib/$(MACH64) -R/usr/gnu/lib/$(MACH64)

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library
