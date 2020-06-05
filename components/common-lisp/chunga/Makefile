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
# Copyright 2015 Josef 'Jeff' Sipek <jeffpc@josefsipek.net>
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		chunga
COMPONENT_VERSION=	1.1.6
COMPONENT_PROJECT_URL=	http://weitz.de/chunga
COMPONENT_FMRI=		library/common-lisp/chunga
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:4edbba3132b8fc0785ffb8f7bd60db0c648b99e8cf44e927b4c3c350f3dc6639
COMPONENT_ARCHIVE_URL=	http://weitz.de/files/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	BSD-style
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license
COMPONENT_SUMMARY=	Portable chunked streams for Common Lisp

include ../../../make-rules/prep.mk
include ../../../make-rules/common-lisp.mk
include ../../../make-rules/ips.mk

build:		$(BUILD_32)

install:	$(INSTALL_32)
