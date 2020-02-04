#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2020 Jim Klimov
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		enet
COMPONENT_VERSION=	1.3.14
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=		library/security/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://enet.bespin.org
# Development is on GitHub, but releases are not :(
#COMPONENT_PROJECT_URL=	https://github.com/lsalzman/enet
#COMPONENT_ARCHIVE_URL=	https://github.com/lsalzman/$(COMPONENT_NAME)/releases/download/$(COMPONENT_NAME)-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/download/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	\
	sha256:98f6f57aab0a424469619ed3047728f0d3901ce8f0dea919c11e7966d807e870
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE= LICENSE
COMPONENT_DESCRIPTION=	ENet's purpose is to provide a relatively thin, simple and robust network communication layer on top of UDP (User Datagram Protocol).The primary feature it provides is optional reliable, in-order delivery of packets. ENet omits certain higher level networking features such as authentication, lobbying, server discovery, encryption, or other similar tasks that are particularly application specific so that the library remains flexible, portable, and easily embeddable.
COMPONENT_SUMMARY=	ENet is a relatively thin, simple and robust network communication layer on top of UDP

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION = \
        (cd $(@D) &&\
        autoreconf -fiv &&\
        $(RM) config.h )

COMPONENT_PRE_CONFIGURE_ACTION = \
        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS += --disable-static

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

REQUIRED_PACKAGES += system/library
