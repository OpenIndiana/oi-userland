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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gd2
COMPONENT_VERSION=      2.0.35
COMPONENT_REVISION=	2
COMPONENT_SRC_NAME=	gd
COMPONENT_SRC=          $(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  http://www.libgd.org/
COMPONENT_ARCHIVE=      gd-$(COMPONENT_VERSION).tar.bz2
COMPONENT_ARCHIVE_HASH= \
    sha256:bf222490749d2a9a9ac3593b01eb55aed98461ff81202414707f61b42aa300f9
COMPONENT_ARCHIVE_URL=  http://pkgs.fedoraproject.org/repo/pkgs/gd/$(COMPONENT_ARCHIVE)/6c6c3dbb7bf079e0bb5fbbfd3bb8a71c/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/gd2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk
include $(WS_MAKE_RULES)/lint-libraries.mk

PATCH_LEVEL = 0

CFLAGS += $(CPP_LARGEFILES)
CPPFLAGS += $(CPP_LARGEFILES)

# Needed for "gmake test" to work.
COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

CONFIGURE_OPTIONS  +=           --includedir=$(CONFIGURE_INCLUDEDIR)/gd2
CONFIGURE_OPTIONS  +=           --disable-static
CONFIGURE_OPTIONS  +=           --disable-rpath
CONFIGURE_OPTIONS  +=           --with-x
CONFIGURE_OPTIONS  +=           --with-pic

COMPONENT_PREP_ACTION = (cd $(@D) ; autoreconf -if)

COMPONENT_TEST_CMD = \
	cmake -DBUILD_TEST=1 .; \
	(cd $(@D)/tests; gmake); \
	ctest .
COMPONENT_TEST_TARGETS =

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

# gdimageline_aa fails
test: 	$(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk

