#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2015 Adam Stevko
# Copyright 2021, 2023 Andreas Wacknitz
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= botan
COMPONENT_VERSION= 3.2.0
COMPONENT_SUMMARY= Crypto and TLS for Modern C++
COMPONENT_PROJECT_URL= https://botan.randombit.net/
COMPONENT_SRC= Botan-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:049c847835fcf6ef3a9e206b33de05dd38999c325e247482772a5598d9e5ece3
COMPONENT_ARCHIVE_URL= https://botan.randombit.net/releases/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI= library/security/botan
COMPONENT_CLASSIFICATION= System/Security
COMPONENT_LICENSE= BSD-2-Clause
COMPONENT_LICENSE_FILE= license.txt

# add for using variable in manifest
PKG_VARS += PYTHON_VERSION

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION = ( $(CLONEY) $(SOURCE_DIR) $(@D) )

COMPONENT_POST_INSTALL_ACTION = ( \
	cd $(PROTO_DIR) && \
	mkdir -p .$(PYTHON_LIB) && \
	mv usr/lib/$(MACH64)/python$(PYTHON_VERSION)/site-packages/botan3.py .$(PYTHON_LIB) && \
	$(CONFIG_SHELL) -m py_compile .$(PYTHON_LIB)/botan3.py )

CONFIG_SHELL= $(PYTHON)
CONFIGURE_SCRIPT= $(SOURCE_DIR)/configure.py

# cleanup CONFIGURE_OPTIONS presettings to prevent 
# ERROR:root:Unhandled option(s): CC= CXX= F77= FC= CFLAGS= CXXFLAGS= FFLAGS= FCFLAGS= LDFLAGS= PKG_CONFIG_PATH=
CONFIGURE_OPTIONS= 
CONFIGURE_OPTIONS += --prefix=/usr
ifeq ($(strip $(MACH)),i386)
CONFIGURE_OPTIONS += --cpu=x86_64
else
CONFIGURE_OPTIONS += --cpu=sparc64
endif

CONFIGURE_OPTIONS += --disable-static-library
CONFIGURE_OPTIONS += --libdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS += --os solaris
CONFIGURE_OPTIONS += --with-bzip2
CONFIGURE_OPTIONS += --with-lzma
CONFIGURE_OPTIONS += --with-zlib
CONFIGURE_OPTIONS += --with-sqlite3
CONFIGURE_OPTIONS += --with-python-versions=$(PYTHON_VERSION)

COMPONENT_TEST_TRANSFORMS += \
	' -e "s/in [0-9]*.[0-9]* msec //" ' \
	' -e "s/in [0-9]*.[0-9]* sec //" ' \
	' -n ' \
	' -e "/ok/p" ' \
	' -e "/:/p" '

# Manually added dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
