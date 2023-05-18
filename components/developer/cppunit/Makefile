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
# Copyright (c) 2013, Igor Kozhukhov <ikozhukhov@gmail.com>.  All rights reserved.
# Copyright (c) 2020, Andreas Wacknitz
#

BUILD_BITS= 64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			cppunit
COMPONENT_VERSION=		1.15.1
COMPONENT_REVISION=		1
COMPONENT_SUMMARY=		Unit Testing Library for C++
COMPONENT_PROJECT_URL=	https://www.freedesktop.org/wiki/Software/cppunit/
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:89c5c6665337f56fd2db36bc3805a5619709d51fb136e51937072f63fcc717a7
COMPONENT_ARCHIVE_URL=	https://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			developer/cppunit
COMPONENT_CLASSIFICATION=Development/C++
COMPONENT_LICENSE=		LGPLv2.1
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-doxygen

# Tests failure
unexport SHELLOPTS

COMPONENT_TEST_ENV += LANG=C

COMPONENT_TEST_TRANSFORMS += \
	'-e "/CXX/d"' \
	'-e "/[mM]ake/d"' \
	'-e "/^[mM]aking/d"' \
	'-e "s|make.*: Leaving directory.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|make.*: Entering directory.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|make.*: Nothing to be done.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "/^XXX_REMOVE_XXX$$/d" '

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
