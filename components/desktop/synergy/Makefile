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
# Copyright 2015 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		synergy
COMPONENT_VERSION=      1.10.1
COMPONENT_REVISION=     1
COMPONENT_PROJECT_URL=	https://symless.com/synergy
COMPONENT_SUMMARY=	Synergy: Mouse and Keyboard Sharing
COMPONENT_SRC=		$(COMPONENT_NAME)-core-$(COMPONENT_VERSION)-stable
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
  sha256:67ef37a9c090e0197018220c04df3005fc574a391935c29b7cb0c3f208fd0429
COMPONENT_ARCHIVE_URL=	https://github.com/symless/synergy-core/archive/v$(COMPONENT_VERSION)-stable.tar.gz
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	LICENSE
COMPONENT_FMRI=		desktop/synergy
COMPONENT_CLASSIFICATION=Applications/System Utilities

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)
PATH=$(PATH.gnu):$(QT5_ROOT)/bin/
QT5_ROOT=/usr/lib/qt/5.8
PKG_CONFIG_PATH=$(QT5_ROOT)/lib/pkgconfig

LDFLAGS += -lnsl -lsocket

CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS += -DSYNERGY_BUILD_LEGACY_GUI:BOOL=OFF
CMAKE_OPTIONS += -DSYNERGY_BUILD_LEGACY_SERVICE:BOOL=OFF
CMAKE_OPTIONS += -DSYNERGY_BUILD_LEGACY_INSTALLER:BOOL=OFF

COMPONENT_PREP_ACTION += ($(RM) $(COMPONENT_SRC)/src/test/CMakeLists.txt)

MY_INSTALL_32 =            $(BUILD_DIR_32)/.my_installed

$(MY_INSTALL_32):	$(BUILD_32)
	$(RM) -r $(PROTO_DIR)
	$(MKDIR) $(PROTO_DIR)/usr/bin
	$(CP) $(BUILD_DIR_32)/bin/{synergyc,synergys,syntool} $(PROTO_DIR)/usr/bin
	$(MKDIR) $(PROTO_DIR)/usr/share/man/man1
	$(CP) $(SOURCE_DIR)/doc/synergyc.man $(PROTO_DIR)/usr/share/man/man1/synergyc.1
	$(CP) $(SOURCE_DIR)/doc/synergys.man $(PROTO_DIR)/usr/share/man/man1/synergys.1
	$(TOUCH) $(MY_INSTALL_32)

MY_INSTALL_64 =            $(BUILD_DIR_64)/.my_installed

$(MY_INSTALL_64):	$(BUILD_64)
	$(RM) -r $(PROTO_DIR)
	$(MKDIR) $(PROTO_DIR)/usr/bin
	$(CP) $(BUILD_DIR_64)/bin/{synergyc,synergys,syntool} $(PROTO_DIR)/usr/bin
	$(MKDIR) $(PROTO_DIR)/usr/share/man/man1
	$(CP) $(SOURCE_DIR)/doc/synergyc.man $(PROTO_DIR)/usr/share/man/man1/synergyc.1
	$(CP) $(SOURCE_DIR)/doc/synergys.man $(PROTO_DIR)/usr/share/man/man1/synergys.1
	$(TOUCH) $(MY_INSTALL_64)

# common targets
build:		$(BUILD_64)

install:	$(MY_INSTALL_64)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxi
REQUIRED_PACKAGES += x11/library/libxinerama
REQUIRED_PACKAGES += x11/library/libxtst
REQUIRED_PACKAGES += x11/library/libxrandr
REQUIRED_PACKAGES += library/security/openssl
