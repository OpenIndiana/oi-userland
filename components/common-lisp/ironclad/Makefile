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

COMPONENT_NAME=		ironclad
COMPONENT_VERSION=	0.32.1
COMPONENT_PROJECT_URL=	http://method-combination.net/lisp/ironclad/
COMPONENT_FMRI=		library/common-lisp/ironclad
COMPONENT_SRC=		$(COMPONENT_NAME)_$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:980be839491e773b96ac51d36b5fa8bb67ea0528f55554c51a6dcbef8a009e18
COMPONENT_ARCHIVE_URL=	http://www.method-combination.net/lisp/files/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	MIT-like
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license
COMPONENT_SUMMARY=	Ironclad is a cryptography library written entirely in Common Lisp

include ../../../make-rules/prep.mk
include ../../../make-rules/common-lisp.mk
include ../../../make-rules/ips.mk

build:		$(BUILD_32)

install:	$(INSTALL_32)
