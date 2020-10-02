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

COMPONENT_NAME=		cl-ppcre
COMPONENT_VERSION=	2.0.11
COMPONENT_PROJECT_URL=	http://weitz.de/cl-ppcre/
COMPONENT_FMRI=		library/common-lisp/cl-ppcre
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:626d4e1f78659d0b6e4d675c94e39afb1f602427724c961b1e4f029b348f4cb6
COMPONENT_ARCHIVE_URL=	http://weitz.de/files/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	BSD-style
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license
COMPONENT_SUMMARY=	CL-PPCRE is a portable regular expression library for Common Lisp

include ../../../make-rules/prep.mk
include ../../../make-rules/common-lisp.mk
include ../../../make-rules/ips.mk

build:		$(BUILD_32)

install:	$(INSTALL_32)
