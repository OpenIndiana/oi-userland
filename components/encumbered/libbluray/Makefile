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
# Copyright 2016 phorcys@126.com.  All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libbluray
COMPONENT_VERSION= 0.9.2
COMPONENT_FMRI = library/video/libbluray
COMPONENT_CLASSIFICATION = System/Multimedia Libraries
COMPONENT_SUMMARY= An open-source library designed for Blu-Ray Discs playback for media players.
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:efc994f42d2bce6af2ce69d05ba89dbbd88bcec7aca065de094fb3a7880ce7ea
COMPONENT_ARCHIVE_URL= \
  ftp://ftp.videolan.org/pub/videolan/libbluray/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.videolan.org/developers/libbluray.html
COMPONENT_LICENSE = LGPLv2.1

include $(WS_TOP)/make-rules/encumbered.mk
include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

COMMON_BUILD_ENV += JDK_HOME="$(JAVA_HOME)" 

CFLAGS += -I $(JAVA_HOME)/include/solaris

CONFIGURE_OPTIONS += --enable-udf
CONFIGURE_OPTIONS += --datadir=$(USRSHARELIBDIR)
CONFIGURE_OPTIONS += --with-libxml2
CONFIGURE_OPTIONS += --with-freetype

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
