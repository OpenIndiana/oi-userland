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
# Copyright (c) 2016 Sergey Avseyev
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		claws-mail
COMPONENT_VERSION=	3.13.2
COMPONENT_PROJECT_URL=	http://www.claws-mail.org
COMPONENT_FMRI=		mail/claws-mail
COMPONENT_SUMMARY=	The user-friendly, lightweight, and fast email client
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:6a731052814b3284abeca1662d47817a86e018bc7123ab428f015f0cfab40ad1
COMPONENT_ARCHIVE_URL=	http://www.claws-mail.org/releases/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPL-3
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS += --disable-ldap
CONFIGURE_OPTIONS += --disable-perl-plugin
CONFIGURE_OPTIONS += --disable-rssyl-plugin
CONFIGURE_ENV.64 += PATH=/usr/bin/$(MACH64):/usr/bin

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk
