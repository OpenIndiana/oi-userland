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

COMPONENT_NAME=           ibus-pinyin
COMPONENT_VERSION=        1.5.1
COMPONENT_SUMMARY=        ibus-pinyin - The PinYin engine for IBus
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_NAME)-$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=   sha256:3e971567b72dae4b08b710fd1471bff34f58814df2aa74e97ed386590df3c5db
COMPONENT_ARCHIVE_URL=    https://github.com/ibus/$(COMPONENT_NAME)/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=           system/input-method/ibus/pinyin
COMPONENT_CLASSIFICATION= System/Localizations
COMPONENT_LICENSE=        GPL v2
COMPONENT_LICENSE_FILE=   COPYING
COMPONENT_PROJECT_URL=    https://github.com/ibus/ibus-pinyin

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_PREP_ACTION =	(cd $(@D) && PATH="$(PATH)" NOCONFIGURE=1 ./autogen.sh)

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-lua-extension

# Manually added build dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += developer/build/automake-115

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/input-method/ibus
REQUIRED_PACKAGES += system/input-method/library/pyzy
REQUIRED_PACKAGES += system/library
