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
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libsndfile
COMPONENT_VERSION=	1.0.28
COMPONENT_REVISION=	2
COMPONENT_SUMMARY=	libsndfile - a library for reading/writing sound files
COMPONENT_DESCRIPTION=	Libsndfile is a C library for reading and writing files\
 containing sampled sound (such as MS Windows WAV and the Apple/SGI AIFF\
 format) through one standard library interface.
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://www.mega-nerd.com/libsndfile/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:1ff33929f042fa333aed1e8923aa628c3ee9e1eb85512686c55092d1e5a9dfa9
COMPONENT_ARCHIVE_URL=	http://www.mega-nerd.com/libsndfile/files/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	library/libsndfile
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE= LGPLv2.1

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Need to use GNU sed otherwise we get a:
# Error : sfversion <version> and PACKAGE_VERSION <version> don't match."
# failure from the test_wrapper.sh script.
COMPONENT_TEST_ENV +=   PATH="$(GNUBIN):$(PATH)"
COMPONENT_SYSTEM_TEST_ENV +=   PATH="$(GNUBIN):$(PATH)"

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += \
	'-e "s|libsndfile-1\.0\...|libsndfile-1\.0\.xx|g" ' \
	'-e "/FILE_OFFSET_BITS/d"' \
	'-n ' \
	'-e "/-------/p" ' \
	'-e "/=======/p" ' \
	'-e "/ passed /p" ' \
	'-e "/ failed /p" ' \
	'-e "/^Testing/p" ' \
	'-e "/dev\/full/p" ' \
	'-e "/^\./p" ' \
	'-e "/ok$$/p" '

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:	$(TEST_32_and_64)

REQUIRED_PACKAGES += codec/flac
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/libogg
REQUIRED_PACKAGES += library/libvorbis
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
