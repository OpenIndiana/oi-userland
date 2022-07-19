#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016 EveryCity Ltd. All rights reserved.
#

BUILD_STYLE=configure
BUILD_BITS=32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libpcap
COMPONENT_FMRI=         library/libpcap
COMPONENT_VERSION=      1.8.1
COMPONENT_REVISION=     1
COMPONENT_LICENSE=      BSD
COMPONENT_PROJECT_URL=  http://www.tcpdump.org/
COMPONENT_SUMMARY=      Packet Capture Library
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:673dbc69fdc3f5a86fb5759ab19899039a8e5e6c631749e48dcd9c6f0c83541e
COMPONENT_ARCHIVE_URL=  http://www.tcpdump.org/release/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION+=	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS  +=  --disable-dbus

CONFIGURE_ENV+=		ac_cv_func_getifaddrs=no

LDFLAGS+=	-lnsl -lsocket

# Build dependencies
REQUIRED_PACKAGES += driver/network/bpf
# Auto-generated dependencies
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
