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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		libsndfile
COMPONENT_VERSION=	1.0.23
COMPONENT_PROJECT_URL=	http://www.mega-nerd.com/libsndfile/
COMPONENT_ARCHIVE_HASH=	\
    sha256:54c9c375598538263395a691f9b30987a2faa3d8a166d27e6a09ba4700223d4d
COMPONENT_ARCHIVE_URL=	http://www.mega-nerd.com/libsndfile/files/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/libsndfile

TPNO=			8890

include $(WS_MAKE_RULES)/common.mk

# Needed for __func__ in cpp_test.cc
CXXFLAGS += $(studio_FEATURES_EXTENSIONS)
CFLAGS +=	$(studio_PIC)

# Master test results are the same for 32-bit and 64-bit, so override
# here, rather than create multiple identical master files.
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

# The additional libsndfile specific set of transforms to be applied to the
# test results to try to normalize them.
COMPONENT_TEST_TRANSFORMS += \
	'-e "s|\(^SunOS\).*|\1|" '

REQUIRED_PACKAGES += codec/flac
REQUIRED_PACKAGES += codec/ogg-vorbis
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += system/library/math
