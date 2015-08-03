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
# Copyright 2011, Andrzej Szeszo
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		rxvt-unicode
COMPONENT_VERSION=	9.21
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	sha256:75270ed72bc5895a64a1d7392bf45a622204192371c3965bd3dd978dc088956b
COMPONENT_ARCHIVE_URL=	http://dist.schmorp.de/rxvt-unicode/Attic/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://software.schmorp.de/pkg/rxvt-unicode.html

COMPONENT_ARCHIVE_1=	tabbedex
COMPONENT_ARCHIVE_URL_1=	https://raw.github.com/stepb/urxvt-tabbedex/master/tabbedex

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PKG_PROTO_DIRS += $(USERLAND_ARCHIVES)

CPPFLAGS += -DLASTLOG_FILE='\"/var/adm/lastlog\"'

CONFIGURE_OPTIONS += CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_OPTIONS += PERL="$(PERL)"
CONFIGURE_OPTIONS += --enable-256-color
CONFIGURE_OPTIONS += --enable-everything

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)
