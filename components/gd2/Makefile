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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=         gd
COMPONENT_VERSION=      2.0.35
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  http://www.libgd.org/
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha1:ad6b6ce72c83e513ef7c31b7f8a5c6f07a2e0143
COMPONENT_ARCHIVE_URL=  http://www.libgd.org/releases/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

LIBNAME =       gd
LINTOUT =       lint.out

PKG_CONFIG_PATH_32 = /usr/lib/pkgconfig
PKG_CONFIG_PATH_64 = /usr/lib/$(MACH64)/pkgconfig

PATCH_LEVEL = 0

CFLAGS += $(CPP_LARGEFILES)
CPPFLAGS += $(CPP_LARGEFILES)

CONFIGURE_ENV += CFLAGS="$(CFLAGS)"
CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_ENV += PKG_CONFIG_PATH="$(PKG_CONFIG_PATH_$(BITS))"

CONFIGURE_OPTIONS  +=           --includedir=$(CONFIGURE_INCLUDEDIR)/gd2
CONFIGURE_OPTIONS  +=           --disable-static
CONFIGURE_OPTIONS  +=           --disable-rpath
CONFIGURE_OPTIONS  +=           --with-x
CONFIGURE_OPTIONS  +=           --with-pic

PKG_PROTO_DIRS +=	$(COMPONENT_SRC)

COMPONENT_PREP_ACTION = (cd $(@D) ; autoconf)

COMPONENT_POST_BUILD_ACTION = \
	 (cd $(@D); $(LINT) -nsvx $(CC_BITS) -o $(LIBNAME) -I$(@D) \
			-I$(COMPONENT_DIR)/$(COMPONENT_SRC) \
			$(COMPONENT_DIR)/llib-l$(LIBNAME) > $(LINTOUT) 2>&1)

COMPONENT_POST_INSTALL_ACTION = \
	(cd $(@D); $(INSTALL) llib-l$(LIBNAME).ln \
			$(PROTO_DIR)/$(CONFIGURE_LIBDIR.$(BITS)))

PROTOUSRSHAREDOCDIR = $(PROTOUSRSHAREDIR)/doc/gd2/html

build: $(BUILD_32_and_64)

GSED =	/usr/gnu/bin/sed

include ../../make-rules/shared-targets.mk

install: $(INSTALL_32_and_64)

test: $(BUILD_32_and_64)
	@echo "There is no test harness for libgd2."
	@echo "Test programs must be run manually and their output"
	@echo "should be visually inspected."

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include ../../make-rules/depend.mk

