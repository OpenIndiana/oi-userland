#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2015 Alexander Pyhalov
# Copyright (c) 2018 Michal Nowak
#
BUILD_BITS= 32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		fftw
COMPONENT_VERSION=	3.3.10
COMPONENT_PROJECT_URL=	https://www.fftw.org/
COMPONENT_SUMMARY=	FFTW - library for calculating discrete Fourier transforms
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
  sha256:56c932549852cddcfafdab3820b0200c7742675be92179e59e6215b340e26467
COMPONENT_ARCHIVE_URL=	https://www.fftw.org/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=Development/High Performance Computing
COMPONENT_FMRI=		library/fftw-3
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	GPLv2

include $(WS_MAKE_RULES)/common.mk

VARIANT_FFTW = $(BUILD_DIR)/fftw
VARIANT_FFTW_FLOAT = $(BUILD_DIR)/fftw-f

VARIANTS = $(VARIANT_FFTW) $(VARIANT_FFTW_FLOAT)

BUILD_32 = $(VARIANTS:%=%/$(MACH32)/.built)
BUILD_64 = $(VARIANTS:%=%/$(MACH64)/.built)

INSTALL_32 = $(VARIANTS:%=%/$(MACH32)/.installed)
INSTALL_64 = $(VARIANTS:%=%/$(MACH64)/.installed)

TEST_32 = $(VARIANTS:%=%/$(MACH32)/.tested)
TEST_64 = $(VARIANTS:%=%/$(MACH64)/.tested)

$(VARIANT_FFTW)/$(MACH64)/.configured: BITS=64
$(VARIANT_FFTW_FLOAT)/$(MACH64)/.configured:  BITS=64

$(VARIANT_FFTW_FLOAT)/%/.configured: CONFIGURE_OPTIONS+=--enable-float

CONFIGURE_OPTIONS += --enable-threads
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --with-combined-threads
CONFIGURE_OPTIONS += --enable-sse2

$(INSTALL_32):	$(BUILD_32) $(INSTALL_64)
$(INSTALL_64):	$(BUILD_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
