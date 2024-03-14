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
# Copyright 2023 Niklas Poslovski
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libmad
COMPONENT_VERSION=      0.15.1.2
HUMAN_VERSION=          0.15.1b
COMPONENT_REVISION=     3
COMPONENT_SUMMARY=      A high-quality MPEG Audio Decoder
COMPONENT_SRC=          $(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:27afcbde70b6539471c0c83cd71f425361763e077987621086337cdbebcd8815
COMPONENT_ARCHIVE_URL=  \
	https://sourceforge.net/projects/mad/files/libmad/$(HUMAN_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  https://www.underbit.com/products/mad/
COMPONENT_LICENSE=      GPLv2
COMPONENT_LICENSE_FILE= COPYING
COMPONENT_CLASSIFICATION=System/Multimedia Libraries
COMPONENT_FMRI=         library/audio/libmad

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS  += --sysconfdir=/etc
CONFIGURE_OPTIONS  += --enable-accuracy
CONFIGURE_OPTIONS  += --enable-shared
CONFIGURE_OPTIONS  += --disable-static
CONFIGURE_OPTIONS  += --enable-fpm=64bit
CONFIGURE_OPTIONS  += --enable-sso
CONFIGURE_OPTIONS  += --enable-strict-iso
# disable architecture-specific optimizations
CONFIGURE_OPTIONS  += --disable-aso

COMPONENT_POST_INSTALL_ACTION= \
	( $(GSED) -e "s:%LIBDIR%:$(CONFIGURE_LIBDIR.$(BITS)):g" \
		-e "s:%VERSION%:$(COMPONENT_VERSION):g" \
		< $(COMPONENT_DIR)/files/mad.pc > $(BUILD_DIR)/mad.pc.$(BITS) )

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
