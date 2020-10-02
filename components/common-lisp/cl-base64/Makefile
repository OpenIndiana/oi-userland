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

COMPONENT_NAME=		cl-base64
COMPONENT_VERSION=	3.3.3
COMPONENT_PROJECT_URL=	http://www.cliki.net/cl-base64
COMPONENT_FMRI=		library/common-lisp/cl-base64
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:35c2f6b0a2562e8ecbc956e5899390fa244976d41e6b03bc4c13a3fe768c229f
COMPONENT_ARCHIVE_URL=	https://common-lisp.net/project/lispy/repository/distfiles/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	BSD-ish
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license
COMPONENT_SUMMARY=	cl-base64 provides base64 (RFC 1521) encoding and decoding.

include ../../../make-rules/prep.mk
include ../../../make-rules/common-lisp.mk
include ../../../make-rules/ips.mk

build:		$(BUILD_32)

install:	$(INSTALL_32)
