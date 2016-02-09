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
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		harfbuzz
COMPONENT_VERSION=	1.0.6
COMPONENT_PROJECT_URL=	http://www.freedesktop.org/wiki/Software/HarfBuzz/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:f616a7fbdc78a627043f9029000bf08c0c71df59cde4143fc92a014f6a993b26
COMPONENT_ARCHIVE_URL=	http://www.freedesktop.org/software/harfbuzz/release/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/harfbuzz

TPNO=			25623

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure-32_and_64.mk

# Requires newer version of gobject-introspection from Desktop, available in
# S12 but not 11.3, so do not publish.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_32_and_64=
INSTALL_32_and_64=
PUBLISH_STAMP=
endif

include $(WS_MAKE_RULES)/common-32_and_64.mk

# For now, all things built for C++11 require gcc.
COMPILER = gcc
CXXFLAGS += -std=c++11

CONFIGURE_ENV += CC="$(CC) $(CC_BITS)"
CONFIGURE_ENV += CFLAGS="$(CFLAGS)"
CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_ENV += CXXFLAGS="$(CXXFLAGS)"
# Required by other components.
CONFIGURE_OPTIONS += --enable-introspection
# Required by other components.
CONFIGURE_OPTIONS += --with-glib
# Required by other components.
CONFIGURE_OPTIONS += --with-gobject
# Requires GNU-ABI compatible build of ICU.
CONFIGURE_OPTIONS += --with-icu
# build the API documentation
CONFIGURE_OPTIONS += --enable-gtk-doc

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_ARGS =   -k -i
COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/TOTAL:/p" ' \
        '-e "/SKIP:/p" ' \
        '-e "/PASS:/p" ' \
        '-e "/FAIL:/p" ' \
        '-e "/XFAIL:/p" ' \
        '-e "/XERROR:/p" ' \
        '-e "/ERROR:/p" '

configure:      $(CONFIGURE_32_and_64)

build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)

test:           $(TEST_32_and_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)

REQUIRED_PACKAGES += developer/build/autoconf
REQUIRED_PACKAGES += developer/build/automake
REQUIRED_PACKAGES += developer/build/gnu-make
REQUIRED_PACKAGES += developer/build/pkg-config
REQUIRED_PACKAGES += developer/icu
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/math
