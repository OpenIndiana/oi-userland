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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         pkgbuild
COMPONENT_VERSION=      1.3.105
COMPONENT_REVISION=	5
COMPONENT_SUMMARY=	pkgbuild - rpmbuild-like tool for building packages
COMPONENT_PROJECT_URL=	https://sourceforge.net/projects/pkgbuild/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:ed32d913af249d4221c2b94450eb4e996747024260c210620e94ac8130bc0fd6
COMPONENT_ARCHIVE_URL=  https://downloads.sourceforge.net/project/$(COMPONENT_NAME)/$(COMPONENT_NAME)/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		package/pkgbuild
COMPONENT_CLASSIFICATION=System/Packaging
COMPONENT_LICENSE=	GPL-2.0-only
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION += \
    (cd $(@D); aclocal -I m4; automake --add-missing; autoconf)

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/library
