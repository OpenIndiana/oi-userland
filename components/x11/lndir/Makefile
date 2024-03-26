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
# Copyright 2016 Alexander Pyhalov
#

X11_CATEGORY=APP
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME= lndir
COMPONENT_VERSION= 1.0.5
COMPONENT_SUMMARY= lndir - create a shadow directory of symbolic links to another directory tree
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:3b65577a5575cce095664f5492164a96941800fe6290a123731d47f3e7104ddb
COMPONENT_ARCHIVE_URL= https://www.x.org/releases/individual/util/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI= file/lndir
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

# Build dependencies
REQUIRED_PACKAGES += x11/header/x11-protocols

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
