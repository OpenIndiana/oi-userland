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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mod_security2
COMPONENT_VERSION=	2.7.7
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://www.modsecurity.org/
COMPONENT_SRC_NAME=	modsecurity-apache
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)_$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:11e05cfa6b363c2844c6412a40ff16f0021e302152b38870fd1f2f44b204379b
COMPONENT_ARCHIVE_URL= \
    $(COMPONENT_PROJECT_URL)tarball/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/apache

VARIANT_APACHE22 =       $(BUILD_DIR)/apache-22
VARIANT_APACHE24 =       $(BUILD_DIR)/apache-24

VARIANTS = $(VARIANT_APACHE22) $(VARIANT_APACHE24)

BUILD_32 = $(VARIANTS:%=%/$(MACH32)/.built)
BUILD_64 = $(VARIANTS:%=%/$(MACH64)/.built)

INSTALL_32 = $(VARIANTS:%=%/$(MACH32)/.installed)
INSTALL_64 = $(VARIANTS:%=%/$(MACH64)/.installed)

$(VARIANT_APACHE22)/$(MACH64)/.configured: BITS=64
$(VARIANT_APACHE24)/$(MACH64)/.configured:  BITS=64

$(VARIANT_APACHE22)/%/.configured: APACHE_USR_PREFIX=/usr/apache2/2.2
$(VARIANT_APACHE24)/%/.configured: APACHE_USR_PREFIX=/usr/apache2/2.4

include ../../../make-rules/prep.mk
include ../../../make-rules/configure.mk
include ../../../make-rules/ips.mk

APXS.32=	$(APACHE_USR_PREFIX)/bin/apxs
APXS.64=	$(APACHE_USR_PREFIX)/bin/$(MACH64)/apxs

CONFIGURE_OPTIONS += LTFLAGS="--silent --tag=CC"
CONFIGURE_OPTIONS += --with-apxs=$(APXS.$(BITS))
CONFIGURE_OPTIONS += --with-apr=`$(APXS.$(BITS)) -q APR_CONFIG`
CONFIGURE_OPTIONS += --with-apu=`$(APXS.$(BITS)) -q APU_CONFIG`

COMPONENT_TEST_ARGS += CFLAGS="$(CFLAGS) -DMSC_TEST"

build: $(BUILD_32_and_64) $(SOURCE_DIR)/modsecurity.conf-recommended-24
	$(TOUCH) $(BUILD_DIR)

$(SOURCE_DIR)/modsecurity.conf-recommended-24: $(SOURCE_DIR)/.prep
	$(GSED) -e 's:apache2/2\.2:apache2/2.4:g' $(SOURCE_DIR)/modsecurity.conf-recommended > $@

test: $(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../../make-rules/depend.mk
