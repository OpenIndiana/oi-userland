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
COMPONENT_VERSION=	2.1.2
COMPONENT_SUMMARY=	CL-PPCRE is a portable regular expression library for Common Lisp
COMPONENT_PROJECT_URL=	https://edicl.github.io/cl-ppcre/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:2ddd99706fa2b442d3eb12ea36bb25f57613fc82e5eb91c4fcaec3b7ce4cfe85
COMPONENT_ARCHIVE_URL=	https://github.com/edicl/cl-ppcre/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=		library/common-lisp/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=Development/Other Languages
COMPONENT_LICENSE=	BSD-style
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/common-lisp.mk
include $(WS_MAKE_RULES)/ips.mk

build:		$(BUILD_64)

install:	$(INSTALL_64)

# Auto-generated dependencies
