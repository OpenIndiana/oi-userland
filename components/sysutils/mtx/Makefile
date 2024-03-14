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
# Copyright 2024 Carsten Grzemba
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mtx
COMPONENT_VERSION=	1.3.12
COMPONENT_FMRI=		media/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://sourceforge.net/projects/mtx
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=  https://downloads.sourceforge.net/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:0261c5e90b98b6138cd23dadecbc7bc6e2830235145ed2740290e1f35672d843
COMPONENT_LICENSE=		GPLv2
COMPONENT_LICENSE_FILE= LICENSE
COMPONENT_SUMMARY=	Media Changer Tools

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
