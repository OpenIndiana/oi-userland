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
# Copyright 2011 Josef 'Jeff' Sipek <jeffpc@josefsipek.net>
# Copyright 2017 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		guilt
COMPONENT_VERSION=	0.36
COMPONENT_SUMMARY=	quilt for git; similar to Mercurial queues
COMPONENT_PROJECT_URL=	http://repo.or.cz/w/guilt.git
COMPONENT_FMRI=		developer/versioning/guilt
COMPONENT_CLASSIFICATION=	Development/Source Code Management
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:34fba8e0ac59fb9729170c91e06a90a228a7d9110b13c9b06f6a6ed417aa2711
COMPONENT_ARCHIVE_URL=	http://guilt.31bits.net/src/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	GPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_BUILD_TARGETS = all doc

COMPONENT_INSTALL_TARGETS = install install-doc

COMPONENT_INSTALL_ENV += INSTALL=$(INSTALL)

COMPONENT_TEST_TARGETS = test

# Tests suppose GNU tools
COMPONENT_TEST_ENV += PATH="$(PATH.gnu)"

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

# Build dependencies
REQUIRED_PACKAGES += text/asciidoc
REQUIRED_PACKAGES += text/xmlto

# Auto-generated dependencies
REQUIRED_PACKAGES += developer/versioning/git
REQUIRED_PACKAGES += file/gnu-coreutils
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += text/gawk
REQUIRED_PACKAGES += text/gnu-grep
