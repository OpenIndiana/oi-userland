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
# Copyright (c) 2026 Geoff Weiss
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         garagejam
COMPONENT_VERSION=      8.0.1
COMPONENT_GIT_HASH=	28e51fb89c4f7025d45288f2520214fac8a07234
COMPONENT_SUMMARY=      Music — a multiple-track audio recording studio from the GarageJam project. Record, arrange and mix multitrack sessions with GTK4 and GStreamer, and save projects in the open GJXML format.
COMPONENT_PROJECT_URL=  https://www.garagejam.org
COMPONENT_SRC=          music-$(COMPONENT_GIT_HASH)
COMPONENT_ARCHIVE=      $(COMPONENT_GIT_HASH).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:1ee4f2dfbe38152cb991460c687fa71a648648dbb436e7e1fe22e73b29822fb4
COMPONENT_ARCHIVE_URL=  https://github.com/oleaamot-dev/music/archive/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         desktop/audio/garagejam
COMPONENT_CLASSIFICATION=Applications/Sound and Video
COMPONENT_LICENSE=      GPLv3
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/audio/gstreamer
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gtk4
REQUIRED_PACKAGES += library/desktop/libadwaita
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
