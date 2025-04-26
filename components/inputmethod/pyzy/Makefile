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

COMPONENT_NAME=           pyzy
COMPONENT_VERSION=        0.1.0
COMPONENT_GIT_REV=	6d9c3cdff364e0da75e1c26222240f26370ebf73
COMPONENT_SUMMARY=        pyzy - The Chinese PinYin and Bopomofo conversion library
COMPONENT_SRC=		pyzy-$(COMPONENT_GIT_REV)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=   sha256:abd1712b73a28b1202c7f8b5339b1f71eb5f7c013ac785c9941b73586bdaff31
COMPONENT_ARCHIVE_URL=    https://codeload.github.com/pyzy/$(COMPONENT_NAME)/tar.gz/$(COMPONENT_GIT_REV)
COMPONENT_FMRI=           system/input-method/library/pyzy
COMPONENT_CLASSIFICATION= System/Localizations
COMPONENT_LICENSE=        LGPL v2.1
COMPONENT_LICENSE_FILE=   COPYING
COMPONENT_PROJECT_URL=    https://github.com/pyzy/pyzy

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION =	(cd $(@D) && PATH="$(PATH)" NOCONFIGURE=1 ./autogen.sh)

CONFIGURE_OPTIONS += --disable-static
#CONFIGURE_OPTIONS += --enable-db-open-phrase
#CONFIGURE_OPTIONS += --enable-opencc

# Manually added build dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += developer/build/automake-115

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
