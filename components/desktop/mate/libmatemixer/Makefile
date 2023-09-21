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
# Copyright (c) 2021 Tim Mooney. All rights reserved
# Copyright 2022 Andreas Wacknitz
#

MATE_CATEGORY= LIB
BUILD_STYLE= configure
include ../../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/mate.mk

COMPONENT_NAME=		libmatemixer
COMPONENT_MJR_VERSION=  1.26
COMPONENT_MNR_VERSION=	1
COMPONENT_SUMMARY=	Mixer library for MATE desktop
COMPONENT_ARCHIVE_HASH= sha256:4960f59a6b9faf82a01d4a4b8cc260b4868dd991efd4a9b17b5d0a15a1d3a1ae
COMPONENT_LICENSE=	GPLv2, LGPLv2, FDLv1.1

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS+= --enable-pulseaudio
CONFIGURE_OPTIONS+= --enable-oss

# Build requirements
REQUIRED_PACKAGES += system/header/header-audio
# if we stop rebuilding configure these two build dependencies can
# be dropped
REQUIRED_PACKAGES += developer/build/autoconf-archive

# Auto-generated dependencies
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
