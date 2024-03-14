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
# Copyright (c) 2016, 2022, Oracle and/or its affiliates.
#

BUILD_BITS= 64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= fftw
COMPONENT_VERSION= 3.3.10
COMPONENT_SUMMARY= FFTW - library for calculating discrete Fourier transforms
COMPONENT_DESCRIPTION= FFTW is a C subroutine library for computing the discrete Fourier transform (DFT) in one or more dimensions, of arbitrary input size, and of both real and complex data
COMPONENT_PROJECT_URL= https://fftw.org
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:56c932549852cddcfafdab3820b0200c7742675be92179e59e6215b340e26467
COMPONENT_ARCHIVE_URL= $(COMPONENT_PROJECT_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI= library/fftw-3
COMPONENT_CLASSIFICATION= Development/High Performance Computing
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE= GPLv2

# Need to build regular, float, and long-double variants
VARIANTS=			f l
VARIANT_DIRS_32=	$(VARIANTS:%=$(BUILD_DIR)/$(MACH32)-%)
VARIANT_DIRS_64=	$(VARIANTS:%=$(BUILD_DIR)/$(MACH64)-%)

CONFIGURE_32 +=		$(VARIANT_DIRS_32:%=%/.configured)
CONFIGURE_64 +=		$(VARIANT_DIRS_64:%=%/.configured)
BUILD_32 +=			$(VARIANT_DIRS_32:%=%/.built)
BUILD_64 +=			$(VARIANT_DIRS_64:%=%/.built)
INSTALL_32 +=		$(VARIANT_DIRS_32:%=%/.installed)
INSTALL_64 +=		$(VARIANT_DIRS_64:%=%/.installed)
TEST_32 +=			$(VARIANT_DIRS_32:%=%/.tested-and-compared)
TEST_64 +=			$(VARIANT_DIRS_64:%=%/.tested-and-compared)
SYSTEM_TEST_32 +=	$(VARIANT_DIRS_32:%=%/.system-tested-and-compared)
SYSTEM_TEST_64 +=	$(VARIANT_DIRS_64:%=%/.system-tested-and-compared)

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --disable-fortran
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-threads
CONFIGURE_OPTIONS += --with-combined-threads

CONFIGURE_OPTIONS.f += --enable-sse2
CONFIGURE_OPTIONS.l += --enable-sse2
CONFIGURE_OPTIONS.f= --enable-float
CONFIGURE_OPTIONS.l= --enable-long-double
CONFIGURE_OPTIONS += $(CONFIGURE_OPTIONS.$(VARIANT))

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

COMPONENT_TEST_BUILD_DIR= $(BUILD_DIR)/test/$(MACH$(BITS))$(VARIANT:%=-%)

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
