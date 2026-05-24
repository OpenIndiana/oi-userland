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
# Copyright 2024 Marcel Telka
#

BUILD_STYLE = meson
USE_DEFAULT_TEST_TRANSFORMS = yes

include ../../../../make-rules/shared-macros.mk

# Odd minor versions are unstable.

COMPONENT_NAME=			at-spi2-core
HUMAN_VERSION=			2.60.4
COMPONENT_SUMMARY=		DBus interface definitions for AT-SPI (Assistive Technology Service Provider Interface)
COMPONENT_ARCHIVE_HASH=		sha256:1a1f5ba9805917f41fc6aa6823dcf887a291d607a427e2d5afb6b5dfa65070c7
COMPONENT_FMRI=			gnome/accessibility/at-spi2-core
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_LICENSE=		LGPL-2.1-only
COMPONENT_LICENSE_FILE=		COPYING

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# We do not need the systemd support (obviously)
CONFIGURE_OPTIONS += -Duse_systemd=false

# to get declaration of timersub()
CPPFLAGS += -D__EXTENSIONS__

# Move all modules from default site-packages directory to vendor-packages
# directory where we place modules shipped by the OS but not included in the
# core Python distribution.
COMPONENT_POST_INSTALL_ACTION += $(MV) $(PROTOPYTHONSITEDIR) $(PROTOPYTHONVENDORDIR) ;

# Testing needs dbus up and running
TEST_REQUIRED_PACKAGES += system/library/dbus/dbus-x11
COMPONENT_PRE_TEST_ACTION += $(ENV) /usr/bin/dbus-launch > $(BUILD_DIR_$(BITS))/.dbus-env ;
COMPONENT_TEST_ENV += $$($(CAT) $(BUILD_DIR_$(BITS))/.dbus-env)
COMPONENT_POST_TEST_ACTION += . $(BUILD_DIR_$(BITS))/.dbus-env ; kill $$DBUS_SESSION_BUS_PID ; $(RM) $(BUILD_DIR_$(BITS))/.dbus-env ;

# We need to start the currently built at-spi-bus-launcher and
# at-spi2-registryd because otherwise the installed one will be started (and so
# tested).  The sleep after the at-spi-bus-launcher start is needed to make
# sure it is properly running before we start at-spi2-registryd.  We do not
# need to kill at-spi-bus-launcher because it will end automatically.
COMPONENT_PRE_TEST_ACTION += $(ENV) $$($(CAT) $(BUILD_DIR_$(BITS))/.dbus-env) $(BUILD_DIR_$(BITS))/bus/at-spi-bus-launcher & sleep 5 ;
COMPONENT_PRE_TEST_ACTION += $(ENV) $$($(CAT) $(BUILD_DIR_$(BITS))/.dbus-env) $(BUILD_DIR_$(BITS))/registryd/at-spi2-registryd & echo $$! > $(BUILD_DIR_$(BITS))/.registry ;
COMPONENT_POST_TEST_ACTION += kill $$($(CAT) $(BUILD_DIR_$(BITS))/.registry) ; $(RM) $(BUILD_DIR_$(BITS))/.registry ;

# Dynamic library version number
SOVER = 26013.1
SOVER_RE = $(subst .,\.,$(SOVER))

# Replace library version number by SOVER
GENERATE_EXTRA_SED += -e 's/$(SOVER_RE)/$$(SOVER)/'

# SOVER is needed for manifest processing
PKG_VARS += SOVER

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxi
REQUIRED_PACKAGES += x11/library/libxres
REQUIRED_PACKAGES += x11/library/libxtst
