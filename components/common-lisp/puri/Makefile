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

COMPONENT_NAME=		puri
COMPONENT_VERSION=	1.5.5
COMPONENT_PROJECT_URL=	http://puri.b9.com/
COMPONENT_FMRI=		library/common-lisp/puri
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:25bd8fbd6daa8e324a7f5f870926c0a4e34efee50a960763f4b6af0dcd51e52c
COMPONENT_ARCHIVE_URL=	http://files.kpe.io/puri/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	LLGPL
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license
COMPONENT_SUMMARY=	Puri provides a Common Lisp library for manipulating Universal Resource Identifiers

include ../../../make-rules/prep.mk
include ../../../make-rules/common-lisp.mk
include ../../../make-rules/ips.mk

build:		$(BUILD_32)

install:	$(INSTALL_32)
