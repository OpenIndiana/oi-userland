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

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= enchant
COMPONENT_VERSION= 2.8.14
COMPONENT_SUMMARY= GNOME spell checker component
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:d04588769399ff7140fa214b9731e6fc6eda9bb2e75df9f67263717710bb4c4b
COMPONENT_ARCHIVE_URL=	https://github.com/AbiWord/enchant/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://abiword.github.io/enchant/
COMPONENT_FMRI=			library/spell-checking/enchant
COMPONENT_CLASSIFICATION=	Applications/Accessories
COMPONENT_LICENSE=		LGPLv2.1
COMPONENT_LICENSE_FILE=	COPYING.LIB

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = ( cd $(@D)  && autoreconf -vif )

CONFIGURE_OPTIONS += --with-hunspell-dir=$(USRSHAREDIR)/spell/hunspell
CONFIGURE_OPTIONS += --disable-aspell
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-relocatable
CONFIGURE_OPTIONS += OBJC=$(CC)

# Manually added dependencies
TEST_REQUIRED_PACKAGES += developer/unittest-cpp

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += text/aspell
REQUIRED_PACKAGES += text/hunspell
