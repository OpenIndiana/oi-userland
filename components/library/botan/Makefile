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

BUILD_BITS= 64_and_32
#USE_OPENSSL11= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		botan
COMPONENT_VERSION=	1.10.17
COMPONENT_LICENSE=	BSD
COMPONENT_PROJECT_URL=	https://botan.randombit.net/
COMPONENT_SUMMARY= 	Crypto and TLS for C++11
COMPONENT_SRC=		Botan-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	sha256:6847ffb64b8d2f939dccfecc17bd2c80385d08f7621e2c56d3a335118e823613
COMPONENT_ARCHIVE_URL=	https://botan.randombit.net/releases/old/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/common.mk

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

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
