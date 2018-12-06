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

COMPONENT_NAME=         VirtualBox
COMPONENT_VERSION=      5.2.22
COMPONENT_SUMMARY=      VirtualBox - general-purpose full virtualizer
COMPONENT_PROJECT_URL=  http://www.virtualbox.org/
COMPONENT_FMRI=         system/virtualbox
COMPONENT_CLASSIFICATION= System/Virtualization
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_DOWNLOAD_URL= \
  http://download.virtualbox.org/virtualbox/$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_URL=  $(COMPONENT_DOWNLOAD_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
  sha256:5580e875349341a1aabc6d5d2f697d242f277487316faaf1fbe68d9014f788d4
COMPONENT_LICENSE=      GPLv2

COMPONENT_NAME_1=       VirtualBoxSDK
COMPONENT_VERSION_1=    $(COMPONENT_VERSION)-126460
COMPONENT_SRC_1=        $(COMPONENT_NAME_1)-$(COMPONENT_VERSION_1)
COMPONENT_ARCHIVE_1=    $(COMPONENT_SRC_1).zip
COMPONENT_ARCHIVE_URL_1=$(COMPONENT_DOWNLOAD_URL)/$(COMPONENT_ARCHIVE_1)
COMPONENT_ARCHIVE_HASH_1= \
  sha256:b15fc5330d435834c1a683c63b4117feb7cb96a02a30a0c034b8c4c746c93259
COMPONENT_LICENSE_1=      GPLv2
UNPACK_ARGS_1= -r $(COMPONENT_SRC_1)

COMPONENT_POST_UNPACK_ACTION_1 = \
	cd $(COMPONENT_SRC); $(LN) -s ../$(COMPONENT_SRC_1)/sdk .;

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

X11_SERVERMODS_DIR=/usr/lib/xorg/modules
X11_SERVERLIBS_DIR=/usr/lib/xorg

QT5_ROOT=/usr/lib/qt/5.8
PATH=$(PATH.gnu):$(QT5_ROOT)/bin/$(MACH64)
PKG_CONFIG_PATH=$(PKG_CONFIG_PATH.64):$(QT5_ROOT)/lib/$(MACH64)/pkgconfig

CONFIGURE_SCRIPT=$(@D)/configure

# Build for the system Xorg (only possibility for 1.19) or for any guest up to 1.18
USE_SYSTEM_X11=yes
ifeq ($(strip $(USE_SYSTEM_X11)),yes)
LOCAL_CONFIG+='\nVBOX_USE_SYSTEM_XORG_HEADERS = 1'
LOCAL_CONFIG+='\nVBOX_USE_SYSTEM_GL_HEADERS = 1'
endif

COMPONENT_BUILD_GMAKE_ARGS=
COMPONENT_BUILD_ARGS=
COMPONENT_BUILD_TARGETS=
COMPONENT_INSTALL_GMAKE_ARGS=
COMPONENT_INSTALL_ARGS=
COMPONENT_INSTALL_TARGETS=

LOCAL_CONFIG+='\nVBOX_WITH_DRAG_AND_DROP_GH = 1'
LOCAL_CONFIG+='\nVBOX_WITH_VBOXDRV = 1'
LOCAL_CONFIG+='\nVBOX_WITH_NETFLT = 1'
LOCAL_CONFIG+='\nVBOX_WITH_NETADP = 1'
LOCAL_CONFIG+='\nVBOX_WITHOUT_ADDITIONS = 1'
LOCAL_CONFIG+='\nVBOX_GCC_OPT=$(CXXFLAGS)'
LOCAL_CONFIG+='\nVBOX_GCC_std = -std=c++11'
LOCAL_CONFIG+='\nVBOX_WITH_TESTSUITE='
LOCAL_CONFIG+='\nVBOX_WITH_TESTCASES='

# Disable DTrace, needs patching
LOCAL_CONFIG+='\nVBOX_WITH_DTRACE_R3 ='
LOCAL_CONFIG+='\nVBOX_WITH_DTRACE_R3_MAIN ='
LOCAL_CONFIG+='\nVBOX_WITH_DTRACE_R0DRV ='
LOCAL_CONFIG+='\nVBOX_WITH_DTRACE_RC ='
LOCAL_CONFIG+='\nVBOX_WITH_NATIVE_DTRACE ='

COMPONENT_PRE_CONFIGURE_ACTION= \
  ( cd $(@D); echo $(LOCAL_CONFIG) > LocalConfig.kmk; $(CP) -a $(SOURCE_DIR)/* $(@D) )

CONFIGURE_OPTIONS = --with-gcc="$(CC)"
CONFIGURE_OPTIONS+= --with-g++="$(CXX)"
CONFIGURE_OPTIONS+= --enable-qt5
CONFIGURE_OPTIONS+= --disable-alsa
CONFIGURE_OPTIONS+= --disable-dbus
CONFIGURE_OPTIONS+= --disable-docs
CONFIGURE_OPTIONS+= --enable-pulse
CONFIGURE_OPTIONS+= --disable-python
CONFIGURE_OPTIONS+= --disable-sdl-ttf
CONFIGURE_OPTIONS+= --disable-libvpx
CONFIGURE_OPTIONS+= --nofatal

VBOX_PREFIX   = /opt/VirtualBox
VBOX_LIBDIR   = $(VBOX_PREFIX)/$(MACH64)
VBOX_QT5_LIBS = VirtualBox.so VBoxDbg.so
VBOX_QT5_RPATH= $(VBOX_LIBDIR):$(GCC_LIBDIR):$(QT5_ROOT)/lib/$(MACH64)
COMPONENT_POST_INSTALL_ACTION = \
	for file in $(VBOX_QT5_LIBS); \
	do \
		/usr/bin/elfedit -e 'dyn:value -s RUNPATH "$(VBOX_QT5_RPATH)"' $(PROTO_DIR)$(VBOX_LIBDIR)/$$file; \
		/usr/bin/elfedit -e 'dyn:value -s RPATH   "$(VBOX_QT5_RPATH)"' $(PROTO_DIR)$(VBOX_LIBDIR)/$$file; \
	done; \
	echo "$(COMPONENT_VERSION)" > $(PROTO_DIR)$(VBOX_PREFIX)/VERSION
		
$(BUILD_64): GMAKE= cd $(@D)/src/VBox/HostDrivers && $(SHELL) -c ". $(@D)/env.sh && kmk"

build:		$(BUILD_64) 

$(INSTALL_64): GMAKE= cd $(@D)/src/VBox/Installer && $(SHELL) -c ". $(@D)/env.sh && kmk solaris-install VBOX_PATH_SI_SCRATCH_PKG=$(PROTO_DIR)"

install:	$(INSTALL_64)

test:		$(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES += system/header/header-audio

# Auto-generated dependencies
REQUIRED_PACKAGES += driver/usb
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/sdl
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG) 
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcursor
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxmu
REQUIRED_PACKAGES += x11/library/toolkit/libxt
