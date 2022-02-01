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
COMPONENT_VERSION=	2.0.8
COMPONENT_PROJECT_URL=	https://edicl.github.io/drakma/
COMPONENT_FMRI=		library/common-lisp/drakma
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:5c0c1c4a0614deaa395968660636edbd9168064d0e6be66d6f93e594e78d0770
COMPONENT_ARCHIVE_URL=	https://github.com/edicl/drakma/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE=	BSD-style
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license
COMPONENT_SUMMARY=	Drakma is a full-featured HTTP client implemented in Common Lisp.
COMPONENT_CLASSIFICATION=Development/Other Languages

include ../../../make-rules/prep.mk
include ../../../make-rules/common-lisp.mk
include ../../../make-rules/ips.mk

build:		$(BUILD_32)

install:	$(INSTALL_32)
