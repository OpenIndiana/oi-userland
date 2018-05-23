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
# Copyright 2016 Adam Stevko 
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	udpxy
COMPONENT_VERSION= 1.0.23
COMPONENT_VERSION_REV= 10
COMPONENT_REVISION= 11
IPS_COMPONENT_VERSION= $(COMPONENT_VERSION).$(COMPONENT_VERSION_REV) 
COMPONENT_SUMMARY=udpxy is a UDP-to-HTTP multicast traffic relay daemon: it forwards UDP traffic from a given multicast subscription to the requesting HTTP client.
COMPONENT_PROJECT_URL=	http://www.udpxy.com/
COMPONENT_FMRI=	network/udpxy
COMPONENT_CLASSIFICATION=  Applications/Internet
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)-$(COMPONENT_VERSION_REV)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	http://www.udpxy.com/download/$(COMPONENT_NAME)/$(COMPONENT_NAME)-src.tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:187d5306136b9ed1bb59a7f2822bbcb1cc0a279090dba88a7a6bd78ab20a95a6
COMPONENT_LICENSE= GPLv3

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

CDEFS+= -DNO_SOCKADDR_SA_LEN
CDEFS+= -D_POSIX_PTHREAD_SEMANTICS

LDFLAGS+= -lsocket
LDFLAGS+= -lnsl

COMPONENT_BUILD_ENV+= CC=$(CC)
COMPONENT_BUILD_ENV+= CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV+= LDFLAGS="$(LDFLAGS)"
COMPONENT_BUILD_ENV+= CDEFS="$(CDEFS)"
COMPONENT_INSTALL_ENV+= PREFIX=/usr

COMPONENT_BUILD_TARGETS= release

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
