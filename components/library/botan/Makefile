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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		botan
COMPONENT_VERSION=      1.10.9
COMPONENT_REVISION=     2
COMPONENT_LICENSE=      BSD
COMPONENT_PROJECT_URL=  http://botan.randombit.net/
COMPONENT_SUMMARY= 	Crypto and TLS for C++11
COMPONENT_SRC=		Botan-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	\
    sha256:487d27d3a081ae403cf87c0fc78c2a64183f001b48f9feb87e8de1e16fba8df2
COMPONENT_ARCHIVE_URL= http://botan.randombit.net/releases/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIG_SHELL =  /usr/bin/python
CONFIGURE_SCRIPT= $(SOURCE_DIR)/configure.py

CONFIGURE_OPTIONS.64= --cpu=x86_64
CONFIGURE_OPTIONS.32= --cpu=x86_32

CONFIGURE_OPTIONS=  --prefix=/usr
CONFIGURE_OPTIONS+= $(CONFIGURE_OPTIONS.$(BITS))
CONFIGURE_OPTIONS+= --bindir=$(CONFIGURE_BINDIR.$(BITS))
CONFIGURE_OPTIONS+= --docdir=/usr/share/doc
CONFIGURE_OPTIONS+= --libdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS+= --includedir=/usr/include
CONFIGURE_OPTIONS+= --cc gcc
CONFIGURE_OPTIONS+= --cc-bin $(CXX)
CONFIGURE_OPTIONS+= --os sunos
CONFIGURE_OPTIONS+= --enable-sse2
CONFIGURE_OPTIONS+= --enable-altivec
CONFIGURE_OPTIONS+= --enable-movbe
CONFIGURE_OPTIONS+= --with-openssl
CONFIGURE_OPTIONS+= --disable-modules=ecdsa
CONFIGURE_OPTIONS+= --with-bzip2
CONFIGURE_OPTIONS+= --with-zlib

COMPONENT_POST_INSTALL_ACTION= \
            (cd $(PROTOUSRDIR) ;  \
             $(MV)  include/botan-1.10/botan/build.h include/botan-1.10/botan/build-$(BITS).h )

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-6-runtime
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
