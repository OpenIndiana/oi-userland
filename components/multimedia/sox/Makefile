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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		sox
COMPONENT_VERSION=	14.4.2
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	Sound eXchange, the Swiss Army knife of audio manipulation
COMPONENT_PROJECT_URL=	https://sox.sourceforge.net/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	sha256:81a6956d4330e75b5827316e44ae381e6f1e8928003c6aa45896da9041ea149c
COMPONENT_ARCHIVE_URL=	https://downloads.sourceforge.net/project/$(COMPONENT_NAME)/$(COMPONENT_NAME)/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		audio/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/Sound and Video
COMPONENT_LICENSE=	GPL-2.0-only AND LGPL-2.1-only

include $(WS_MAKE_RULES)/common.mk

# We patched configure.ac so we need to run autoreconf
COMPONENT_PREP_ACTION = ( cd $(@D) && PATH="$(PATH)" autoreconf -f )

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --with-lame
CONFIGURE_OPTIONS += --with-twolame
# Avoid dependencies on encumbered packages
CONFIGURE_OPTIONS += --without-mad

COMPONENT_TEST_TARGETS = installcheck

# Normalize test results
COMPONENT_TEST_TRANSFORMS += "-e '/^make\[/d'"			# delete make logs
COMPONENT_TEST_TRANSFORMS += "-e '/^Making installcheck in/d'"	# delete make logs
COMPONENT_TEST_TRANSFORMS += "-e 's/ [.0-9]\{1,\}s$$//'"	# timing

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
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
