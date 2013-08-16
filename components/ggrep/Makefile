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
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		grep
COMPONENT_VERSION=	2.14
COMPONENT_PROJECT_URL=	http://gnu.org/software/grep/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz

COMPONENT_ARCHIVE_HASH=	\
    sha256:e70e801d4fbb16e761654a58ae48bf5020621c95c8e35bd864742577685872e1
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/grep/$(COMPONENT_ARCHIVE)

COMPONENT_BUGDB=	utility/ggrep

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_OPTIONS  +=		--prefix=/usr

# Enable aslr for this component
ASLR_MODE = $(ASLR_ENABLE)

# Needed for "gmake test" to work.
# SHELLOPTS is exported via make-rules/shared-macros.mk,
# causing the braceexpand option to be set.
# This option causes "$1: unbound variable" errors during the check-TESTS,
# and the gnulib-tests don't even run at all.
# Note that the below unexports SHELLOPTS, even for targets
# other than "test." 
unexport SHELLOPTS

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

# 3 expected failures in gnulib-tests:
# test-mbrtowc3.sh, test-mbrtowc4.sh, test-mbsrtowcs4.sh
test:		$(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
