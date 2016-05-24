#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2015 Alexander Pyhalov
# Copyright 2016 Jim Klimov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	libmad
COMPONENT_VERSION=	0.15.1b
IPS_COMPONENT_VERSION=	0.15.1.2
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	A high-quality MPEG Audio Decoder
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:27afcbde70b6539471c0c83cd71f425361763e077987621086337cdbebcd8815
COMPONENT_ARCHIVE_URL=	\
	http://sourceforge.net/projects/mad/files/libmad/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://www.underbit.com/products/mad/
COMPONENT_LICENSE=		GPLv2
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_CLASSIFICATION=	System/Multimedia Libraries
COMPONENT_FMRI=		library/audio/libmad

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

FP_ARCH.32 = default
FP_ARCH.64 = 64bit

CONFIGURE_OPTIONS  += --enable-accuracy
CONFIGURE_OPTIONS  += --enable-shared
CONFIGURE_OPTIONS  += --disable-static
CONFIGURE_OPTIONS  += --enable-fpm=$(FP_ARCH.$(BITS))
CONFIGURE_OPTIONS  += --enable-sso
CONFIGURE_OPTIONS  += --enable-strict-iso
# disable architecture-specific optimizations
CONFIGURE_OPTIONS  += --disable-aso

# Setup mad.h file to support 32 & 64 bit.
#
COMPONENT_POST_INSTALL_ACTION= \
	( $(MV) $(PROTOUSRDIR)/include/mad.h $(PROTOUSRDIR)/include/mad-$(BITS).h && \
	  $(GSED) -e "s:%LIBDIR%:$(CONFIGURE_LIBDIR.$(BITS)):g" \
		-e "s:%VERSION%:$(COMPONENT_VERSION):g" \
		< $(COMPONENT_DIR)/files/mad.pc > $(BUILD_DIR)/mad.pc.$(BITS) )

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

REQUIRED_PACKAGES += system/library
