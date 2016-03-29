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
# Copyright 2016 Till Wegmueller
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mint-menu
COMPONENT_VERSION=	5.5.2
COMPONENT_PROJECT_URL=	http://www.linuxmint.com
COMPONENT_SUMMARY=	Advanced MATE menu
COMPONENT_SRC=		mintmenu-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:1ba7cb9f280760df49f55d55a9633f1e40d72cae7144aec9f90369ca55f4ac71
COMPONENT_ARCHIVE_URL= https://github.com/linuxmint/mintmenu/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE= GPLv2, LGPLv2, FDLv1.1
COMPONENT_LICENSE_FILE= $(COMPONENT_NAME).license
COMPONENT_CLASSIFICATION = System/Libraries
COMPONENT_FMRI = library/desktop/mate/$(COMPONENT_NAME)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION =  $(CP) $(WS_TOP)/make-rules/cp-install.mk $(SOURCE_DIR)/Makefile&&
COMPONENT_PREP_ACTION += touch $(SOURCE_DIR)/configure
COMPONENT_PRE_CONFIGURE_ACTION = $(CLONEY) $(SOURCE_DIR) $(@D)
COMPONENT_INSTALL_ENV += SOURCE_DIR=$(SOURCE_DIR)
COMPONENT_INSTALL_ENV += PROTO_DIR=$(PROTO_DIR)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
