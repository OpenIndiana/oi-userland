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

BUILD_BITS = 64_and_32
BUILD_STYLE = meson
USE_DEFAULT_TEST_TRANSFORMS = yes

include ../../../../make-rules/shared-macros.mk

# Odd minor versions are unstable.

COMPONENT_NAME=			at-spi2-core
HUMAN_VERSION=			2.58.0
COMPONENT_SUMMARY=		DBus interface definitions for AT-SPI (Assistive Technology Service Provider Interface)
COMPONENT_ARCHIVE_HASH=		sha256:dfdd3300da2783a21969ffade2889817fb7c1906a4ef92497eba65969b3dab5a
COMPONENT_FMRI=			gnome/accessibility/at-spi2-core
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_LICENSE=		LGPL-2.1-only
COMPONENT_LICENSE_FILE=		COPYING

COMPONENT_FMRI.$(COMPONENT_NAME)-32 =		$(COMPONENT_FMRI)/32
COMPONENT_SUMMARY.$(COMPONENT_NAME)-32 =	$(COMPONENT_SUMMARY) (32-bit)

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# We do not need the systemd support (obviously)
CONFIGURE_OPTIONS += -Duse_systemd=false
# There is no 32-bit introspection
CONFIGURE_OPTIONS.32 += -Dintrospection=disabled

# to get declaration of timersub()
CPPFLAGS += -D__EXTENSIONS__

# Drop etc files installed for 32-bit build
COMPONENT_POST_INSTALL_ACTION.32 += $(RM) -r $(PROTOETCDIR) ;
# Drop include files installed for 32-bit build
COMPONENT_POST_INSTALL_ACTION.32 += $(RM) -r $(PROTOUSRINCDIR) ;
# Drop share files installed for 32-bit build
COMPONENT_POST_INSTALL_ACTION.32 += $(RM) -r $(PROTOUSRSHAREDIR) ;
# Drop Python support installed for 32-bit build
COMPONENT_POST_INSTALL_ACTION.32 += $(RM) -r $(PROTO_DIR)/$(PYTHON_DIR) ;

# Move all modules from default site-packages directory to vendor-packages
# directory where we place modules shipped by the OS but not included in the
# core Python distribution.
COMPONENT_POST_INSTALL_ACTION.64 += $(MV) $(PROTO_DIR)/$(PYTHON_DIR)/site-packages $(PROTO_DIR)/$(PYTHON_LIB) ;

# Testing needs dbus up and running
TEST_REQUIRED_PACKAGES += system/library/dbus/dbus-x11
COMPONENT_PRE_TEST_ACTION += /usr/bin/dbus-launch > $(BUILD_DIR_$(BITS))/.dbus-env ;
COMPONENT_TEST_ENV += $$($(CAT) $(BUILD_DIR_$(BITS))/.dbus-env)
COMPONENT_POST_TEST_ACTION += . $(BUILD_DIR_$(BITS))/.dbus-env ; kill $$DBUS_SESSION_BUS_PID ; $(RM) $(BUILD_DIR_$(BITS))/.dbus-env ;

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/glib2/32
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxi
REQUIRED_PACKAGES += x11/library/libxtst
