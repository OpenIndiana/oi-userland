#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		openjade
COMPONENT_VERSION=	1.3.2
COMPONENT_PROJECT_URL=	http://openjade.sourceforge.net/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:1d2d7996cc94f9b87d0c51cf0e028070ac177c4123ecbfd7ac1cb8d0b7d322d1
COMPONENT_ARCHIVE_URL=	http://prdownloads.sourceforge.net/openjade/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/openjade

TPNO=			9620

# Added to find the header files since they are not installed in build/*
PKG_PROTO_DIRS += $(COMPONENT_SRC)/style
PKG_PROTO_DIRS += $(COMPONENT_SRC)/groveoa
PKG_PROTO_DIRS += $(COMPONENT_SRC)/grove
PKG_PROTO_DIRS += $(COMPONENT_SRC)/spgrove
PKG_PROTO_DIRS += $(COMPONENT_SRC)/generic
PKG_PROTO_DIRS += $(COMPONENT_SRC)/dsssl

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))
CONFIGURE_SCRIPT = 	$(@D)/configure

CXX +=			$(studio_NORUNPATH)

CONFIGURE_OPTIONS +=    --enable-spincludedir=/usr/include/OpenSP
CONFIGURE_OPTIONS.32 += --enable-splibdir=/usr/lib
CONFIGURE_OPTIONS.64 +=	--enable-splibdir=/usr/lib/$(MACH64)
CONFIGURE_OPTIONS +=    --enable-mif
CONFIGURE_OPTIONS +=	--disable-http
CONFIGURE_OPTIONS += \
--enable-default-catalog="CATALOG:/etc/sgml/catalog:usr/share/sgml/CATALOG"   
CONFIGURE_OPTIONS +=	--datadir=/usr/share/sgml/$(COMPONENT_NAME)
CONFIGURE_OPTIONS +=	CXX="$(CXX)"
CONFIGURE_OPTIONS +=	CXXFLAGS="$(CXXFLAGS)"
CONFIGURE_OPTIONS +=	LDFLAGS="$(LDFLAGS)"

COMPONENT_TEST_DIR =	$(BUILD_DIR)/$(MACH$(BITS))/testsuite
COMPONENT_TEST_ARGS =   -k -i
COMPONENT_TEST_TARGETS =all

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_INSTALL_TARGETS = install install-man

ASLR_MODE =	$(ASLR_ENABLE)

configure:	$(CONFIGURE_32_and_64)

build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)

test:           $(TEST_32_and_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)

REQUIRED_PACKAGES += developer/documentation-tool/opensp
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/c++-runtime
REQUIRED_PACKAGES += system/library/math
