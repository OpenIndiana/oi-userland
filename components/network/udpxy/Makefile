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
COMPONENT_REVISION= 9
IPS_COMPONENT_VERSION= $(COMPONENT_VERSION).$(COMPONENT_REVISION) 
COMPONENT_SUMMARY=udpxy is a UDP-to-HTTP multicast traffic relay daemon: it forwards UDP traffic from a given multicast subscription to the requesting HTTP client.
COMPONENT_PROJECT_URL=	http://www.udpxy.com/
COMPONENT_FMRI=	network/udpxy
COMPONENT_CLASSIFICATION=  Applications/Internet
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)-$(COMPONENT_REVISION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	http://www.udpxy.com/download/1_23/$(COMPONENT_NAME).$(COMPONENT_VERSION)-$(COMPONENT_REVISION)-prod.tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:6ce33b1d14a1aeab4bd2566aca112e41943df4d002a7678d9a715108e6b714bd
COMPONENT_LICENSE= GPLv3

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

CDEFS+= -DNO_SOCKADDR_SA_LEN
CDEFS+= -D_POSIX_PTHREAD_SEMANTICS

LDFLAGS+= -lsocket
LDFLAGS+= -lnsl

COMPONENT_BUILD_ENV+= CC=$(CC)
COMPONENT_BUILD_ENV+= LDFLAGS="$(LDFLAGS)"
COMPONENT_BUILD_ENV+= CDEFS="$(CDEFS)"
COMPONENT_INSTALL_ENV+= PREFIX=/usr

COMPONENT_BUILD_TARGETS= release

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)
