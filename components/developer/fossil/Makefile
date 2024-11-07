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
# Copyright (c) 2023, Jonathan Schleifer. All rights reserved.
#

# localedir is unknown because configure is just a small wrapper over a tcl script
CONFIGURE_DEFAULT_DIRS=no
USE_PARALLEL_BUILD = yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME = fossil
COMPONENT_VERSION = 2.25
COMPONENT_SUMMARY = Distributed SCM with bug tracking and wiki
COMPONENT_SRC = $(COMPONENT_NAME)-src-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE = $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH = sha256:611cfa50d08899eb993a5f475f988b4512366cded82688c906cf913e5191b525
COMPONENT_PROJECT_URL = https://www.fossil-scm.org/
COMPONENT_ARCHIVE_URL = https://fossil-scm.org/home/tarball/version-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI = developer/versioning/fossil
COMPONENT_CLASSIFICATION = Development/Source Code Management
COMPONENT_LICENSE = BSD 2-clause
COMPONENT_LICENSE_FILE = COPYRIGHT-BSD2.txt

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CONFIGURE_ENV += CPPFLAGS=-I/usr/include/fuse

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += library/libfuse
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
