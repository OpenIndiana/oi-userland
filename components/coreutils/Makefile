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

COMPONENT_NAME=		coreutils
COMPONENT_VERSION=	8.16
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/coreutils/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:2a458fead15d9336f46bb4304cc3eaa6ed9407b9130e7ee2ec533909881d2067
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/coreutils/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/gnu-coreutils

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_PREFIX	 =	/usr/gnu
CONFIGURE_OPTIONS	+=	--libdir=/usr/lib
CONFIGURE_OPTIONS	+=	--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS	+=	CPPFLAGS=-I/usr/include/gmp
CONFIGURE_OPTIONS	+=	CFLAGS="$(CFLAGS)"

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

# Needed for "gmake test" to work successfully.
# If SHELLOPTS is exported (as it is by the userland makefiles),
# then all shell options get exported to child invocations of bash,
# which results in test failures due to nounset and xtrace being
# set unexpectedly, and errors such as "$1: unbound variable" and
# diffs failing due to script tracing in output files.
unexport SHELLOPTS

# Get the binaries to test from the component proto area.
COMPONENT_TEST_ENV +=   PATH=$(PROTOUSRSBINDIR):/usr/bin

test:		install $(TEST_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
