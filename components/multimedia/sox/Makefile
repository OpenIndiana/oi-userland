#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS= 64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		sox
COMPONENT_VERSION=	14.4.1
COMPONENT_REVISION=	5
COMPONENT_SUMMARY=	Sound eXchange, the Swiss Army knife of audio manipulation
COMPONENT_DESCRIPTION=	SoX is a cross-platform command line utility that can convert various formats of computer audio files into other formats.
COMPONENT_PROJECT_URL=	https://sox.sourceforge.net/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:9a8c2c6fe51e608da346a157e111508a957af9e3ecf3de26781d36e9a67fa89b
COMPONENT_ARCHIVE_URL=	https://downloads.sourceforge.net/project/$(COMPONENT_NAME)/$(COMPONENT_NAME)/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		audio/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/Sound and Video
COMPONENT_LICENSE=	GPLv2, LGPLv2.1

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CFLAGS.32 += -D_FILE_OFFSET_BITS=64
CFLAGS += $(CFLAGS.$(BITS))

COMPONENT_PREP_ACTION = ( cd $(@D) && autoreconf -f )

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-gomp
CONFIGURE_OPTIONS += --with-lame
CONFIGURE_OPTIONS += --with-twolame
# Avoid dependencies on encumbered packages
CONFIGURE_OPTIONS += --without-mad
CONFIGURE_OPTIONS += --disable-dl-amrwb

# Auto-generated dependencies
REQUIRED_PACKAGES += audio/lame
REQUIRED_PACKAGES += audio/twolame
REQUIRED_PACKAGES += audio/wavpack
REQUIRED_PACKAGES += codec/flac
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/audio/libao
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/libogg
REQUIRED_PACKAGES += library/libsndfile
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/libvorbis
REQUIRED_PACKAGES += library/magic
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
