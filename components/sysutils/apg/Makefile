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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		apg
COMPONENT_VERSION=	2.3.0b
IPS_COMPONENT_VERSION=	2.3.0.2
COMPONENT_PROJECT_URL=	http://www.adel.nursat.kz/apg/
COMPONENT_SUMMARY=	APG (Automated Pasword Generator)
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:d1e52029709e2d7f9cb99bedce3e02ee7a63cff7b8e2b4c2bc55b3dc03c28b92
COMPONENT_ARCHIVE_URL=	http://www.adel.nursat.kz/apg/download/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		security/apg
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	BSD
COMPONENT_CLASSIFICATION=	Applications/System Utilities

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_POST_UNPACK_ACTION += ( find $(COMPONENT_SRC) -type d -exec chmod u+rwx \{\} \; )

COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)
