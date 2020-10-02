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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		cl-json
COMPONENT_VERSION=	0.5.0
COMPONENT_GITREV=	v$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://common-lisp.net/project/trivial-gray-streams/
COMPONENT_FMRI=		library/common-lisp/cl-json
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_GITREV).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:4c23f41bd4d770df1086f78faca6777a882961cb422ff58f6896cbb41d719c97
COMPONENT_ARCHIVE_URL=	https://github.com/hankhero/cl-json/archive/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license
COMPONENT_SUMMARY=	CL-JSON provides an encoder of Lisp objects to JSON format and a corresponding decoder

include ../../../make-rules/prep.mk
include ../../../make-rules/common-lisp.mk
include ../../../make-rules/ips.mk

build:		$(BUILD_32)

install:	$(INSTALL_32)
