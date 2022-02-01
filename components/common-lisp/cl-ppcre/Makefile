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
COMPONENT_VERSION=	2.1.1
COMPONENT_PROJECT_URL=	https://edicl.github.io/cl-ppcre/
COMPONENT_FMRI=		library/common-lisp/cl-ppcre
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:89631179b71648d9e6c565a928f6896a9d5742aa2083b9c1b705fe0b45d85def
COMPONENT_ARCHIVE_URL=	https://github.com/edicl/cl-ppcre/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE=	BSD-style
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license
COMPONENT_SUMMARY=	CL-PPCRE is a portable regular expression library for Common Lisp
COMPONENT_CLASSIFICATION=Development/Other Languages

include ../../../make-rules/prep.mk
include ../../../make-rules/common-lisp.mk
include ../../../make-rules/ips.mk

build:		$(BUILD_32)

install:	$(INSTALL_32)
