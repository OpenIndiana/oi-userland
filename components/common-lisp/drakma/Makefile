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

COMPONENT_NAME=		drakma
COMPONENT_VERSION=	2.0.2
COMPONENT_PROJECT_URL=	http://weitz.de/drakma/
COMPONENT_FMRI=		library/common-lisp/drakma
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:5f40ae3c8c8cabb834234a17c8f89dd8cc35cc104b89a8f86636b4ee5280fcae
COMPONENT_ARCHIVE_URL=	http://weitz.de/files/drakma.tar.gz
COMPONENT_LICENSE=	BSD-style
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license
COMPONENT_SUMMARY=	Drakma is a full-featured HTTP client implemented in Common Lisp.

include ../../../make-rules/prep.mk
include ../../../make-rules/common-lisp.mk
include ../../../make-rules/ips.mk

build:		$(BUILD_32)

install:	$(INSTALL_32)
