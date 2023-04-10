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
# Copyright 2022 Niklas Poslovski
#
BUILD_BITS = 64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libpcap
COMPONENT_VERSION=      1.10.4
COMPONENT_SUMMARY=      Packet Capture Library
COMPONENT_PROJECT_URL=  https://www.tcpdump.org
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)/release/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:ed19a0383fad72e3ad435fd239d7cd80d64916b87269550159d20e47160ebe5f
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_FMRI=         system/library/libpcap
COMPONENT_LICENSE=      BSD
COMPONENT_LICENSE_FILE=	LICENSE

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

DROP_STATIC_LIBRARIES= yes

COMPONENT_PRE_CONFIGURE_ACTION += ( $(CLONEY) $(SOURCE_DIR) $(@D) )

CONFIGURE_ENV += ac_cv_func_getifaddrs=no
CONFIGURE_OPTIONS += --disable-dbus
LDFLAGS += -lnsl -lsocket

# Build dependencies
REQUIRED_PACKAGES += driver/network/bpf

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
