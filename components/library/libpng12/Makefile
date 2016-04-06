#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2015 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libpng
COMPONENT_VERSION=	1.2.56
COMPONENT_PROJECT_URL=	http://www.libpng.org/
COMPONENT_SUMMARY=	Portable Network Graphics library version $(COMPONENT_VERSION)
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:24ce54581468b937734a6ecc86f7e121bc46a90d76a0d948dca08f32ee000dbe
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/libpng/files/libpng12/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_LICENSE=	libpng
COMPONENT_LICENSE_FILE=	LICENSE
COMPONENT_CLASSIFICATION=	System/Multimedia Libraries
COMPONENT_FMRI= 	image/library/libpng12

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CONFIGURE_OPTIONS+=	--sysconfdir=/etc

# for tests to pass
ENV=/usr/bin/env -i

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)
