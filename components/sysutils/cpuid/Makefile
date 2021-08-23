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
# Copyright 2020 Nona Hansel
#

BUILD_BITS=	64
BUILD_STYLE=	justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		cpuid
COMPONENT_VERSION=	1.8.0
COMPONENT_SUMMARY=	A simple CPUID decoder/dumper for x86/x86_64
COMPONENT_PROJECT_URL=	https://github.com/tycho/cpuid
COMPONENT_FMRI=		diagnostic/cpuid
COMPONENT_CLASSIFICATION=System/Hardware
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL= https://github.com/tycho/cpuid/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:3c2899033477cd27a7e507481d6af0c64be5c65cd958118c16dda5fe3025dee8
COMPONENT_LICENSE=	MIT

TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_BUILD_ARGS +=		CC="$(CC) $(CC_BITS) "
COMPONENT_BUILD_ARGS +=		prefix=$(USRDIR)

COMPONENT_INSTALL_ARGS +=	CC="$(CC) $(CC_BITS) "
COMPONENT_INSTALL_ARGS +=	prefix=$(USRDIR)

COMPONENT_POST_INSTALL_ACTION = $(INSTALL) -D files/cpuid.1 $(PROTOUSRDIR)/share/man/man1/cpuid.1

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
