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
# Copyright 2016 Jim Klimov
#

# See zeromq configure.ac for ABI version mapping to software version
# NOTE: This requires functionality offered by libzmq-4.1.2 (and hopefully
# subsequent releases) which we package in a dedicated subtree
NEEDED_ZEROMQ_VER = 4.1

# The zeromq components define this directory structure
ZEROMQ_DIR = $(USRDIR)/zeromq-$(NEEDED_ZEROMQ_VER)

# We define these before including any common structure makefiles
CXXFLAGS   = -I$(ZEROMQ_DIR)/include
CPPFLAGS   = -I$(ZEROMQ_DIR)/include
CFLAGS     = -I$(ZEROMQ_DIR)/include
LDFLAGS.32 = -L$(ZEROMQ_DIR)/lib
LDFLAGS.64 = -L$(ZEROMQ_DIR)/lib/$(MACH64)

# This should be after the CFLAGS and CXXFLAGS above, so the preferred
# versions of includes are looked at before the mediated-installed ones.
include ../../../make-rules/shared-macros.mk

PATH=/usr/bin:/usr/gnu/bin:/usr/sbin

COMPONENT_NAME=		pyzmq
COMPONENT_VERSION=	14.7.0
COMPONENT_PROJECT_URL=	https://github.com/zeromq/pyzmq
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:07c7f63aaa7709438345a5e5f4d90fe7decb147ff72d244acf4fa56f8801e5e0
COMPONENT_ARCHIVE_URL=	https://pypi.python.org/packages/source/p/pyzmq/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:	$(TEST_32_and_64)
