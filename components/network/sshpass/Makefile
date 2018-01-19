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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=sshpass
COMPONENT_VERSION=1.06
COMPONENT_SUMMARY=Non-interactive ssh password auth
COMPONENT_PROJECT_URL=https://sourceforge.net/projects/sshpass
COMPONENT_FMRI=network/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=System/Administration and Configuration
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=  https://sourceforge.net/projects/sshpass/files/sshpass/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:c6324fcee608b99a58f9870157dfa754837f8c48be3df0f5e2f3accf145dee60
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
