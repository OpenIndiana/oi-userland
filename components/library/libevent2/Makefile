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
# Copyright 2023 Niklas Poslovski
# Copyright 2025 Klaus Ziegler
#

BUILD_BITS= 32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libevent2
COMPONENT_VERSION=	2.1.13
COMPONENT_PROJECT_URL=	https://libevent.org/
COMPONENT_SUMMARY=	An event notification library for event-driven network servers
COMPONENT_SRC=		libevent-$(COMPONENT_VERSION)-stable
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:f7e9383b8c0baa81b687e5b5eecc01beefaf1b19b64151d95ed61647fe7a315c
COMPONENT_ARCHIVE_URL= https://github.com/libevent/libevent/releases/download/release-$(COMPONENT_VERSION)-stable/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=     library/libevent2
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	LICENSE

PYTHON_VERSION= 3.9

# Test results aren't stable, thus concentrate on 64 bit tests.
TEST_TARGET= $(TEST_64)
include $(WS_MAKE_RULES)/common.mk

# Replace the python script with a python3 version
COMPONENT_PREP_ACTION= ( $(CP) $(COMPONENT_DIR)/files/event_rpcgen.py $(@D) )

CONFIGURE_OPTIONS += --disable-static

# Setup event-config.h file to support 32 & 64 bit.
#
COMPONENT_POST_INSTALL_ACTION= \
	( $(MV) $(PROTO_DIR)/usr/include/event2/event-config.h $(PROTO_DIR)/usr/include/event2/event-config-$(BITS).h  )

TEST_LIBPATH.32 = $(PROTOUSRLIBDIR)
TEST_LIBPATH.64 = $(PROTOUSRLIBDIR64)
COMPONENT_TEST_ENV += LD_LIBRARY_PATH=$(TEST_LIBPATH.$(BITS))
COMPONENT_TEST_TARGETS = verify

COMPONENT_TEST_TRANSFORMS += \
    '-n ' \
    '-e "/Runnung tests/p" ' \
	'-e "/regress:/p" ' \
    '-e "/OKAY/p" ' \
    '-e "/FAIL/p" ' \
    '-e "/EPOLL/p" '

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

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += $(OPENSSL_PKG)/32
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.python += runtime/python
