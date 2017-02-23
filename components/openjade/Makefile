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
# Copyright (c) 2015, 2017, Oracle and/or its affiliates. All rights reserved.
#
COMPILER= gcc
BUILD_BITS= 64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		openjade
COMPONENT_VERSION=	1.3.2
COMPONENT_PROJECT_URL=	http://openjade.sourceforge.net/
COMPONENT_ARCHIVE_HASH=	\
    sha256:1d2d7996cc94f9b87d0c51cf0e028070ac177c4123ecbfd7ac1cb8d0b7d322d1
COMPONENT_ARCHIVE_URL=	http://prdownloads.sourceforge.net/openjade/$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	2564

TPNO=			9620

# Added to find the header files since they are not installed in build/*
PKG_PROTO_DIRS += $(COMPONENT_SRC)/style
PKG_PROTO_DIRS += $(COMPONENT_SRC)/groveoa
PKG_PROTO_DIRS += $(COMPONENT_SRC)/grove
PKG_PROTO_DIRS += $(COMPONENT_SRC)/spgrove
PKG_PROTO_DIRS += $(COMPONENT_SRC)/generic
PKG_PROTO_DIRS += $(COMPONENT_SRC)/dsssl

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION += ($(CLONEY) $(SOURCE_DIR) $(@D))

# Prevent libtool from embedding runpath (via -R).
COMPONENT_POST_CONFIGURE_ACTION += \
	$(GSED) -i -e 's/hardcode_into_libs=yes/hardcode_into_libs=no/' $(@D)/libtool; \
	$(GSED) -i -e 's/hardcode_libdir_flag_spec=.*/hardcode_libdir_flag_spec=""/' $(@D)/libtool;

CONFIGURE_SCRIPT = 	$(@D)/configure

# Expects GNU install.
CONFIGURE_ENV += INSTALL="$(INSTALL)"

# Get opensp header files and libraries out of the opensp build prototype area.
OPENSP_BASE = $(WS_COMPONENTS)/opensp/build/prototype/$(MACH)

CONFIGURE_OPTIONS +=    --enable-spincludedir=$(OPENSP_BASE)/$(USRINCDIR)/OpenSP
CONFIGURE_OPTIONS +=	--enable-splibdir=$(OPENSP_BASE)/$(USRLIB.$(BITS))
CONFIGURE_OPTIONS +=    --enable-mif
CONFIGURE_OPTIONS +=	--disable-http
CONFIGURE_OPTIONS +=	--enable-default-catalog="CATALOG:/etc/sgml/catalog:/usr/share/sgml/CATALOG"
CONFIGURE_OPTIONS +=	--datadir=$(USRSHAREDIR)/sgml/$(COMPONENT_NAME)

COMPONENT_TEST_DIR =	$(BUILD_DIR)/$(MACH$(BITS))/testsuite
COMPONENT_TEST_ARGS =   -k -i
COMPONENT_TEST_TARGETS =all

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += \
	'-e "/^[mM]ake/d" '

COMPONENT_INSTALL_TARGETS += install-man

# Workaround broken install targets.
COMPONENT_PRE_INSTALL_ACTION.32 += \
	$(MKDIR) $(PROTOUSRBINDIR)/$(MACH32);

REQUIRED_PACKAGES += developer/documentation-tool/opensp
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/math
