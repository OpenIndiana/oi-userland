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
# Copyright 2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

PATH=/usr/bin:/usr/gnu/bin:/usr/sbin

COMPONENT_NAME=		netifaces
COMPONENT_VERSION=	0.10.4
COMPONENT_PROJECT_URL=	https://pypi.python.org/pypi/netifaces
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:9656a169cb83da34d732b0eb72b39373d48774aee009a3d1272b7ea2ce109cde
COMPONENT_ARCHIVE_URL=	https://pypi.python.org/packages/source/n/netifaces/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:           $(NO_TEST)

include $(WS_TOP)/make-rules/depend.mk
