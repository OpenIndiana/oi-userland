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
# Copyright 2013 Alexander Pyhalov.  All rights reserved.
# Copyright 2020 Andreas Wacknitz

BUILD_BITS= 32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= mrtg
COMPONENT_VERSION= 2.17.7
COMPONENT_SUMMARY= mrtg - The Multi Router Traffic Grapher
COMPONENT_FMRI= diagnostic/mrtg
COMPONENT_CLASSIFICATION= Applications/Internet
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:9b94cb268fb15b0304ad3bb3ec92b9a8a16dacfcee72baac19298224a2c332c3
COMPONENT_ARCHIVE_URL= \
	https://oss.oetiker.ch/mrtg/pub/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://oss.oetiker.ch/mrtg/
COMPONENT_LICENSE= GPLv2

TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SCRIPT=       $(@D)/configure
CONFIGURE_OPTIONS+=	--with-gd-lib=/usr/lib
CONFIGURE_OPTIONS+=	--with-gd-inc=/usr/include/gd2

REQUIRED_PACKAGES += image/rrdtool

# Auto-generated dependencies
REQUIRED_PACKAGES += library/gd
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
