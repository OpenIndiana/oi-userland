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

COMPONENT_NAME= rtmpdump
COMPONENT_VERSION= 2.4
COMPONENT_SUMMARY= RTMPdump -- a toolkit for RTMP streams
COMPONENT_SRC= $(COMPONENT_NAME)
COMPONENT_ARCHIVE= $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:0be975011d116bbdf1befad2a984ac83d09b1061c86550326a7ec496d2f188fc
COMPONENT_ARCHIVE_URL= \
  http://rtmpdump.mplayerhq.hu/download/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://rtmpdump.mplayerhq.hu/
COMPONENT_LICENSE = GPLv2,LGPLv2
COMPONENT_LICENSE_FILE = rtmpdump.license
COMPONENT_CLASSIFICATION = Applications/Sound and Video
COMPONENT_FMRI = video/rtmpdump

COMPONENT_ENV += CC="$(CC)"
COMPONENT_ENV += XCFLAGS="$(CFLAGS)"
COMPONENT_ENV += XLDFLAGS="$(LDFLAGS)"
COMPONENT_ENV += XLIBS="-lnsl -lsocket"

COMPONENT_BUILD_ENV += $(COMPONENT_ENV)

COMPONENT_INSTALL_ENV.64 = ARCH=/$(MACH64)
COMPONENT_INSTALL_ENV += $(COMPONENT_ENV)

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

$(INSTALL_32): $(INSTALL_64)

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)
