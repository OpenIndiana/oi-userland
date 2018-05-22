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
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=       cppunit
COMPONENT_VERSION=	  1.14.0
COMPONENT_FMRI=       developer/cppunit
COMPONENT_SUMMARY=    Unit Testing Library for C++
COMPONENT_CLASSIFICATION=Development/C++
COMPONENT_PROJECT_URL=http://www.freedesktop.org/wiki/Software/cppunit/
COMPONENT_SRC=        $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=    $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:3d569869d27b48860210c758c4f313082103a5e58219a7669b52bfd29d674780
COMPONENT_ARCHIVE_URL= \
  http://dev-www.libreoffice.org/src/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=    LGPLv2.1

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-doxygen
CONFIGURE_OPTIONS += --enable-shared

# Tests failure
unexport SHELLOPTS

COMPONENT_TEST_ENV+= LANG=C

COMPONENT_TEST_TRANSFORMS += \
	'-e "/CXX/d"' \
	'-e "/[mM]ake/d"' \
	'-e "/^[mM]aking/d"' \
	'-e "s|make.*: Leaving directory.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|make.*: Entering directory.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|make.*: Nothing to be done.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "/^XXX_REMOVE_XXX$$/d" '

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
