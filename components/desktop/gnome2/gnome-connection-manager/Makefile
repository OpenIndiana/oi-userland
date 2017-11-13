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

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnome-connection-manager
COMPONENT_NAME_SHORT=	gcm
COMPONENT_VERSION=	1.1.0
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://kuthulu.com/gcm
COMPONENT_SRC=		$(COMPONENT_NAME_SHORT)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_HASH=	\
    sha256:71a128676d16153c735499cec9f0a1af1e2dc1107ed5c57cea1994eadc120c4c
# Project site is gone, use a mirror for now
#COMPONENT_ARCHIVE=	$(COMPONENT_NAME)_$(COMPONENT_VERSION)_all.tgz
#COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)_$(COMPONENT_VERSION).orig.tar.gz
COMPONENT_ARCHIVE_URL= http://ftp.heanet.ie/mirrors/www.getdeb.net/getdeb/ubuntu/pool/apps/g/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)

COMPONENT_SUMMARY=	GCM - an Advanced SSH connections manager for X/Windows
COMPONENT_FMRI=		terminal/gnome-connection-manager
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk

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

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/desktop/vte
REQUIRED_PACKAGES += library/python/pygobject-27
REQUIRED_PACKAGES += library/python/pygtk2-27
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += shell/expect
