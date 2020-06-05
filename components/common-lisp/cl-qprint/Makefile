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

COMPONENT_NAME=		cl-qprint
COMPONENT_VERSION=	0.2.1
COMPONENT_PROJECT_URL=	http://www.bobturf.org/software/cl-qprint/
COMPONENT_FMRI=		library/common-lisp/cl-qprint
COMPONENT_SRC=		$(COMPONENT_NAME)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:ce2a26c152c6b7db4e097deb3a0ac5c0439e2acf5b4b02402e1ed5e876873fc7
COMPONENT_ARCHIVE_URL=	http://www.bobturf.org/software/cl-qprint/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	LGPL2.1
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license
COMPONENT_SUMMARY=	quoted-printable encoder/decoder

include ../../../make-rules/prep.mk
include ../../../make-rules/common-lisp.mk
include ../../../make-rules/ips.mk

build:		$(BUILD_32)

install:	$(INSTALL_32)
