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
# Copyright 2019 Nona Hansel
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         rarian
COMPONENT_VERSION=	0.8.6
COMPONENT_SUMMARY=      Documentation meta-data library
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	sha256:2dcb9a421e084511d654aa8803807ddd56560747ac37ab2fe7d84270b94084ed
COMPONENT_ARCHIVE_URL=	https://gitlab.freedesktop.org/$(COMPONENT_NAME)/$(COMPONENT_NAME)/-/archive/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://rarian.freedesktop.org
COMPONENT_FMRI=			text/rarian
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_LICENSE=		LGPL-2.1-or-later AND GPL-2.0-or-later

include $(WS_MAKE_RULES)/common.mk

# helper target
update-license-file: patch
	( \
		$(CAT) $(SOURCE_DIR)/COPYING ; \
		printf '\n--- COPYING.LIB -----------------------------------------------------------\n\n' ; \
		$(CAT) $(SOURCE_DIR)/COPYING.LIB ; \
		printf '\n--- COPYING.UTILS ---------------------------------------------------------\n\n' ; \
		$(CAT) $(SOURCE_DIR)/COPYING.UTILS \
	) > $(COMPONENT_DIR)/$(COMPONENT_LICENSE_FILE)

# The configure file is not distributed
COMPONENT_PREP_ACTION= ( cd $(@D) && $(ENV) PATH="$(PATH)" NOCONFIGURE=1 ./autogen.sh )

CONFIGURE_OPTIONS += --disable-skdb-update
CONFIGURE_OPTIONS += --disable-static

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/tinyxml2
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
