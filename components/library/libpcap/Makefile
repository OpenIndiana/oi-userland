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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libpcap
COMPONENT_FMRI=         library/libpcap
COMPONENT_VERSION=      1.7.4
COMPONENT_LICENSE=      BSD
COMPONENT_PROJECT_URL=  http://www.tcpdump.org/
COMPONENT_SUMMARY=	Packet Capture Library
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:7ad3112187e88328b85e46dce7a9b949632af18ee74d97ffc3f2b41fe7f448b0
COMPONENT_ARCHIVE_URL=	http://www.tcpdump.org/release/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION+=	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS  +=  --disable-dbus

CONFIGURE_ENV+=		ac_cv_func_getifaddrs=no

LDFLAGS+=	-lnsl -lsocket

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

