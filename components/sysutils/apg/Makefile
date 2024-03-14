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
# Copyright 2015 Alexander Pyhalov
#

BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		apg
COMPONENT_VERSION=	2.3.0.2
HUMAN_VERSION=		2.3.0b
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	https://github.com/wilx/apg
COMPONENT_SUMMARY=	APG (Automated Pasword Generator)
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:89539aa734a47d68124fca5ba7acbe559edc5003b6791f5200ef9e706dd00fe9
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/archive/refs/tags/v$(HUMAN_VERSION).tar.gz
COMPONENT_FMRI=		security/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_POST_UNPACK_ACTION += ( find $(COMPONENT_SRC) -type d -exec chmod u+rwx \{\} \; )

COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

# Auto-generated dependencies
REQUIRED_PACKAGES += library/security/cracklib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
