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
# Copyright 2011, Andrzej Szeszo
# Copyright 2019, Nona Hansel
#
# Note: Depends on xz for build

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pkgbuild
COMPONENT_VERSION=	1.3.105
COMPONENT_REVISION=	3
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	sha256:ed32d913af249d4221c2b94450eb4e996747024260c210620e94ac8130bc0fd6
COMPONENT_ARCHIVE_URL=	http://downloads.sourceforge.net/project/$(COMPONENT_NAME)/$(COMPONENT_NAME)/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION += \
    (cd $(@D); aclocal-1.10 -I m4; automake-1.10 --add-missing; autoconf)

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

# Build Dependencies
REQUIRED_PACKAGES += developer/build/automake-110

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/library
