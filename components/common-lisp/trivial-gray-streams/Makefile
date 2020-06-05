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

COMPONENT_NAME=		trivial-gray-streams
COMPONENT_VERSION=	0.20140912
COMPONENT_GITREV=	0483ade330508b4b2edeabdb47d16ec9437ee1cb
COMPONENT_PROJECT_URL=	http://common-lisp.net/project/trivial-gray-streams/
COMPONENT_FMRI=		library/common-lisp/trivial-gray-streams
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_GITREV)
COMPONENT_ARCHIVE=	$(COMPONENT_GITREV).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:2c7990f1919203fb7285239908241ea3673a117ab248d10f6fee4c5380e89ed0
COMPONENT_ARCHIVE_URL=	https://github.com/trivial-gray-streams/trivial-gray-streams/archive/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license
COMPONENT_SUMMARY=	an extremely thin compatibility layer for gray streams

include ../../../make-rules/prep.mk
include ../../../make-rules/common-lisp.mk
include ../../../make-rules/ips.mk

build:		$(BUILD_32)

install:	$(INSTALL_32)
