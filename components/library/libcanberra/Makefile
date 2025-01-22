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
# Copyright 2015 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libcanberra
COMPONENT_VERSION=      0.30
COMPONENT_REVISION=	2
COMPONENT_SUMMARY=      Event Sound API Using XDG Sound Theming Specification
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:c2b671e67e0c288a69fc33dc1b6f1b534d07882c2aceed37004bf48c601afa72
COMPONENT_ARCHIVE_URL=  http://0pointer.de/lennart/projects/libcanberra/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  http://0pointer.de/lennart/projects/libcanberra/
COMPONENT_FMRI=         library/desktop/xdg/libcanberra
COMPONENT_CLASSIFICATION=System/Multimedia Libraries
COMPONENT_LICENSE=	LGPL-2.1-only
COMPONENT_LICENSE_FILE= LGPL

include $(WS_MAKE_RULES)/common.mk

# We are patching configure.ac
COMPONENT_PREP_ACTION += cd $(@D) && $(ENV) PATH="$(PATH)" autoreconf -fi ;

CONFIGURE_OPTIONS += --enable-gtk
CONFIGURE_OPTIONS += --disable-static

# Auto-generated dependencies
REQUIRED_PACKAGES += library/audio/gstreamer1
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/libvorbis
REQUIRED_PACKAGES += library/tdb
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
