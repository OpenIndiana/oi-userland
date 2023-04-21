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
BUILD_BITS= 64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libsndfile
COMPONENT_VERSION=	1.0.31
COMPONENT_REVISION= 1
COMPONENT_SUMMARY=	libsndfile - a library for reading/writing sound files
COMPONENT_DESCRIPTION=	Libsndfile is a C library for reading and writing files\
 containing sampled sound (such as MS Windows WAV and the Apple/SGI AIFF\
 format) through one standard library interface.
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://libsndfile.github.io/libsndfile/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:8cdee0acb06bb0a3c1a6ca524575643df8b1f3a55a0893b4dd9f829d08263785
COMPONENT_ARCHIVE_URL=	https://github.com/libsndfile/libsndfile/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=	library/libsndfile
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE= LGPLv2.1

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = ( cd $(@D) && ./autogen.sh )

# Need to use GNU sed otherwise we get a:
# Error : sfversion <version> and PACKAGE_VERSION <version> don't match."
# failure from the test_wrapper.sh script.
#
# Attention: If the user running the tests has increased privileges the permission tests may fail.
COMPONENT_TEST_ENV +=   PATH="$(GNUBIN):$(PATH)"
COMPONENT_SYSTEM_TEST_ENV +=   PATH="$(GNUBIN):$(PATH)"
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_TRANSFORMS += \
	'-e "s|libsndfile-1\.0\...|libsndfile-1\.0\.xx|g" ' \
	'-e "/FILE_OFFSET_BITS/d"' \
	'-n ' \
	'-e "/Running/p" ' \
	'-e "/-------/p" ' \
	'-e "/ passed /p" ' \
	'-e "/ failed /p" ' \
	'-e "/^FAIL/p" ' \
	'-e "/^Testing/p" ' \
	'-e "/dev\/full/p" ' \
	'-e "/aiff_ima/p" ' \
	'-e "/ok$$/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += codec/flac
REQUIRED_PACKAGES += library/libogg
REQUIRED_PACKAGES += library/libvorbis
REQUIRED_PACKAGES += library/opus
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
