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
# Copyright (c) 2015-2020 Jim Klimov
#

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME_LONG=	gnome-connection-manager
COMPONENT_NAME_SHORT=	gcm
# The value below should match the .p5m and .license filenames, in particular:
COMPONENT_NAME=  		$(COMPONENT_NAME_LONG)
COMPONENT_VERSION=	1.2.0
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://kuthulu.com/gcm
# The new GCM release should bring support for Gtk3 and Python3,
# and is expected to work in OI unlike the venerable 1.1.0 made
# for Gtk2 which just stopped working. So far it is unreleased,
# hence the GitHub latest-commit fetching and tweaked definitions
# of COMPONENT_SRC and COMPONENT_ARCHIVE below:
COMPONENT_COMMIT_ID=	878d59ed3a77db55a6d22bbda5ce1ee1acac16a5
COMPONENT_SRC=		$(COMPONENT_NAME_LONG)-$(COMPONENT_COMMIT_ID)
###COMPONENT_SRC=		$(COMPONENT_NAME_SHORT)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_HASH=	\
    sha256:92f0db50a31cee9bce271a3f85c269d604737edf139e0b55d52a36c0217876c1

### How the original sites name the archive:
#COMPONENT_ARCHIVE_ORIG=	$(COMPONENT_NAME_LONG)_$(COMPONENT_VERSION)_all.tgz
###COMPONENT_ARCHIVE_ORIG=	$(COMPONENT_NAME_LONG)_$(COMPONENT_VERSION).orig.tar.gz
COMPONENT_ARCHIVE_ORIG=	$(COMPONENT_COMMIT_ID).zip

### Project site is gone, use a mirror for now
#COMPONENT_ARCHIVE_URL=	http://ftp.heanet.ie/mirrors/www.getdeb.net/getdeb/ubuntu/pool/apps/g/$(COMPONENT_NAME_LONG)/$(COMPONENT_ARCHIVE_ORIG)
#COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/$(COMPONENT_ARCHIVE_ORIG)
COMPONENT_ARCHIVE_URL=	https://github.com/kuthulux/$(COMPONENT_NAME_LONG)/archive/$(COMPONENT_ARCHIVE_ORIG)

### How we name the archive to store on build hosts:
#COMPONENT_ARCHIVE=	$(COMPONENT_ARCHIVE_ORIG)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION)-$(COMPONENT_COMMIT_ID).zip

COMPONENT_SUMMARY=	GCM - an Advanced SSH connections manager for X/Windows
COMPONENT_FMRI=		terminal/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk

PYTHON_VERSION =	3.5
PKG_MACROS +=		PYVER=$(PYTHON_VERSION)

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
REQUIRED_PACKAGES += library/desktop/vte-291
REQUIRED_PACKAGES += library/python/pygobject-3-35
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += shell/expect
