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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libmad
COMPONENT_VERSION= 0.15.1b
IPS_COMPONENT_VERSION= 0.15.1.2
COMPONENT_SUMMARY= A high-quality MPEG audio decoder
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:27afcbde70b6539471c0c83cd71f425361763e077987621086337cdbebcd8815
COMPONENT_ARCHIVE_URL= \
  http://sourceforge.net/projects/mad/files/libmad/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.underbit.com/products/mad/
COMPONENT_LICENSE = GPLv2
COMPONENT_LICENSE_FILE = COPYING
COMPONENT_CLASSIFICATION = System/Multimedia Libraries
COMPONENT_FMRI = library/audio/libmad

include $(WS_TOP)/make-rules/encumbered.mk
include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

CONFIGURE_OPTIONS.32 += --enable-fpm=default
CONFIGURE_OPTIONS.64 += --enable-fpm=64bit

CONFIGURE_OPTIONS += --enable-accuracy
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static

# Setup mad.h file to support 32 & 64 bit.
#
COMPONENT_POST_INSTALL_ACTION= \
            ( $(MV) $(PROTOUSRDIR)/include/mad.h $(PROTOUSRDIR)/include/mad-$(BITS).h && \
		$(GSED) -e "s:%LIBDIR%:$(CONFIGURE_LIBDIR.$(BITS)):g" -e "s:%VERSION%:$(COMPONENT_VERSION):g" $(COMPONENT_DIR)/files/mad.pc > $(BUILD_DIR)/mad.pc.$(BITS) )

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)
