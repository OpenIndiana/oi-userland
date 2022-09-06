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
COMPONENT_VERSION=	2.19.2
COMPONENT_LICENSE=	BSD-2-Clause
COMPONENT_PROJECT_URL=	https://botan.randombit.net/
COMPONENT_SUMMARY= 	Crypto and TLS for C++11
COMPONENT_SRC=		Botan-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
	sha256:3af5f17615c6b5cd8b832d269fb6cb4d54ec64f9eb09ddbf1add5093941b4d75
COMPONENT_ARCHIVE_URL=	https://botan.randombit.net/releases/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=library/security/botan
COMPONENT_CLASSIFICATION=System/Security
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

PYTHON_VERSION= 3.9
CONFIG_SHELL =  /usr/bin/python$(PYTHON_VERSION)
CONFIGURE_SCRIPT= $(SOURCE_DIR)/configure.py

# cleanup CONFIGURE_OPTIONS presettings to prevent 
# ERROR:root:Unhandled option(s): CC= CXX= F77= FC= CFLAGS= CXXFLAGS= FFLAGS= FCFLAGS= LDFLAGS= PKG_CONFIG_PATH=
CONFIGURE_OPTIONS= 
CONFIGURE_OPTIONS+= --prefix=/usr
CONFIGURE_OPTIONS+= --cpu=x86_64
CONFIGURE_OPTIONS+= --docdir=/usr/share/doc
CONFIGURE_OPTIONS+= --libdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS+= --includedir=/usr/include
CONFIGURE_OPTIONS+= --cc gcc
CONFIGURE_OPTIONS+= --cc-bin $(CXX)
CONFIGURE_OPTIONS+= --os solaris
CONFIGURE_OPTIONS+= --with-bzip2
CONFIGURE_OPTIONS+= --with-zlib
CONFIGURE_OPTIONS+= --with-python-versions=$(PYTHON_VERSION)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/python-39
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
