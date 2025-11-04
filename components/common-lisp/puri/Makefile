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
COMPONENT_VERSION=	1.5.7.2
COMPONENT_SUMMARY=	Puri provides a Common Lisp library for manipulating Universal Resource Identifiers
COMPONENT_PROJECT_URL=	https://github.com/darabi/puri	
COMPONENT_SRC=		cl-$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:36821e005b289a002070e63e479c89d8c10401dcb7446275f11545214a4a82cf
COMPONENT_ARCHIVE_URL=	https://dlc.openindiana.org/oi-userland/source-archives/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/common-lisp/puri
COMPONENT_CLASSIFICATION=Development/Other Languages
COMPONENT_LICENSE=	LLGPL
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/common-lisp.mk
include $(WS_MAKE_RULES)/ips.mk

build:		$(BUILD_64)

install:	$(INSTALL_64)

# Auto-generated dependencies
