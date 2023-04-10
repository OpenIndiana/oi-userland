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
# Copyright (c) 2016 Alexander Pyhalov
# Copyright (c) 2017 Ken Mays
# Copyright (c) 2023 Klaus Ziegler
#

BUILD_BITS = 64_and_32
USE_DEFAULT_TEST_TRANSFORMS = yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           hunspell
COMPONENT_VERSION=        1.7.2
COMPONENT_REVISION=       1
COMPONENT_SUMMARY=        Hunspell is a free spell checker and morphological analyzer library and command-line tool
COMPONENT_PROJECT_URL=    https://hunspell.github.io/
COMPONENT_SRC=            $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=   sha256:69fa312d3586c988789266eaf7ffc9861d9f6396c31fc930a014d551b59bbd6e
COMPONENT_ARCHIVE_URL=    https://github.com/hunspell/hunspell/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=           text/hunspell
COMPONENT_CLASSIFICATION= System/Text Tools
COMPONENT_LICENSE=        GPLv3, LGPLv3, MPLv1.1

include $(WS_MAKE_RULES)/common.mk

PATH = $(PATH.gnu)

CPPFLAGS += -I/usr/include/ncurses

CFLAGS += $(CPP_XPG6MODE)

COMPONENT_PREP_ACTION = ( cd $(@D) && autoreconf -vif )

# Missing files in build dir without this.
COMPONENT_PRE_CONFIGURE_ACTION = ( $(CLONEY) $(SOURCE_DIR) $(@D) )

CONFIGURE_SCRIPT = $(@D)/configure

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

CONFIGURE_OPTIONS += --with-ui
CONFIGURE_OPTIONS += --with-readline

unexport SHELLOPTS

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
