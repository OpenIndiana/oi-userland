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
# Copyright 2017 Alexander Pyhalov
#

BUILD_STYLE=configure
BUILD_BITS=32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         xmlrpc-c
COMPONENT_VERSION=      1.39.12
COMPONENT_REVISION=     2
COMPONENT_FMRI=         library/xmlrpc-c
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_PROJECT_URL=  http://xmlrpc-c.sourceforge.net/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_NAME)-$(COMPONENT_VERSION).tgz
COMPONENT_ARCHIVE_HASH= sha256:d830f3264a832dfe09f629cc64036acfd08121692526d0fabe090f7ff881ce08
COMPONENT_ARCHIVE_URL=  https://sourceforge.net/projects/xmlrpc-c/files/Xmlrpc-c%20Super%20Stable/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      BSD-like
COMPONENT_LICENSE_FILE= doc/COPYING
COMPONENT_SUMMARY=      XMLRPC C/C++ Library

include $(WS_MAKE_RULES)/common.mk

# Parallel build can fail
COMPONENT_BUILD_ARGS=

CPPFLAGS += -D_FILE_OFFSET_BITS=64
# This one fixes tests build
LDFLAGS += -lnsl -lsocket

COMMON_ENV = CFLAGS="$(CFLAGS)"
COMMON_ENV += CXXFLAGS="$(CXXFLAGS)"
COMMON_ENV += CPPFLAGS="$(CPPFLAGS)"
COMMON_ENV += LADD="$(LDFLAGS)"

# Note, this is not autoconf/automake-based package
# Missing files in build dir during build without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))
CONFIGURE_SCRIPT = $(@D)/configure

COMPONENT_BUILD_ENV += $(COMMON_ENV)
COMPONENT_INSTALL_ENV += $(COMMON_ENV)
COMPONENT_TEST_ENV += $(COMMON_ENV)

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/Running/p" ' \
        '-e "/passed/p" ' \
        '-e "/failed/p" ' \
        '-e "/tests/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += web/curl
