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
# Copyright (c) 2014, 2015, Oracle and/or its affiliates. All rights reserved.
#
COMPONENT_BUGDB ?=	utility/apache

COMMON_TARGETS=no
include $(WS_MAKE_RULES)/common.mk

MODULES_CONFIGURE ?= $(CONFIGURE_64)
MODULES_BUILD ?= $(BUILD_64)
MODULES_INSTALL ?= $(INSTALL_64)
MODULES_TEST ?= $(NO_TESTS)
MODULES_SYSTEM_TEST ?= $(NO_TESTS)

APACHE_24_USR_PREFIX=/usr/apache2/2.4

VARIANT_APACHE_24 =	$(BUILD_DIR)/apache24

VARIANTS_64 ?= $(VARIANT_APACHE_24)

BUILD_64 = $(VARIANTS_64:%=%/$(MACH64)/.built)

INSTALL_64 = $(VARIANTS_64:%=%/$(MACH64)/.installed)

TEST_64 = $(VARIANTS_64:%=%/$(MACH64)/.tested)

$(VARIANT_APACHE_24)/$(MACH64)/.configured: BITS=64

$(VARIANT_APACHE_24)/$(MACH64)/.built: BITS=64

$(VARIANT_APACHE_24)/$(MACH64)/.tested: BITS=64

$(VARIANT_APACHE_24)/%/.configured: APACHE_USR_PREFIX=$(APACHE_24_USR_PREFIX)

$(VARIANT_APACHE_24)/%/.built: APACHE_USR_PREFIX=$(APACHE_24_USR_PREFIX)

$(VARIANT_APACHE_24)/%/.installed: APACHE_USR_PREFIX=$(APACHE_24_USR_PREFIX)

$(BUILD_DIR)/apache24/$(MACH64)/.configured: APXS=$(APACHE_USR_PREFIX)/bin/apxs

$(BUILD_DIR)/apache24/$(MACH64)/.built: APXS=$(APACHE_USR_PREFIX)/bin/apxs

ASLR_MODE= $(ASLR_NOT_APPLICABLE)

DEFAULT_COMPILER ?= yes

ifeq ($(strip $(BUILD_STYLE)),configure)
CONFIGURE_OPTIONS += --with-apxs=$(APXS)
endif

# Attempt to define shared module targets.
ifeq ($(strip $(MODULES_CONFIGURE)),configure)
configure:	$(MODULES_CONFIGURE)
endif

ifneq ($(strip $(MODULES_BUILD)),)
build:          $(MODULES_BUILD)
endif

ifneq ($(strip $(MODULES_INSTALL)),)
install:        $(MODULES_INSTALL)
endif

ifneq ($(strip $(MODULES_TEST)),)
test:           $(MODULES_TEST)
endif

ifneq ($(strip $(MODULES_SYSTEM_TEST)),)
system-test:    $(MODULES_SYSTEM_TEST)
endif

ifeq   ($(strip $(DEFAULT_COMPILER)),no)
CC=
CXX=
endif

ifeq   ($(strip $(PARFAIT_BUILD)),yes)
PATH=$(PARFAIT_TOOLS):$(SPRO_VROOT)/bin:$(USRBINDIR)
else
PATH=$(SPRO_VROOT)/bin:$(USRBINDIR):$(GNUBIN)
endif

REQUIRED_PACKAGES += web/server/apache-24
