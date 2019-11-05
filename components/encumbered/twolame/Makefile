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

COMPONENT_NAME= twolame
COMPONENT_VERSION= 0.3.13
COMPONENT_SUMMARY= twolame MP3 Encoder
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:98f332f48951f47f23f70fd0379463aff7d7fb26f07e1e24e42ddef22cc6112a
COMPONENT_ARCHIVE_URL= \
  http://tenet.dl.sourceforge.net/project/twolame/twolame/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.twolame.org/
COMPONENT_LICENSE = LGPLv2.1
COMPONENT_LICENSE_FILE = COPYING
COMPONENT_CLASSIFICATION = System/Multimedia Libraries
COMPONENT_FMRI = audio/twolame

include $(WS_TOP)/make-rules/encumbered.mk
include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libsndfile
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
