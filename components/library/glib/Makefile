#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016 Alexander Pyhalov
# Copyright 2019 Michal Nowak
# Copyright 2023 Friedrich Kink
#

BUILD_BITS= 64_and_32
BUILD_STYLE= meson
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		glib
HUMAN_VERSION=		2.82.0
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	GNOME core libraries
COMPONENT_ARCHIVE_HASH=	sha256:f4c82ada51366bddace49d7ba54b33b4e4d6067afa3008e4847f41cb9b5c38d3
COMPONENT_FMRI=		library/glib2
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Libraries
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# /usr/lib and /usr/lib/$(MACH64) needed to make dbus-daemon program available
PATH = $(PATH.gnu):/usr/lib:/usr/lib/$(MACH64)

# socketpair(3socket) requires -lsocket -lnsl
LDFLAGS += -lsocket -lnsl

# Support for hexadecimal strings in strtod() is available in C99 mode only,
# but we cannot use -std=c99 because float/double support is broken there
# (https://www.illumos.org/issues/14935)
CFLAGS += -std=gnu11

# We need standard conforming getpwnam_r()/getpwuid_r()
CPPFLAGS += $(CPP_XPG6MODE)

# Some warnings are treated as errors by default but we do not want that
CFLAGS += -Wno-error=format-nonliteral
CFLAGS += -Wno-error=format-security

# We do not have getxattr() so disable xattr
CONFIGURE_OPTIONS += -Dxattr=false
CONFIGURE_OPTIONS += -Dman=true
CONFIGURE_OPTIONS += -Druntime_libdir=$(USRLIBDIR)
CONFIGURE_OPTIONS += -Dcharsetalias_dir=$(USRLIBDIR)
CONFIGURE_OPTIONS += -Druntime_dir=$(VARDIR)/run
CONFIGURE_OPTIONS += -Dselinux=disabled
CONFIGURE_OPTIONS += -Dxattr=false
CONFIGURE_OPTIONS += -Dlibmount=disabled
CONFIGURE_OPTIONS += -Dbsymbolic_functions=false
CONFIGURE_OPTIONS += -Dman=true
CONFIGURE_OPTIONS += -Dfam=true
CONFIGURE_OPTIONS += -Ddtrace=disabled
CONFIGURE_OPTIONS += -Dsystemtap=disabled
CONFIGURE_OPTIONS += -Dsysprof=disabled
# see https://gitlab.gnome.org/GNOME/glib/-/issues/3421
CONFIGURE_OPTIONS += -Dglib_debug=disabled

COMPONENT_POST_CONFIGURE_ACTION= \
  ( cd $(@D); $(GSED) -i "s/_FILE_OFFSET_BITS=64/_FILE_OFFSET_BITS=$(BITS)/g" ./build.ninja )

# We need to install libraries and set correct LD_LIBRARY_PATH before test
$(TEST_TARGET): $(INSTALL_TARGET)

# Dtrace flags
DFLAGS.64 = -64
COMPONENT_BUILD_ENV += DFLAGS=$(DFLAGS.$(BITS))

# Without this the gi-compile-repository loads system libraries which makes the
# typelib compilation to fail
COMPONENT_BUILD_ENV += LD_LIBRARY_PATH=gio:glib:gobject

# necessary otherwise make REQUIRED_PACKAGES will fail
COMPONENT_POST_INSTALL_ACTION.32= $(GSED) -i -e "s:\#!/usr/bin/env .*$$:\#!/usr/bin/python$(PYTHON_VERSION):" $(PROTOUSRBINDIR32)/g*
COMPONENT_POST_INSTALL_ACTION.64= $(GSED) -i -e "s:\#!/usr/bin/env .*$$:\#!/usr/bin/python$(PYTHON_VERSION):" $(PROTOUSRBINDIR)/g*

# We need to install libraries and set correct LD_LIBRARY_PATH before test
$(TEST_TARGET): $(INSTALL_TARGET)

# dbus-daemon is in /usr/lib
COMPONENT_TEST_ENV.32 = LD_LIBRARY_PATH=$(PROTO_DIR)/usr/lib PATH=$(PATH):/usr/lib
COMPONENT_TEST_ENV.64 = LD_LIBRARY_PATH=$(PROTO_DIR)/usr/lib/$(MACH64) PATH=$(PATH):/usr/lib/$(MACH64)
COMPONENT_TEST_ENV = $(COMPONENT_TEST_ENV.$(BITS))
COMPONENT_TEST_ENV += LC_ALL=C.UTF-8
COMPONENT_TEST_ENV += TZ=UTC

COMPONENT_TEST_TRANSFORMER = $(NAWK)
COMPONENT_TEST_TRANSFORMS = "'/^(Fail|Ok|Expected Fail|Unexpected Pass|Skipped|Timeout)/'"

# Dynamic library version number
SOVER := 0.$(shell printf '%s00.%s' $(wordlist 2,3,$(subst ., ,$(COMPONENT_VERSION))))
SOVER_RE = $(subst .,\.,$(SOVER))

# Replace library version number by SOVER
GENERATE_EXTRA_CMD += | $(GSED) -e 's/$(SOVER_RE)/$$(SOVER)/'

# SOVER is needed for manifest processing
PKG_MACROS += SOVER=$(SOVER)

# Build dependencies
PYTHON_REQUIRED_PACKAGES += library/python/docutils

# dbus-daemon is needed for testing
TEST_REQUIRED_PACKAGES += system/library/dbus

# update-desktop-database is needed for testing
TEST_REQUIRED_PACKAGES += library/desktop/desktop-file-utils

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/python-subunit
PYTHON_REQUIRED_PACKAGES += library/python/testtools
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += library/file-monitor/gamin
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/pcre2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
