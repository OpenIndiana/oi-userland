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
# Copyright 2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		fio
COMPONENT_VERSION=	2.15
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	Flexible I/O tester
COMPONENT_FMRI=		system/test/fio
COMPONENT_CLASSIFICATION=	Development/System
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:bcc4407d3f8d0b02964a738b11719e6daa45461fd830ac6d0a7909ea25da4156
COMPONENT_PROJECT_URL=	http://freecode.com/projects/fio
COMPONENT_ARCHIVE_URL=	\
	https://github.com/axboe/fio/archive/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	GPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS = --prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --cc="$(CC)"
CONFIGURE_OPTIONS += --extra-cflags="$(CFLAGS)"

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
