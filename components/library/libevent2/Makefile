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
# Copyright 2021 Gary Mills
# Copyright 2014 Alexander Pyhalov
#

BUILD_BITS=		32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libevent2
COMPONENT_VERSION=	2.0.22
COMPONENT_REVISION=	4
COMPONENT_PROJECT_URL=	http://libevent.org/
COMPONENT_SUMMARY=	An event notification library for event-driven network servers
COMPONENT_FMRI=         library/libevent2
COMPONENT_CLASSIFICATION=       System/Libraries
COMPONENT_SRC=		libevent-$(COMPONENT_VERSION)-stable
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:71c2c49f0adadacfdbe6332a372c38cf9c8b7895bb73dabeaa53cdcc1d4e1fa3
COMPONENT_ARCHIVE_URL=\
https://github.com/libevent/libevent/releases/download/release-$(COMPONENT_VERSION)-stable/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	LICENSE

PYTHON_VERSION=		3.9

include $(WS_MAKE_RULES)/common.mk

# Replace the python script with a python3 version
COMPONENT_PREP_ACTION= \
	( $(CP) $(COMPONENT_DIR)/files/event_rpcgen.py $(@D) )

CONFIGURE_OPTIONS+=	--disable-static
CONFIGURE_OPTIONS+=	--includedir=/usr/include/libevent2

# Setup event-config.h file to support 32 & 64 bit.
#
COMPONENT_POST_INSTALL_ACTION= \
            ($(MV) $(PROTO_DIR)/usr/include/libevent2/event2/event-config.h $(PROTO_DIR)/usr/include/libevent2/event2/event-config-$(BITS).h )

# Typical results from the test target
#EVPORT
#...
#EPOLL
#...
#EPOLL (changelist)
#...
#DEVPOLL
#...
#POLL
#...
#SELECT
#...
#  FAIL .../libevent-2.0.22-stable/test/regress_util.c:972: assert(a)
#  [getaddrinfo FAILED]
#1/180 TESTS FAILED. (0 skipped)
#....
#==================
#1 of 1 test failed
#==================

# util/getaddrinfo fails (https://github.com/libevent/libevent/issues/134)

REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += runtime/python-39
REQUIRED_PACKAGES += system/library
