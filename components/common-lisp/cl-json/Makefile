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

BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		cl-json
COMPONENT_VERSION=	0.6.0
COMPONENT_GITREV=	v$(COMPONENT_VERSION)
COMPONENT_SUMMARY=	CL-JSON provides an encoder of Lisp objects to JSON format and a corresponding decoder
COMPONENT_PROJECT_URL=	https://cl-json.common-lisp.dev/cl-json.html
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:447f361d6527784b5e8dc11d7d2d99394df713d6e711afa2281397291d70224e
COMPONENT_ARCHIVE_URL=	https://github.com/sharplispers/cl-json/archive/refs/tags/$(COMPONENT_GITREV).tar.gz
COMPONENT_FMRI=		library/common-lisp/cl-json
COMPONENT_CLASSIFICATION= Development/Other Languages
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	LICENSE

include ../../../make-rules/common.mk
include ../../../make-rules/common-lisp.mk
include ../../../make-rules/ips.mk

build:		$(BUILD_32)

install:	$(INSTALL_32)

# Auto-generated dependencies
