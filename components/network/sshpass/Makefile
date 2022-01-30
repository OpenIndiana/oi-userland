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
# Copyright 2018 Till wegmueller
#
BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	sshpass
COMPONENT_VERSION=	1.09
IPS_COMPONENT_VERSION=1.0.9
COMPONENT_SUMMARY=	Non-interactive ssh password auth
COMPONENT_PROJECT_URL=	https://sourceforge.net/projects/sshpass
COMPONENT_FMRI=	network/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=System/Administration and Configuration
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=  https://sourceforge.net/projects/sshpass/files/sshpass/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:71746e5e057ffe9b00b44ac40453bf47091930cba96bbea8dc48717dedc49fb7
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
