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
# Copyright 2017 Aurelien Larcher
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         bvi
COMPONENT_VERSION=      1.4.2
COMPONENT_SUMMARY=      bvi - Binary Visual Editor  
COMPONENT_PROJECT_URL=  http://bvi.sourceforge.net/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).src.tar.gz
COMPONENT_ARCHIVE_URL=  https://sourceforge.net/projects/bvi/files/bvi/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_ARCHIVE_HASH= sha256:4bba16c2b496963a9b939336c0abcc8d488664492080ae43a86da18cf4ce94f2
COMPONENT_FMRI=         editor/bvi
COMPONENT_CLASSIFICATION=Development/Editors
COMPONENT_LICENSE=      GPLv3
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION= ( $(CLONEY) $(SOURCE_DIR) $(@D) )

CONFIGURE_OPTIONS += --with-ncurses=$(USRDIR)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library
