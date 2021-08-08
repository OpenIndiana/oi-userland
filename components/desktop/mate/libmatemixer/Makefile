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
# Copyright 2016 Till Wegmueller
# Copyright 2016 Ken Mays
# Copyright 2020 Michal Nowak
# Copyright 2021 Andreas Wacknitz
#

MATE_CATEGORY=	LIB
include ../../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/mate.mk

COMPONENT_NAME=		libmatemixer
COMPONENT_MJR_VERSION=  1.26
COMPONENT_MNR_VERSION=	0
COMPONENT_SUMMARY=	Mixer library for MATE desktop
COMPONENT_ARCHIVE_HASH= sha256:9a9bcc605b27e9c5c91a28eb7cb79831e6d6fbf6339f5e5c18d524f3ee259ff1

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS+= --enable-pulseaudio
CONFIGURE_OPTIONS+= --enable-oss

# Build requirements
REQUIRED_PACKAGES += system/header/header-audio

# Auto-generated dependencies
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
