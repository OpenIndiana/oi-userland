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
# Copyright 2024 Marcel Telka
#

BUILD_STYLE = meson
USE_DEFAULT_TEST_TRANSFORMS = yes

include ../../../make-rules/shared-macros.mk

# This is vte-2.91 ABI series
ABIVER = 2.91

COMPONENT_NAME=			vte
HUMAN_VERSION=			0.78.1
COMPONENT_SUMMARY=		Virtual terminal widget for GTK applications
COMPONENT_ARCHIVE_HASH=		sha256:6499d25179315255f9bcfce03c66fb84c03ad325dea23d0e372178521eca42b5
COMPONENT_FMRI=			library/desktop/vte-291
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_LICENSE=		CC-BY-4.0 AND GPL-3.0-only AND LGPL-3.0-only AND MIT

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# helper target
update-license-file: patch
	( \
		printf -- '--- COPYING.CC-BY-4-0 -----------------------------------------------------\n\n' ; \
		$(CAT) $(SOURCE_DIR)/COPYING.CC-BY-4-0 ; \
		printf '\n--- COPYING.GPL3 ----------------------------------------------------------\n\n' ; \
		$(CAT) $(SOURCE_DIR)/COPYING.GPL3 ; \
		printf '\n--- COPYING.LGPL3 ---------------------------------------------------------\n\n' ; \
		$(CAT) $(SOURCE_DIR)/COPYING.LGPL3 ; \
		printf '\n--- COPYING.XTERM ---------------------------------------------------------\n\n' ; \
		$(CAT) $(SOURCE_DIR)/COPYING.XTERM \
	) > $(COMPONENT_DIR)/$(COMPONENT_LICENSE_FILE)

# We need IMAXBEL and so we need to define __EXTENSIONS__
CFLAGS += -D__EXTENSIONS__

# We have no /etc/profile.d support
# See also https://www.illumos.org/issues/3395
COMPONENT_POST_INSTALL_ACTION += $(RM) -r $(PROTOETCDIR)/profile.d ;

# Replace ABI version number by ABIVER
ABIVER_RE = $(subst .,\.,$(ABIVER))
GENERATE_EXTRA_CMD += | $(GSED) -e 's/\([Vv]te-\)$(ABIVER_RE)/\1$$(ABIVER)/g'

# ABIVER is needed for manifest processing
PKG_MACROS += ABIVER=$(ABIVER)

# Dynamic library version number
SOVER := $(shell printf '%s00.%s' $(wordlist 2,3,$(subst ., ,$(COMPONENT_VERSION))))
SOVER_RE = $(subst .,\.,$(SOVER))

# Replace library version number by SOVER
GENERATE_EXTRA_CMD += | $(GSED) -e 's/$(SOVER_RE)/$$(SOVER)/'

# SOVER is needed for manifest processing
PKG_MACROS += SOVER=$(SOVER)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(ICU_LIBRARY_PKG)
REQUIRED_PACKAGES += gnome/accessibility/at-spi2-core
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/graphene
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/gtk4
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/fribidi
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/lz4
REQUIRED_PACKAGES += library/pcre2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
