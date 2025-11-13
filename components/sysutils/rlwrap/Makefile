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
# Copyright 2024 Andreas Wacknitz
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		rlwrap
COMPONENT_VERSION=	0.48
COMPONENT_SUMMARY=	rlwrap is a small utility that uses the GNU Readline library to allow the editing of keyboard input for any command
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:b2721b1c0147aaafc98e6a31d875316ba032ad336bec7f2a8bc538f9e3c6db60
COMPONENT_PROJECT_URL=	https://github.com/hanslub42/rlwrap
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI= 		utility/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE=		GPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = ( cd $(@D) ; autoreconf -fiv )

COMPONENT_PRE_CONFIGURE_ACTION += ( $(CLONEY) $(SOURCE_DIR) $(@D); )

# Replace "#!/usr/bin/env ..." shebang line with properly versioned one
COMPONENT_POST_INSTALL_ACTION += \
	$(GSED) -i -e 's:env python3:python$(PYTHON_VERSION):' $(PROTOUSRSHAREDIR)/rlwrap/filters/*.py ;

CFLAGS += $(CPP_LARGEFILES)
CFLAGS += $(XPG6MODE)

# We don't have libptytty yet
CONFIGURE_OPTIONS += --without-libptytty
CONFIGURE_OPTIONS += --disable-dependency-tracking

# Auto-generated dependencies
REQUIRED_PACKAGES += $(READLINE_PKG)
REQUIRED_PACKAGES += system/library
