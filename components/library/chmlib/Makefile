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
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= chmlib
COMPONENT_VERSION= 0.40
COMPONENT_REVISION= 2
COMPONENT_SUMMARY= A library for reading Microsoft .CHM files
COMPONENT_PROJECT_URL = https://www.jedrea.com/chmlib/
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:512148ed1ca86dea051ebcf62e6debbb00edfdd9720cde28f6ed98071d3a9617
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI= library/desktop/chmlib
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Libraries
COMPONENT_LICENSE= LGPLv2.1

include $(WS_MAKE_RULES)/common.mk

# Missing files in build dir for configure without this.
# COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS+= --disable-static

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
