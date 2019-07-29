#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2019 Rouven Weiler
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		wavpack
COMPONENT_FMRI =		audio/wavpack
COMPONENT_VERSION =		5.1.0
COMPONENT_PROJECT_URL =		http://www.wavpack.com/
COMPONENT_SRC =			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH =	sha256:1939627d5358d1da62bc6158d63f7ed12905552f3a799c799ee90296a7612944
COMPONENT_ARCHIVE_URL =		$(COMPONENT_PROJECT_URL)$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =             BSD
COMPONENT_LICENSE_FILE =        $(COMPONENT_NAME).license
COMPONENT_SUMMARY =		wavpack - Hybrid Lossless Audio Compression
COMPONENT_CLASSIFICATION =	System/Multimedia Libraries

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk


CONFIGURE_OPTIONS +=	--disable-static
CONFIGURE_OPTIONS +=	--enable-legacy
CONFIGURE_OPTIONS +=	--disable-asm

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:           $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
