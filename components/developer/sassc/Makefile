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
# Copyright 2025 Marcel Telka
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			sassc
COMPONENT_VERSION=		3.6.2
COMPONENT_SUMMARY=		libsass command line driver
COMPONENT_PROJECT_URL=		https://github.com/sass/sassc/
COMPONENT_FMRI=			developer/sassc
COMPONENT_CLASSIFICATION=	Development/Other Languages
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=		https://github.com/sass/sassc/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=		sha256:92434b8b441bc2de65aa945654ae15f40516ab2d8d30b47308e5cf325789e160
COMPONENT_LICENSE=		MIT
COMPONENT_LICENSE_FILE=		LICENSE

TEST_TARGET=$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# We need to bootstrap the project
COMPONENT_PREP_ACTION += ( cd $(@D) && $(ENV) PATH="$(PATH)" autoreconf -fi ) ;

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libsass
REQUIRED_PACKAGES += system/library
