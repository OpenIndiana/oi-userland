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
# Copyright (c) 2014 Alexander Pyhalov.  All rights reserved.
#

include ../../../make-rules/shared-macros.mk

PATH=/usr/bin:/usr/gnu/bin:/usr/sbin

COMPONENT_NAME=		pyzmq
COMPONENT_VERSION=	14.0.1
COMPONENT_PROJECT_URL=	https://github.com/zeromq/pyzmq
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:07c7f63aaa7709438345a5e5f4d90fe7decb147ff72d244acf4fa56f8801e5e0
COMPONENT_ARCHIVE_URL=	https://pypi.python.org/packages/source/p/pyzmq/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

LDFLAGS.32  +=  -L/usr/g++/lib -R/usr/g++/lib
LDFLAGS.64  +=  -L/usr/g++/lib/$(MACH64) -R/usr/g++/lib/$(MACH64)

PKG_CONFIG_PATH.32   = /usr/g++/lib/pkgconfig:/usr/lib/pkgconfig
PKG_CONFIG_PATH.64   = /usr/g++/lib/$(MACH64)/pkgconfig:/usr/lib/$(MACH64)/pkgconfig
LDFLAGS +=  $(LDFLAGS.$(BITS))


COMPONENT_ENV+= PKG_CONFIG_PATH="$(PKG_CONFIG_PATH.$(BITS))"
COMPONENT_ENV+= LDFLAGS="$(LDFLAGS)"

COMPONENT_BUILD_ENV+=$(COMPONENT_ENV)
COMPONENT_INSTALL_ENV+=$(COMPONENT_ENV)


# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:           $(TEST_32_and_64)
