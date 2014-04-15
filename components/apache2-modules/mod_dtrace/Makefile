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

COMPONENT_NAME=		mod_dtrace
COMPONENT_VERSION=	0.3.1
COMPONENT_REVISION=	2
COMPONENT_SRC=		src
COMPONENT_PROJECT_URL=	http://prefetch.net/projects/apache_modtrace/
COMPONENT_BUGDB=	utility/apache

include ../../../make-rules/justmake.mk
include ../../../make-rules/ips.mk

VARIANT_APACHE22 =       $(BUILD_DIR)/apache-22
VARIANT_APACHE24 =       $(BUILD_DIR)/apache-24

VARIANTS = $(VARIANT_APACHE22) $(VARIANT_APACHE24)

BUILD_32 = $(VARIANTS:%=%/$(MACH32)/.built)
BUILD_64 = $(VARIANTS:%=%/$(MACH64)/.built)

INSTALL_32 = $(VARIANTS:%=%/$(MACH32)/.installed)
INSTALL_64 = $(VARIANTS:%=%/$(MACH64)/.installed)

$(VARIANTS:%=%/$(MACH32)/.built): Makefile
$(VARIANTS:%=%/$(MACH64)/.built): Makefile

$(VARIANT_APACHE22)/$(MACH32)/.built: COMPONENT_BUILD_ARGS += APXS=/usr/apache2/2.2/bin/apxs
$(VARIANT_APACHE22)/$(MACH32)/.built: COMPONENT_BUILD_ARGS += DTRACE="/usr/sbin/dtrace -32"
$(VARIANT_APACHE22)/$(MACH64)/.built: COMPONENT_BUILD_ARGS += APXS=/usr/apache2/2.2/bin/$(MACH64)/apxs
$(VARIANT_APACHE22)/$(MACH64)/.built: COMPONENT_BUILD_ARGS += DTRACE="/usr/sbin/dtrace -64"
$(VARIANT_APACHE22)/$(MACH64)/.built: BITS=64
$(VARIANT_APACHE24)/$(MACH32)/.built: COMPONENT_BUILD_ARGS += APXS=/usr/apache2/2.4/bin/apxs
$(VARIANT_APACHE24)/$(MACH32)/.built: COMPONENT_BUILD_ARGS += DTRACE="/usr/sbin/dtrace -32"
$(VARIANT_APACHE24)/$(MACH64)/.built: COMPONENT_BUILD_ARGS += APXS=/usr/apache2/2.4/bin/$(MACH64)/apxs
$(VARIANT_APACHE24)/$(MACH64)/.built: COMPONENT_BUILD_ARGS += DTRACE="/usr/sbin/dtrace -64"
$(VARIANT_APACHE24)/$(MACH64)/.built: BITS=64

COMPONENT_BUILD_ENV +=	CFLAGS="$(CFLAGS)"

PATH=$(SPRO_VROOT)/bin:/usr/bin:/usr/gnu/bin

download:

clobber: clean

$(SOURCE_DIR)/.prep:
	$(TOUCH) $@

clean::
	$(RM) $(SOURCE_DIR)/.prep

build: $(BUILD_32_and_64)
	$(TOUCH) $(BUILD_DIR)

test: $(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../../make-rules/depend.mk
