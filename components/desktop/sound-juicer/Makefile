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
# Copyright 2025 Marcel Telka
#

BUILD_STYLE = meson

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			sound-juicer
COMPONENT_VERSION=		3.40.0
COMPONENT_SUMMARY=		CD ripping tool using GTK+ and GStreamer
COMPONENT_ARCHIVE_HASH= \
	sha256:2ee882744391beb4c6d64a0f6825fb765510b706ec2b704bfb42e42afaae1de6
COMPONENT_CLASSIFICATION=	Applications/Sound and Video
COMPONENT_FMRI=			desktop/cd-ripping/sound-juicer
COMPONENT_LICENSE=		GPL-2.0-only
COMPONENT_LICENSE_FILE=		COPYING

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# GNU msgfmt is needed
PATH=$(PATH.gnu)

# Install additional file
COMPONENT_POST_INSTALL_ACTION += \
	$(INSTALL) -D $(COMPONENT_DIR)/files/desktop-cd-ripping-sound-juicer \
		$(PROTOETCSECDIR)/exec_attr.d/desktop-cd-ripping-sound-juicer ;

# Manually added build dependencies
REQUIRED_PACKAGES += library/audio/gstreamer1/plugin/good

# Auto-generated dependencies
REQUIRED_PACKAGES += desktop/cd-burning/brasero
REQUIRED_PACKAGES += library/audio/gstreamer1
REQUIRED_PACKAGES += library/audio/gstreamer1/plugin/base
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/xdg/libcanberra
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/musicbrainz/libdiscid
REQUIRED_PACKAGES += library/musicbrainz/libmusicbrainz-5
REQUIRED_PACKAGES += system/library
