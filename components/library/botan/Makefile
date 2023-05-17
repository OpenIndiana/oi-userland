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
# Copyright 2021 Andreas Wacknitz
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		botan
COMPONENT_VERSION=	2.19.3
COMPONENT_REVISION=	2
COMPONENT_SUMMARY= 	Crypto and TLS for C++11
COMPONENT_PROJECT_URL=	https://botan.randombit.net/
COMPONENT_SRC=		Botan-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:dae047f399c5a47f087db5d3d9d9e8f11ae4985d14c928d71da1aff801802d55
COMPONENT_ARCHIVE_URL=	https://botan.randombit.net/releases/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=library/security/botan
COMPONENT_CLASSIFICATION=System/Security
COMPONENT_LICENSE=	BSD-2-Clause
COMPONENT_LICENSE_FILE=license.txt

# add for using variable in manifest
PKG_VARS+= PYTHON_VERSION
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
        ($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_POST_INSTALL_ACTION = \
	( cd $(PROTO_DIR) && \
	mkdir -p .$(PYTHON_LIB) && \
	mv usr/lib/$(MACH64)/python$(PYTHON_VERSION)/site-packages/botan2.py .$(PYTHON_LIB) && \
	$(CONFIG_SHELL) -m py_compile .$(PYTHON_LIB)/botan2.py )

CONFIG_SHELL =  /usr/bin/python$(PYTHON_VERSION)
CONFIGURE_SCRIPT= $(SOURCE_DIR)/configure.py

# cleanup CONFIGURE_OPTIONS presettings to prevent 
# ERROR:root:Unhandled option(s): CC= CXX= F77= FC= CFLAGS= CXXFLAGS= FFLAGS= FCFLAGS= LDFLAGS= PKG_CONFIG_PATH=
CONFIGURE_OPTIONS= 
CONFIGURE_OPTIONS+= --prefix=/usr
ifeq ($(strip $(MACH)),i386)
CONFIGURE_OPTIONS+= --cpu=x86_64
else
CONFIGURE_OPTIONS+= --cpu=sparc64
endif
CONFIGURE_OPTIONS+= --docdir=/usr/share/doc
CONFIGURE_OPTIONS+= --libdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS+= --includedir=/usr/include
CONFIGURE_OPTIONS+= --cc gcc
CONFIGURE_OPTIONS+= --cc-bin $(CXX)
CONFIGURE_OPTIONS+= --os solaris
CONFIGURE_OPTIONS+= --with-bzip2
CONFIGURE_OPTIONS+= --with-zlib
CONFIGURE_OPTIONS+= --with-python-versions=$(PYTHON_VERSION)

COMPONENT_TEST_TRANSFORMS += \
	'-e "s/in [0-9]*.[0-9]* msec //"' \
	'-e "s/in [0-9]*.[0-9]* sec //"' \
	'-n' \
	'-e "/ok/p"' \
	'-e "/:/p"'

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
