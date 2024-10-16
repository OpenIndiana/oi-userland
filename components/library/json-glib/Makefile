#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2014 Alexander Pyhalov
# Copyright (c) 2022 Niklas Poslovski
#

BUILD_BITS= 64_and_32
BUILD_STYLE= meson
USE_DEFAULT_TEST_TRANSFORMS = yes
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= json-glib
HUMAN_VERSION=		1.10.0
COMPONENT_SUMMARY= JSON parser library for GLib
COMPONENT_ARCHIVE_HASH=	sha256:1bca8d66d96106ecc147df3133b95a5bb784f1fa6f15d06dd7c1a8fb4a10af7b
COMPONENT_FMRI= library/desktop/json-glib
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Libraries
COMPONENT_LICENSE= LGPLv2
COMPONENT_LICENSE_FILE= COPYING

COMPONENT_FMRI.json-glib-32 =		$(COMPONENT_FMRI)/32
COMPONENT_SUMMARY.json-glib-32 =	$(COMPONENT_SUMMARY) (32-bit)

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# There is no 32-bit introspection
CONFIGURE_OPTIONS.32 += -Dintrospection=disabled
# We do not need message catalogs built for 32-bit.
# Catalogs built during the 64-bit build will be used.
CONFIGURE_OPTIONS.32 += -Dnls=disabled
# For now we are not interested in installed tests
CONFIGURE_OPTIONS += -Dinstalled_tests=false

# Drop 32-bit binaries
COMPONENT_POST_INSTALL_ACTION.32 += $(RM) -r $(PROTOUSRBINDIR32) ;
# Drop include files installed for 32-bit build
COMPONENT_POST_INSTALL_ACTION.32 += $(RM) -r $(PROTOUSRINCDIR) ;

# Dynamic library version number
SOVER := $(shell printf '%s00.%s' $(wordlist 2,3,$(subst ., ,$(COMPONENT_VERSION))))
SOVER_RE = $(subst .,\.,$(SOVER))

# Replace library version number by SOVER
GENERATE_EXTRA_CMD += | $(GSED) -e 's/$(SOVER_RE)/$$(SOVER)/'

# SOVER is needed for manifest processing
PKG_MACROS += SOVER=$(SOVER)

# Build dependencies
PYTHON_REQUIRED_PACKAGES += library/python/gi-docgen
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/glib2/32
REQUIRED_PACKAGES += system/library
