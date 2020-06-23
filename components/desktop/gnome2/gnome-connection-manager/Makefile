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
COMPONENT_VERSION=	1.2.1
COMPONENT_PROJECT_URL=	http://kuthulu.com/gcm

COMPONENT_SRC=		$(COMPONENT_NAME_LONG)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_HASH=	\
    sha256:a78f90fc1b5ea5c3c0f068d51c5db75cfe5b77eff1bed0f910ac9d484b29f3a3

### How the original sites name the archive:
COMPONENT_ARCHIVE_ORIG=	v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/kuthulux/$(COMPONENT_NAME_LONG)/archive/$(COMPONENT_ARCHIVE_ORIG)

### How we name the archive to store on build hosts:
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz

COMPONENT_SUMMARY=	GCM - an Advanced SSH connections manager for X/Windows
COMPONENT_FMRI=		terminal/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk

PYTHON_VERSION =	3.5
PYV =	$(subst .,,$(PYTHON_VERSION))
PKG_MACROS +=		PYVER=$(PYTHON_VERSION)
PKG_MACROS +=		PYV=$(PYV)

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
REQUIRED_PACKAGES += library/python/pygobject-3-$(PYV)
REQUIRED_PACKAGES += library/python/pycairo-$(PYV)
REQUIRED_PACKAGES += runtime/python-$(PYV)
REQUIRED_PACKAGES += shell/expect
