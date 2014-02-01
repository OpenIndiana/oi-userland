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
# Copyright (c) 2014 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ccsm
COMPONENT_VERSION=	0.8.4
COMPONENT_PROJECT_URL=	http://www.compiz.org/
COMPONENT_SUMMARY=	ccsm settings manager for the CompizConfig system
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:46b9da032cf29e71aec0823799861d926937ad41f4edea3be718ac6a8532c16d
COMPONENT_ARCHIVE_URL=	http://releases.compiz.org/components/ccsm/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

# compizconfig-python is Python 2.6 only
PYTHON_VERSIONS = $(PYTHON_VERSION)

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_BUILD_ARGS += --prefix=/usr

COMPONENT_INSTALL_ARGS = --prefix=/usr
COMPONENT_INSTALL_ARGS +=       --root $(PROTO_DIR) 
COMPONENT_INSTALL_ARGS +=       --install-lib=$(PYTHON_LIB)
COMPONENT_INSTALL_ARGS +=       --install-purelib=$(PYTHON_LIB)
COMPONENT_INSTALL_ARGS +=       --install-platlib=$(PYTHON_LIB)
COMPONENT_INSTALL_ARGS +=       --force

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
