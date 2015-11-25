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

MODULES_CONFIGURE = $(CONFIGURE_64)
MODULES_BUILD = $(BUILD_64)
MODULES_INSTALL = $(INSTALL_64)
MODULES_TEST = $(TEST_64)

APACHE_24_USR_PREFIX=/usr/apache2/2.4

VARIANT_APACHE_24 =	$(BUILD_DIR)/apache24

VARIANTS_64 = $(VARIANT_APACHE_22) $(VARIANT_APACHE_24)

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

DEFAULT_COMPILER?=yes

ifeq   ($(strip $(DEFAULT_COMPILER)),no)
CC=
CXX=
endif

PATH=$(SPRO_VROOT)/bin:/usr/bin:/usr/gnu/bin
ifeq   ($(strip $(PARFAIT_BUILD)),yes)
PATH=$(PARFAIT_TOOLS):$(SPRO_VROOT)/bin:/usr/bin
endif

REQUIRED_PACKAGES += web/server/apache-24
