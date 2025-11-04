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
# Copyright 2025 Bill Sommerfeld.  All rights reserved.
#

DROP_STATIC_LIBRARIES= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libdbi
COMPONENT_VERSION= 0.9.0
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= Database access library for C
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL= http://libdbi.sourceforge.net/
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:dafb6cdca524c628df832b6dd0bf8fabceb103248edb21762c02d3068fca4503

COMPONENT_ARCHIVE_URL= https://sourceforge.net/projects/libdbi/files/$(COMPONENT_NAME)/$(COMPONENT_NAME)-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_FMRI= library/libdbi
COMPONENT_LICENSE= LGPLv2.1
COMPONENT_LICENSE_FILE= COPYING

CONFIGURE_OPTIONS += --enable-docs=no

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
