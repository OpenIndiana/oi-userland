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
# Copyright 2018 Aurelien Larcher
# Copyright 2018-2019 Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		cpuid
COMPONENT_VERSION=	1.7.2
COMPONENT_SUMMARY=	A simple CPUID decoder/dumper for x86/x86_64
COMPONENT_PROJECT_URL=	https://github.com/tycho/cpuid
COMPONENT_FMRI=		diagnostic/cpuid
COMPONENT_CLASSIFICATION=System/Hardware
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL= \
	https://github.com/tycho/cpuid/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:8120ffa5b0068810b44dfaf7f5e8a2a2002f2af23b5bfc9435912eac7e2049c0
COMPONENT_LICENSE=	MIT

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_BUILD_ARGS +=		CC="$(CC) $(CC_BITS) "
COMPONENT_BUILD_ARGS +=		prefix=$(USRDIR)

COMPONENT_INSTALL_ARGS +=	CC="$(CC) $(CC_BITS) "
COMPONENT_INSTALL_ARGS +=	prefix=$(USRDIR)

COMPONENT_POST_INSTALL_ACTION = $(INSTALL) -D files/cpuid.1 $(PROTOUSRDIR)/share/man/man1/cpuid.1

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
