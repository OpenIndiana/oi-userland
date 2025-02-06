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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2021 Andreas Wacknitz
#

USE_COMMON_TEST_MASTER= no
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libsndfile
COMPONENT_VERSION=	1.2.2
COMPONENT_REVISION=	2
COMPONENT_SUMMARY=	libsndfile - a library for reading/writing sound files
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://libsndfile.github.io/libsndfile/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:3799ca9924d3125038880367bf1468e53a1b7e3686a934f098b7e1d286cdb80e
COMPONENT_ARCHIVE_URL=	https://github.com/libsndfile/libsndfile/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	library/libsndfile
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=	LGPL-2.1-only
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

# Install Octave files
COMPONENT_POST_INSTALL_ACTION += $(INSTALL) -d $(PROTO_DIR)/usr/share/octave/site/m ;
COMPONENT_POST_INSTALL_ACTION += \
	for f in load play save ; do \
		$(INSTALL) $(SOURCE_DIR)/Octave/sndfile_$$f.m $(PROTO_DIR)/usr/share/octave/site/m ; \
	done ;

# Normalize test results
COMPONENT_TEST_TRANSFORMS += "-e '/^make\[/d'"			# delete make logs
COMPONENT_TEST_TRANSFORMS += "-n"
COMPONENT_TEST_TRANSFORMS += "-e '/Pedantic header test/,\$$p'"	# this is the actual test report

# Auto-generated dependencies
REQUIRED_PACKAGES += audio/lame
REQUIRED_PACKAGES += audio/mpg123
REQUIRED_PACKAGES += codec/flac
REQUIRED_PACKAGES += library/libogg
REQUIRED_PACKAGES += library/libvorbis
REQUIRED_PACKAGES += library/opus
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
