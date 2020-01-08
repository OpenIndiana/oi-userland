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

PREFERRED_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         bvi
COMPONENT_VERSION=      1.4.1
COMPONENT_SUMMARY=      bvi - Binary Visual Editor  
COMPONENT_PROJECT_URL=  http://bvi.sourceforge.net/
COMPONENT_FMRI=         editor/bvi
COMPONENT_CLASSIFICATION=Development/Editors
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).src.tar.gz
COMPONENT_ARCHIVE_URL= \
  http://sourceforge.net/projects/bvi/files/bvi/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_ARCHIVE_HASH= \
  sha256:3035255ca79e0464567d255baa5544f7794e2b7eb791dcc60cc339cf1aa01e28
COMPONENT_LICENSE=      GPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION= ( $(CLONEY) $(SOURCE_DIR) $(@D) )

CONFIGURE_OPTIONS+= --with-ncurses=$(USRDIR)

build:    $(BUILD_64)

install:  $(INSTALL_64)

test:    $(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES += library/ncurses

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
