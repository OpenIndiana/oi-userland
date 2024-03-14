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

BUILD_BITS= 64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= twolame
COMPONENT_VERSION= 0.4.0
COMPONENT_SUMMARY= Optimised MPEG Audio Layer 2 (MP2) encoder
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:cc35424f6019a88c6f52570b63e1baf50f62963a3eac52a03a800bb070d7c87d
COMPONENT_ARCHIVE_URL= \
  http://tenet.dl.sourceforge.net/project/twolame/twolame/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.twolame.org/
COMPONENT_LICENSE = LGPL-2.1-only
COMPONENT_LICENSE_FILE = COPYING
COMPONENT_CLASSIFICATION = System/Multimedia Libraries
COMPONENT_FMRI = audio/twolame

USE_DEFAULT_TEST_TRANSFORMS = yes

include $(WS_TOP)/make-rules/common.mk

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static

# Drop 32-bit binaries
COMPONENT_POST_INSTALL_ACTION += $(RM) -r $(PROTOUSRBINDIR32) ;
# Install html documentation
COMPONENT_POST_INSTALL_ACTION += $(INSTALL) -d $(PROTOUSRSHAREDOCDIR)/twolame/html ;
COMPONENT_POST_INSTALL_ACTION += $(INSTALL) $(SOURCE_DIR)/doc/html/* $(PROTOUSRSHAREDOCDIR)/twolame/html ;
COMPONENT_POST_INSTALL_ACTION += $(RM) $(PROTOUSRSHAREDOCDIR)/twolame/html/{Doxyfile,Makefile}.* ;

# We need to run tests in clean environment
COMPONENT_TEST_ENV_CMD = $(ENV) -

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libsndfile
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
