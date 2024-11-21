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
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
# Copyright 2016 Jim Klimov
# Copyright 2024 Klaus Ziegler
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libzmq
COMPONENT_VERSION= 4.3.5
COMPONENT_REVISION= 2
COMPONENT_SUMMARY= Open source message queue optimised for performance
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:6c972d1e6a91a0ecd79c3236f04cf0126f2f4dfbbad407d72b4606a7ba93f9c6
COMPONENT_ARCHIVE_URL=	https://github.com/zeromq/libzmq/archive/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL= https://zeromq.org/
COMPONENT_FMRI= library/c++/zeromq
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE= MPL 2.0
COMPONENT_LICENSE_FILE= LICENSE

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = \
	( cd $(@D) && \
	  libtoolize --copy --force && \
	  aclocal -I m4 && \
	  autoheader && \
	  automake -c -f -a && \
	  autoconf )

COMPONENT_PRE_CONFIGURE_ACTION = ( $(CLONEY) $(SOURCE_DIR) $(@D) )

CONFIGURE_OPTIONS +=	--with-docs
CONFIGURE_OPTIONS +=	--enable-static=no
CONFIGURE_OPTIONS +=	--with-libsodium
CONFIGURE_OPTIONS +=	--disable-dependency-tracking

# Necessary for tests
unexport SHELLOPTS

# Build time dependencies (both needed for documentation)
REQUIRED_PACKAGES +=text/asciidoc
REQUIRED_PACKAGES +=text/xmlto

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/security/libsodium
REQUIRED_PACKAGES += system/library
