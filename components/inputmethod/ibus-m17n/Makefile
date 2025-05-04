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
# Copyright 2025 Jiwon Na
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           ibus-m17n
COMPONENT_VERSION=        1.4.36
COMPONENT_SUMMARY=        ibus-m17n - The m17n engine for IBus
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=   sha256:96573d52e443e8cd9644c8d52a8609f0f3e560a7d27d5abf061f9e095ce8bd0d
COMPONENT_ARCHIVE_URL=    https://github.com/ibus/$(COMPONENT_NAME)/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

COMPONENT_FMRI=           system/input-method/ibus/m17n
COMPONENT_CLASSIFICATION= System/Localizations
COMPONENT_LICENSE=        GPL v2
COMPONENT_LICENSE_FILE=   COPYING
COMPONENT_PROJECT_URL=    https://github.com/ibus/ibus-m17n

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_PRE_CONFIGURE_ACTION= ( $(CLONEY) $(SOURCE_DIR) $(@D) )

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/input-method/ibus
REQUIRED_PACKAGES += system/input-method/library/m17n
REQUIRED_PACKAGES += system/library
