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
# Copyright 2015 Aurelien Larcher
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           xmakemap
COMPONENT_VERSION=        7.5
COMPONENT_FMRI=           x11/xmakemap
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_SUMMARY=  xmakemap - script to generate xmodmap files
COMPONENT_SRC=      src
COMPONENT_PROJECT_URL = https://hg.java.net/hg/solaris-x11~x-s12-clone
COMPONENT_LICENSE=      Oracle
COMPONENT_LICENSE_FILE= xmakemap.license

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

build:

install:
	mkdir -p $(PROTOUSRBINDIR) $(PROTOUSRSHAREMAN1DIR)
	$(INSTALL) -m 0555 $(SOURCE_DIR)/xmakemap $(PROTOUSRBINDIR)
	$(INSTALL) -m 0444 $(SOURCE_DIR)/xmakemap.man $(PROTOUSRSHAREMAN1DIR)/xmakemap.1

test: $(NO_TESTS)


REQUIRED_PACKAGES += SUNWcs
