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
#

BUILD_BITS=64_and_32

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libzmq
COMPONENT_VERSION= 4.3.4
COMPONENT_REVISION= 2
COMPONENT_SUMMARY= Open source message queue optimised for performance
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:0ff5a531c9ffaf0dfdc7dc78d13d1383088f454896d252934c429b2554d10559
COMPONENT_ARCHIVE_URL=	https://github.com/zeromq/libzmq/archive/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL= https://zeromq.org/
COMPONENT_FMRI= library/c++/zeromq
# Two licenses in tarball, LGPLv3+ is referenced in their spec-file
COMPONENT_LICENSE_FILE= COPYING.LESSER
COMPONENT_LICENSE= LGPLv3+
COMPONENT_CLASSIFICATION= System/Libraries

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = \
	( cd $(@D) && \
	  libtoolize --copy --force && \
	  aclocal -I m4 && \
	  autoheader && \
	  automake -c -f -a && \
	  autoconf )

COMPONENT_PRE_CONFIGURE_ACTION =	($(CLONEY) $(SOURCE_DIR) $(@D))

# Build docs just once (for one ARCH), parameter varies from version to version
CONFIGURE_OPTIONS.32 +=	--with-docs
CONFIGURE_OPTIONS.64 +=	--without-docs

CONFIGURE_OPTIONS +=	--enable-static=no
CONFIGURE_OPTIONS +=	--with-libsodium

CONFIGURE_OPTIONS +=	--sysconfdir=/etc
CONFIGURE_OPTIONS +=	--localstatedir=/var

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/TOTAL:/p" ' \
	'-e "/SKIP:/p" ' \
	'-e "/PASS:/p" ' \
	'-e "/FAIL:/p" ' \
	'-e "/ERROR:/p" '

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
