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
# Copyright 2015 Alexander Pyhalov
# Copyright 2022 Niklas Poslovski
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= enchant
COMPONENT_VERSION= 2.3.2
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= GNOME spell checker component
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:ce9ba47fd4d34031bd69445598a698a6611602b2b0e91d705e91a6f5099ead6e
COMPONENT_ARCHIVE_URL= \
  https://github.com/AbiWord/enchant/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://abiword.github.io/enchant/
COMPONENT_LICENSE = LGPLv2.1
COMPONENT_FMRI = library/spell-checking/enchant
COMPONENT_CLASSIFICATION = Applications/Accessories

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION = ( cd $(@D)  && autoreconf -vif )

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --libexecdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS += --localstatedir=/var
CONFIGURE_OPTIONS += --with-hunspell-dir=/usr/share/spell/hunspell
CONFIGURE_OPTIONS += --disable-aspell
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += OBJC=$(CC)

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

# C tests pass but we do not have unittest-cpp
test: $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += text/aspell
REQUIRED_PACKAGES += text/hunspell
