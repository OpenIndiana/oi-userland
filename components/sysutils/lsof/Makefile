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
# Copyright 2017 Gary Mills
# Copyright 2016 Jim Klimov. All rights reserved.
# Copyright 2019 Michal Nowak
# Copyright 2020 Nona Hansel
#

BUILD_BITS=	64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		lsof
COMPONENT_VERSION=	4.94.0
COMPONENT_PROJECT_URL=	https://github.com/lsof-org/lsof
COMPONENT_SUMMARY=	LSOF - lister of opened files
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/lsof-org/lsof/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:a9865eeb581c3abaac7426962ddb112ecfd86a5ae93086eb4581ce100f8fa8f4

TEST_TARGET:	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION = (cp -a $(SOURCE_DIR)/* $(@D))

CONFIGURE_SCRIPT =	./Configure
CONFIGURE_OPTIONS =	-n solaris

# The p5m manifest directly pulls from source dirs (the "make install" action
# for Solaris in LSOF sources only prints hints what/how should be set up),
# therefore the "sample-manifest" target does not work.

# Including version to the man page
COMPONENT_POST_INSTALL_ACTION=	(cd $(@D) && soelim Lsof.8 > lsof.8)

# Necessary for soelim
REQUIRED_PACKAGES += text/doctools
# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
