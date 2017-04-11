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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
COMPILER= gcc
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		libsndfile
COMPONENT_VERSION=	1.0.28
COMPONENT_PROJECT_URL=	http://www.mega-nerd.com/libsndfile/
COMPONENT_ARCHIVE_HASH=	\
    sha256:1ff33929f042fa333aed1e8923aa628c3ee9e1eb85512686c55092d1e5a9dfa9
COMPONENT_ARCHIVE_URL=	http://www.mega-nerd.com/libsndfile/files/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/libsndfile
COMPONENT_ANITYA_ID=	13277

TPNO=			34734

TEST_TARGET= install $(TEST_32_and_64)
SYSTEM_TEST_TARGET= build $(SYSTEM_TEST_32_and_64)
include $(WS_MAKE_RULES)/common.mk

# Needed to get tests/header_test.c to compile successfully on SPARC.
gcc_XREGS.sparc=	-mapp-regs

# Get correct libsndfile.so.1 from the proto area.
TEST_LIBPATH.32 =	$(PROTOUSRLIBDIR)
TEST_LIBPATH.64 =	$(PROTOUSRLIBDIR64)
COMPONENT_TEST_ENV +=	LD_LIBRARY_PATH=$(TEST_LIBPATH.$(BITS))

# Need to use GNU sed otherwise we get a:
# Error : sfversion <version> and PACKAGE_VERSION <version> don't match."
# failure from the test_wrapper.sh script.
COMPONENT_TEST_ENV +=   PATH="$(GNUBIN):$(PATH)"
COMPONENT_SYSTEM_TEST_ENV +=   PATH="$(GNUBIN):$(PATH)"

# Two tests fail for 32-bit SPARC, so we have 4 master test files.
COMPONENT_TEST_MASTER = \
	$(COMPONENT_TEST_RESULTS_DIR)/results-$(BITS)-$(MACH).master

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

REQUIRED_PACKAGES += codec/flac
ifeq ($(BUILD_TYPE), evaluation)
REQUIRED_PACKAGES += codec/ogg-vorbis
else
REQUIRED_PACKAGES += codec/libogg
REQUIRED_PACKAGES += codec/libvorbis
endif
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += system/library/math
