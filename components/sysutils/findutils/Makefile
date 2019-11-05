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
# Copyright (c) 2012, 2017, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2019, Michal Nowak
#

BUILD_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         findutils
COMPONENT_VERSION=      4.7.0
COMPONENT_SUMMARY=      GNU findutils
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/findutils/
COMPONENT_FMRI=         file/gnu-findutils
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:c5fefbdf9858f7e4feb86f036e1247a54c79fc2d8e4b7064d5aaa1f47dfa789a
COMPONENT_ARCHIVE_URL= \
	http://ftp.gnu.org/pub/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      GPLv2

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_PREFIX = $(GNUDIR)

# Disable the leaf optimisation feature, because the st_nlinks directory
# field is incorrect on ZFS file systems.
CONFIGURE_OPTIONS +=	--disable-leaf-optimisation

# Run all the tests even if there is a failure
COMPONENT_TEST_ARGS += -k
COMPONENT_TEST_ENV +=	PATH="$(PATH.gnu)"
COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/^PASS:/p" ' \
	'-e "/^FAIL:/p" ' \
	'-e "/^SKIP:/p" ' \
	'-e "/^\# /p" '

# Needed for "gmake test" to work successfully.
# Otherwise we see errors such as:
# FAIL: exec-nogaps.old-O3, sh: SHELLOPTS: readonly variable
unexport SHELLOPTS

# Test dependencies:
REQUIRED_PACKAGES += developer/versioning/cvs
REQUIRED_PACKAGES += developer/versioning/git

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
