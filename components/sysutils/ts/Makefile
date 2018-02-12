#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2014 Josef 'Jeff' Sipek <jeffpc@josefsipek.net>
#

PREFERRED_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ts
COMPONENT_VERSION=	1.0
COMPONENT_SUMMARY=	task spooler - a Unix batch system
COMPONENT_PROJECT_URL= http://vicerveza.homeunix.net/~viric/soft/ts/
COMPONENT_FMRI=		utility/ts
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
  sha256:4f53e34fff0bb24caaa44cdf7598fd02f3e5fa7cacaea43fa0d081d03ffbb395
COMPONENT_ARCHIVE_URL= \
  http://vicerveza.homeunix.net/~viric/soft/ts/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2+

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_BUILD_ENV  = CC=$(CC)
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS) -pedantic -ansi -Wall"
COMPONENT_BUILD_ENV += LDFLAGS="$(CC_BITS) -lsocket -lnsl"
COMPONENT_INSTALL_ARGS=PREFIX=$(PROTO_DIR)/usr

COMPONENT_TEST_CMD= ./testbench.sh
COMPONENT_TEST_TARGETS=

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:	$(TEST_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
