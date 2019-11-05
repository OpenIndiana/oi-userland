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

COMPONENT_NAME= toolame
COMPONENT_VERSION= 02l
IPS_COMPONENT_VERSION=0.2.12
COMPONENT_SUMMARY= optimized MPEG Audio Layer 2 encoder
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH= \
  sha256:3b95cd2504bceac4aab2fca03bb3b5974d1d44b5afdd8eb4cc0f0899521bffc4
COMPONENT_ARCHIVE_URL= \
  http://tenet.dl.sourceforge.net/project/toolame/toolame%200.2/toolame%2002l/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://toolame.sourceforge.net/
COMPONENT_LICENSE = LGPLv2.1
COMPONENT_LICENSE_FILE = LGPL.txt
COMPONENT_CLASSIFICATION = System/Media
COMPONENT_FMRI = audio/toolame

COMPONENT_ENV += CC="$(CC)"
COMPONENT_ENV += CFLAGS="$(CFLAGS)"

COMPONENT_BUILD_ENV += $(COMPONENT_ENV)
COMPONENT_INSTALL_ENV += $(COMPONENT_ENV)

include $(WS_TOP)/make-rules/encumbered.mk
include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/justmake.mk
include $(WS_TOP)/make-rules/ips.mk

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
