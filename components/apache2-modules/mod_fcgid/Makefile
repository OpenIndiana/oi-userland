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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mod_fcgid
COMPONENT_VERSION=	2.3.9
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://httpd.apache.org/mod_fcgid/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:1cbad345e3376b5d7c8f9a62b471edd7fa892695b90b79502f326b4692a679cf
COMPONENT_ARCHIVE_URL=	http://archive.apache.org/dist/httpd/mod_fcgid/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/apache

include ../../../make-rules/prep.mk
include ../../../make-rules/justmake.mk
include ../../../make-rules/ips.mk

PATCH_LEVEL=0

VARIANT_APACHE22 =       $(BUILD_DIR)/apache-22
VARIANT_APACHE24 =       $(BUILD_DIR)/apache-24

VARIANTS = $(VARIANT_APACHE22) $(VARIANT_APACHE24)

BUILD_32 = $(VARIANTS:%=%/$(MACH32)/.built)
BUILD_64 = $(VARIANTS:%=%/$(MACH64)/.built)

INSTALL_32 = $(VARIANTS:%=%/$(MACH32)/.installed)
INSTALL_64 = $(VARIANTS:%=%/$(MACH64)/.installed)

$(VARIANT_APACHE22)/$(MACH64)/.configured: BITS=64
$(VARIANT_APACHE24)/$(MACH64)/.configured:  BITS=64

$(VARIANT_APACHE22)/$(MACH32)/.built: APXS=/usr/apache2/2.2/bin/apxs
$(VARIANT_APACHE22)/$(MACH64)/.built: APXS=/usr/apache2/2.2/bin/$(MACH64)/apxs
$(VARIANT_APACHE24)/$(MACH32)/.built: APXS=/usr/apache2/2.4/bin/apxs
$(VARIANT_APACHE24)/$(MACH64)/.built: APXS=/usr/apache2/2.4/bin/$(MACH64)/apxs

COMPONENT_PRE_BUILD_ACTION= ( cd $(@D); APXS=$(APXS) ./configure.apxs )

PATH=$(SPRO_VROOT)/bin:/usr/bin:/usr/gnu/bin

build: $(BUILD_32_and_64) $(SOURCE_DIR)/fcgid.conf-24

$(SOURCE_DIR)/fcgid.conf-24: $(SOURCE_DIR)/.prep
	$(GSED) -e 's:apache2/2\.2:apache2/2.4:g' $(COMPONENT_DIR)/fcgid.conf > $@

install: $(INSTALL_32_and_64)
	$(TOUCH) $(BUILD_DIR)

test: $(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../../make-rules/depend.mk
