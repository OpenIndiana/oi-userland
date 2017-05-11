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
# Copyright (c) 2016 Aurelien Larcher
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libvdpau
COMPONENT_VERSION=	1.1.1
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	VDPAU libaries and headers
COMPONENT_PROJECT_URL=	http://freedesktop.org/wiki/Software/VDPAU/
COMPONENT_FMRI=		library/graphics/libvdpau
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:857a01932609225b9a3a5bf222b85e39b55c08787d0ad427dbd9ec033d58d736
COMPONENT_ARCHIVE_URL= \
    http://people.freedesktop.org/~aplattner/vdpau/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	MIT

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CONFIGURE_OPTIONS+= --sysconfdir=$(ETCDIR)

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += developer/documentation-tool/doxygen
REQUIRED_PACKAGES += image/graphviz
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/header/dri2proto
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
