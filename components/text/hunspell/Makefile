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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           hunspell
COMPONENT_VERSION=        1.6.2
COMPONENT_PROJECT_URL=    http://hunspell.github.io/
COMPONENT_SUMMARY=        Improved spellchecker
COMPONENT_SRC=            $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=        \
    sha256:3cd9ceb062fe5814f668e4f22b2fa6e3ba0b339b921739541ce180cac4d6f4c4 
COMPONENT_ARCHIVE_URL=        https://github.com/hunspell/hunspell/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE=	GPLv3, LGPLv3, MPLv1.1
COMPONENT_FMRI= text/hunspell
COMPONENT_CLASSIFICATION = System/Text Tools

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

CPPFLAGS += -I/usr/include/ncurses
# We need to check headers with C++ compiler, but configure uses $(CC).
# We can't use $(CXX) as $(CC) as $(CC) is used to compile C files.
# So we make $(CC) behave more like $(CXX) during configure.
CFLAGS += -D_XOPEN_SOURCE=600
CFLAGS += -std=c99

COMPONENT_PREP_ACTION = ( cd $(@D) && autoreconf -vif )

# Missing files in build dir without this.
COMPONENT_PRE_CONFIGURE_ACTION =	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SCRIPT = $(@D)/configure

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

CONFIGURE_OPTIONS+=        --with-ui
CONFIGURE_OPTIONS+=        --with-readline

unexport SHELLOPTS

COMPONENT_TEST_MASTER =     $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += \
     '-n ' \
     '-e "/TOTAL:/p" ' \
     '-e "/SKIP:/p" ' \
     '-e "/PASS:/p" ' \
     '-e "/FAIL:/p" ' \
     '-e "/ERROR:/p" '

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
