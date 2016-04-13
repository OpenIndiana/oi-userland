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
# Copyright (c) 2015 Jim Klimov
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnome-connection-manager
COMPONENT_NAME_SHORT=	gcm
COMPONENT_VERSION=	1.1.0
COMPONENT_PROJECT_URL=	http://kuthulu.com/gcm
COMPONENT_SRC=		$(COMPONENT_NAME_SHORT)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)_$(COMPONENT_VERSION)_all.tgz
COMPONENT_ARCHIVE_HASH=	\
    sha256:71a128676d16153c735499cec9f0a1af1e2dc1107ed5c57cea1994eadc120c4c
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_SUMMARY=	GCM - an Advanced SSH connections manager for X/Windows
COMPONENT_FMRI=		terminal/gnome-connection-manager
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

include ../../make-rules/prep.mk
include ../../make-rules/ips.mk

CLEAN_PATHS+= $(BUILD_DIR)

# rules are very simple, because the project is a script - just deliver and run
# unpacked directory is among search paths for the p5m installation anyway

$(BUILD_DIR)/.built:	$(SOURCE_DIR)/.prep
	$(RM) -r $(@D) ; $(MKDIR) $(@D)
	$(CLONEY) $(SOURCE_DIR) $(@D)
	find $(@D) -name '*.pyc' -exec rm -f '{}' \;
	$(PYTHON) -m compileall $(@D)
	$(TOUCH) $@

$(BUILD_DIR)/.installed:	$(BUILD_DIR)/.built
	$(TOUCH) $@

build:		$(BUILD_DIR)/.built files/gcm Makefile

install:	$(BUILD_DIR)/.installed Makefile

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
