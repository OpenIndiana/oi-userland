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
# Copyright 2025 Marcel Telka
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		parted
COMPONENT_VERSION =		1.8.8
# We already do have parted 1.8.8 packaged with ips version 1.8.8.1
IPS_COMPONENT_VERSION =		1.8.8.1
COMPONENT_SUMMARY =		GNU Parted is a program for creating and manipulating partition tables
COMPONENT_PROJECT_URL =		http://www.gnu.org/software/parted/
COMPONENT_FMRI =		system/storage/parted
COMPONENT_CLASSIFICATION =	System/Administration and Configuration
COMPONENT_SRC =			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_URL =		https://ftp.gnu.org/gnu/parted/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH =	sha256:dfcd811a9cc7753d6f310a34301716a7e18a45b905fa8c7eb77d5f121bc3c5ea
COMPONENT_LICENSE =		GPL-3.0-only
COMPONENT_LICENSE_FILE =	COPYING

# Tests are run for the label tool only, but we do not ship it
TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# We do not need static libs
CONFIGURE_OPTIONS += --disable-static

# libdiskmgt is needed for full illumos support
LDFLAGS += -ldiskmgt

# We do not want the charset.alias file
COMPONENT_POST_INSTALL_ACTION += $(RM) $(PROTOUSRLIBDIR.$(BITS))/charset.alias ;
# We do not want the info index file
COMPONENT_POST_INSTALL_ACTION += $(RM) $(PROTOUSRSHAREDIR)/info/dir ;
# We do not need the label tool
COMPONENT_POST_INSTALL_ACTION += $(RM) $(PROTOUSRBINDIR)/label ;
# We do not need the partprobe tool
COMPONENT_POST_INSTALL_ACTION += $(RM) $(PROTOUSRSBINDIR)/partprobe ;
COMPONENT_POST_INSTALL_ACTION += $(RM) $(PROTOUSRSHAREMAN8DIR)/partprobe.8 ;

# Manually added build dependencies
REQUIRED_PACKAGES += system/library/libdiskmgt/header-libdiskmgt

# Auto-generated dependencies
REQUIRED_PACKAGES += $(READLINE_PKG)
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdiskmgt
