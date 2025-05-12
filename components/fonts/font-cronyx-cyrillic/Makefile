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

BUILD_STYLE = configure
FONT_TYPE = X11

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		font-cronyx-cyrillic
COMPONENT_VERSION =		1.0.4
COMPONENT_SUMMARY =		Cyrillic bitmap fonts from X.Org Foundation
COMPONENT_ARCHIVE_EXTENSION =	.tar.xz
COMPONENT_ARCHIVE_HASH =	sha256:dc0781ce0dcbffdbf6aae1a00173a13403f92b0de925bca5a9e117e4e2d6b789
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	COPYING

include $(WS_MAKE_RULES)/font.mk

FONT_SUBDIR = cronyx-cyrillic

CONFIGURE_OPTIONS += --with-fontdir=$(USRSHAREX11FONTSDIR)/$(FONT_SUBDIR)

COMPONENT_POST_INSTALL_ACTION += \
	$(call create-symlinks,$(USRSHAREX11FONTSDIR)/$(FONT_SUBDIR),$(ETCDIR)/X11/fontpath.d) ; \
	$(MV) $(PROTOETCDIR)/X11/fontpath.d/$(FONT_SUBDIR) \
	      $(PROTOETCDIR)/X11/fontpath.d/$(FONT_SUBDIR):pri=75 ;

# Auto-generated dependencies
