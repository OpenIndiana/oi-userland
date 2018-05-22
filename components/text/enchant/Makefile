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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= enchant
COMPONENT_VERSION= 1.6.1
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= GNOME spell checker component
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:bef0d9c0fef2e4e8746956b68e4d6c6641f6b85bd2908d91731efb68eba9e3f5
COMPONENT_ARCHIVE_URL= \
  https://github.com/AbiWord/enchant/releases/download/enchant-1-6-1/$(COMPONENT_ARCHIVE)
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
CONFIGURE_OPTIONS += --with-myspell-dir=/usr/share/spell/myspell
CONFIGURE_OPTIONS += --disable-aspell
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += OBJC=$(CC)

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

# C tests pass but we do not have unittest-cpp
test: $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += text/hunspell
