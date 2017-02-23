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
# Copyright (c) 2016, 2017, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS=		64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		fftw
COMPONENT_VERSION=	3.3.5
COMPONENT_PROJECT_URL=	http://fftw.org
COMPONENT_ARCHIVE_HASH= \
	sha256:8ecfe1b04732ec3f5b7d279fdb8efcad536d555f9d1e8fabd027037d45ea8bcf
COMPONENT_ARCHIVE_URL=	http://fftw.org/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/libfftw
TPNO=			32881
COMPONENT_ANITYA_ID=	803

# Need to build regular, float, and long-double variants
VARIANTS =		f l
VARIANT_DIRS_32 =	$(VARIANTS:%=$(BUILD_DIR)/$(MACH32)-%)
VARIANT_DIRS_64 =	$(VARIANTS:%=$(BUILD_DIR)/$(MACH64)-%)

CONFIGURE_32 +=		$(VARIANT_DIRS_32:%=%/.configured)
CONFIGURE_64 +=		$(VARIANT_DIRS_64:%=%/.configured)
BUILD_32 +=		$(VARIANT_DIRS_32:%=%/.built)
BUILD_64 +=		$(VARIANT_DIRS_64:%=%/.built)
INSTALL_32 +=		$(VARIANT_DIRS_32:%=%/.installed)
INSTALL_64 +=		$(VARIANT_DIRS_64:%=%/.installed)
TEST_32 +=		$(VARIANT_DIRS_32:%=%/.tested-and-compared)
TEST_64 +=		$(VARIANT_DIRS_64:%=%/.tested-and-compared)
SYSTEM_TEST_32 +=	$(VARIANT_DIRS_32:%=%/.system-tested-and-compared)
SYSTEM_TEST_64 +=	$(VARIANT_DIRS_64:%=%/.system-tested-and-compared)

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS +=	--disable-fortran
CONFIGURE_OPTIONS +=	--enable-shared
CONFIGURE_OPTIONS +=	--disable-static

CONFIGURE_OPTIONS.f =	--enable-float
CONFIGURE_OPTIONS.l =	--enable-long-double
CONFIGURE_OPTIONS +=	$(CONFIGURE_OPTIONS.$(VARIANT))

$(BUILD_DIR_32)-f/.%:	VARIANT=f
$(BUILD_DIR_64)-f/.%:	VARIANT=f
$(BUILD_DIR_32)-l/.%:	VARIANT=l
$(BUILD_DIR_64)-l/.%:	VARIANT=l

$(BUILD_DIR_32)-f/.%:	BITS=32
$(BUILD_DIR_32)-l/.%:	BITS=32
$(BUILD_DIR_64)-f/.%:	BITS=64
$(BUILD_DIR_64)-l/.%:	BITS=64

# FFTW selects random transforms for each test run, so just print results
COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
	'-e "/         FFTW/p" '
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_BUILD_DIR =      $(BUILD_DIR)/test/$(MACH$(BITS))$(VARIANT:%=-%)

REQUIRED_PACKAGES += system/library/math
