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
# Copyright (c) 2020, 2021, Oracle and/or its affiliates.
#

# parfait is a bit unhappy (24796622)
export PARFAIT_BUILD=no

BUILD_BITS =		64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mozjs
COMPONENT_VERSION=	78.11.0
COMPONENT_PROJECT_URL=	https://developer.mozilla.org/en-US/docs/Mozilla/Projects/SpiderMonkey
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:5ad54ac2b0368b9748e08756658eb988d65e5bb088d91baf43267486bcbf1d26
# Upstream no longer delivers mozjs archives; it needs to be extracted from
# the firefox archive instead. Archives are hence only available directly in
# the Userland package cache, and no online alternative is available.
# Check the gnome releng location for tarballs if available
#COMPONENT_ARCHIVE_URL=	http://ftp.cse.buffalo.edu/pub/Gnome/teams/releng/tarballs-needing-help/mozjs/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/teams/releng/tarballs-needing-help/mozjs/$(COMPONENT_ARCHIVE)


CXXFLAGS +=		-std=c++17
GCC_VERSION=	10
GNU_ARCH=		x86_64-sun-solaris

# Only used during build process.
PYTHON_VERSION= 3.7
PYTHON_VERSIONS= 3.7

# Tests hook up need work
TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# configure script is not at root of source tree.
CONFIGURE_SCRIPT= $(SOURCE_DIR)/js/src/configure

CONFIGURE_ENV += PYTHON="$(PYTHON)"
CONFIGURE_ENV += PYTHON3="$(PYTHON)"
CONFIGURE_ENV += LDSHARED="$(CC) -shared"
CONFIGURE_ENV += NSPR_CONFIG="/usr/bin/pkg-config nspr"

CONFIGURE_OPTIONS = --prefix=/usr
CONFIGURE_OPTIONS += --libdir=$(USRLIBDIR64)

CONFIGURE_OPTIONS += --target=$(GNU_ARCH)
CONFIGURE_OPTIONS += --disable-jemalloc
CONFIGURE_OPTIONS += --enable-ctypes
CONFIGURE_OPTIONS += --disable-tests
CONFIGURE_OPTIONS += --with-intl-api
# Resulting packages are a few hundred megabytes larger without this!
CONFIGURE_OPTIONS += --enable-install-strip
CONFIGURE_OPTIONS += --enable-readline
CONFIGURE_OPTIONS += --enable-shared-js
CONFIGURE_OPTIONS += --enable-system-ffi
CONFIGURE_OPTIONS += --with-system-icu
CONFIGURE_OPTIONS += --with-system-zlib
CONFIGURE_OPTIONS += --enable-strip
CONFIGURE_OPTIONS += --with-system-nspr
LDFLAGS += -z gnu-version-script-compat

# js coredumps on sparc - see bug 24935318
ifeq ($(MACH), sparc)
LD_EXEC_OPTIONS += -M $(WS_COMPONENTS)/desktop/polkit/mapfile
COMPONENT_BUILD_ENV += LD_EXEC_OPTIONS="$(LD_EXEC_OPTIONS)"
COMPONENT_INSTALL_ENV += LD_EXEC_OPTIONS="$(LD_EXEC_OPTIONS)"
endif

