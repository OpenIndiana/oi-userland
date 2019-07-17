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
# Copyright 2019 Michal Nowak
# Copyright 2019 Tim Mooney
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         VirtualBox
COMPONENT_VERSION=      6.0.10
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
	sha256:5236148a93267478fb6d306f6343aa9587d3f90f437f54c7b3485bd9d538d2f8
COMPONENT_LICENSE=      GPLv2

COMPONENT_NAME_1=       VirtualBoxSDK
COMPONENT_VERSION_1=    $(COMPONENT_VERSION)-132072
COMPONENT_SRC_1=        $(COMPONENT_NAME_1)-$(COMPONENT_VERSION_1)
COMPONENT_ARCHIVE_1=    $(COMPONENT_SRC_1).zip
COMPONENT_ARCHIVE_URL_1=$(COMPONENT_DOWNLOAD_URL)/$(COMPONENT_ARCHIVE_1)
COMPONENT_ARCHIVE_HASH_1= \
	sha256:06a4dbc92b35959f4af89c1cadf2ed06448ad98bf1570024fe00c687e5a83ef3
COMPONENT_LICENSE_1=      GPLv2
UNPACK_ARGS_1= -r $(COMPONENT_SRC_1)

COMPONENT_POST_UNPACK_ACTION_1 = \
	cd $(COMPONENT_SRC); $(LN) -s ../$(COMPONENT_SRC_1)/sdk .;

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

INSTALL_ADDITIONS = $(BUILD_DIR)/.install_additions

X11_SERVERDRV_DIR.32=/usr/lib/xorg/modules/drivers
X11_SERVERDRV_DIR.64=/usr/lib/xorg/modules/drivers/$(MACH64)
X11_SERVERDRV_DIR=$(X11_SERVERDRV_DIR.64)

X11_SERVERINP_DIR.32=/usr/lib/xorg/modules/input
X11_SERVERINP_DIR.64=/usr/lib/xorg/modules/input/$(MACH64)
X11_SERVERINP_DIR=$(X11_SERVERMODS_DIR.64)

VBOX_BINDIR= $(BUILD_DIR_64)/out/solaris.$(MACH64)/release/bin/additions/
VBOX_BINDIR.32= $(BUILD_DIR_32)/out/solaris.x86/release/bin/additions/
VBOX_MODULES= vboxguest vboxms vboxvideo
VBOX_FS_MODULES= vboxfs

VBOX_BINS= VBoxControl VBoxService VBoxClient
VBOX_SBINS= vboxmslnk
VBOX_OGLLIBS= VBoxOGL.so VBoxEGL.so

QT5_ROOT=/usr/lib/qt/5.8
PATH=$(PATH.gnu):$(QT5_ROOT)/bin/$(MACH64)
PKG_CONFIG_PATH=$(PKG_CONFIG_PATH.$(BITS)):$(QT5_ROOT)/lib/$(MACH64)/pkgconfig

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

LOCAL_CONFIG.64+='\nVBOX_WITH_VBOXDRV = 1'
LOCAL_CONFIG.64+='\nVBOX_WITH_NETFLT = 1'
LOCAL_CONFIG.64+='\nVBOX_WITH_NETADP = 1'

# Disable audio/video-recording 
LOCAL_CONFIG.64+='\nVBOX_WITH_VIDEOREC ='
LOCAL_CONFIG.64+='\nVBOX_WITH_AUDIO_VIDEOREC ='

# Enable building with pulse audio support
LOCAL_CONFIG.64 +='\nVBOX_WITH_AUDIO_PULSE = 1'

LOCAL_CONFIG.32 +='\nVBOX_ONLY_ADDITIONS  = 1'

LOCAL_CONFIG += $(LOCAL_CONFIG.$(BITS))

LOCAL_CONFIG +='\nVBOX_GCC_OPT=$(CXXFLAGS)'
LOCAL_CONFIG +='\nVBOX_GCC_std = -std=c++11'
LOCAL_CONFIG +='\nVBOX_WITH_TESTSUITE='
LOCAL_CONFIG +='\nVBOX_WITH_TESTCASES='
LOCAL_CONFIG +='\nVBOX_WITH_DRAG_AND_DROP_GH = 1'
LOCAL_CONFIG +='\nVBOX_WITH_X11_ADDITIONS = 1'

# Disable DTrace, needs patching
LOCAL_CONFIG+='\nVBOX_WITH_DTRACE_R3 ='
LOCAL_CONFIG+='\nVBOX_WITH_DTRACE_R3_MAIN ='
LOCAL_CONFIG+='\nVBOX_WITH_DTRACE_R0DRV ='
LOCAL_CONFIG+='\nVBOX_WITH_DTRACE_RC ='
LOCAL_CONFIG+='\nVBOX_WITH_NATIVE_DTRACE ='

# Set OpenIndiana project as publisher of VirtualBox binaries
VBOX_BUILD_PUBLISHER=OpenIndiana

COMPONENT_PRE_CONFIGURE_ACTION= \
  ( cd $(@D); echo $(LOCAL_CONFIG) > LocalConfig.kmk; $(CP) -a $(SOURCE_DIR)/* $(@D) )

CONFIGURE_OPTIONS = --with-gcc="$(CC)"
CONFIGURE_OPTIONS+= --with-g++="$(CXX)"

CONFIGURE_OPTIONS+= --disable-alsa
CONFIGURE_OPTIONS+= --disable-dbus
CONFIGURE_OPTIONS+= --disable-docs
# we enable pulse support in LocalConfig.kmk by setting the define, because
# --enable-pulse doesn't currently do what we need
# See: https://www.virtualbox.org/ticket/18544 for more info
#CONFIGURE_OPTIONS+= --enable-pulse
CONFIGURE_OPTIONS+= --disable-python
CONFIGURE_OPTIONS+= --disable-sdl-ttf
CONFIGURE_OPTIONS+= --disable-libvpx
CONFIGURE_OPTIONS+= --nofatal
CONFIGURE_OPTIONS+= --enable-webservice
CONFIGURE_OPTIONS+= --enable-vnc

CONFIGURE_OPTIONS.32 += --only-additions
CONFIGURE_OPTIONS.32 += --target-arch=x86
CONFIGURE_OPTIONS.64 += --enable-qt5

CONFIGURE_OPTIONS += $(CONFIGURE_OPTIONS.$(BITS))

VBOX_PREFIX   = /opt/VirtualBox
VBOX_LIBDIR   = $(VBOX_PREFIX)/$(MACH64)
VBOX_QT5_LIBS = VirtualBoxVM.so VBoxDbg.so VBoxGlobal.so
VBOX_QT5_RPATH= $(VBOX_LIBDIR):$(GCC_LIBDIR):$(QT5_ROOT)/lib/$(MACH64)

# As IPS is "no scripting land", user has to install the VNC extension Pack manually:
# https://www.virtualbox.org/manual/UserManual.html#otherextpacks.
COMPONENT_POST_INSTALL_ACTION = \
	build/amd64/kBuild/bin/solaris.amd64/kmk -C $(@D)/src/VBox/ExtPacks/VNC packing; \
	pushd $(@D)/out/solaris.amd64/release/packages/; \
	mkdir -p $(PROTO_DIR)$(VBOX_PREFIX)/ExtensionPacks/; \
	install -m 644 VNC-*.vbox-extpack $(PROTO_DIR)$(VBOX_PREFIX)/ExtensionPacks/VNC-$(COMPONENT_VERSION).vbox-extpack; \
	popd; \
	for file in $(VBOX_QT5_LIBS); \
	do \
		/usr/bin/elfedit -e 'dyn:value -s RUNPATH "$(VBOX_QT5_RPATH)"' $(PROTO_DIR)$(VBOX_LIBDIR)/$$file; \
		/usr/bin/elfedit -e 'dyn:value -s RPATH   "$(VBOX_QT5_RPATH)"' $(PROTO_DIR)$(VBOX_LIBDIR)/$$file; \
	done; \
	/usr/bin/elfedit -e 'dyn:value -s RUNPATH "$(VBOX_QT5_RPATH)"' $(PROTO_DIR)$(VBOX_PREFIX)/$(MACH64)/VirtualBox; \
	/usr/bin/elfedit -e 'dyn:value -s RPATH   "$(VBOX_QT5_RPATH)"' $(PROTO_DIR)$(VBOX_PREFIX)/$(MACH64)/VirtualBox; \
	echo "$(COMPONENT_VERSION)" > $(PROTO_DIR)$(VBOX_PREFIX)/VERSION

$(INSTALL_ADDITIONS):	$(INSTALL_64)
	$(MKDIR) $(PROTO_DIR)/usr/bin
	$(MKDIR) $(PROTO_DIR)/usr/sbin
	$(MKDIR) $(PROTO_DIR)/usr/kernel/drv/$(MACH64)
	for fl in $(VBOX_MODULES); do \
		cp $(VBOX_BINDIR)/$$fl $(PROTO_DIR)/usr/kernel/drv/$(MACH64); \
		cp $(VBOX_BINDIR)/$$fl.conf $(PROTO_DIR)/usr/kernel/drv || true; \
	done
	$(MKDIR) $(PROTO_DIR)/usr/kernel/fs/$(MACH64)
	for fl in $(VBOX_FS_MODULES); do \
		cp $(VBOX_BINDIR)/$$fl $(PROTO_DIR)/usr/kernel/fs/$(MACH64); \
	done
	for fl in $(VBOX_BINS); do \
		cp $(VBOX_BINDIR)/$$fl $(PROTO_DIR)/usr/bin; \
        done
	for fl in $(VBOX_SBINS); do \
		cp $(VBOX_BINDIR)/$$fl $(PROTO_DIR)/usr/sbin; \
        done
	cp $(VBOX_BINDIR)/1099.vboxclient $(PROTO_DIR)/usr/bin/VBoxClient-all
	$(MKDIR) $(PROTO_DIR)/usr/lib/$(MACH64)
	for fl in $(VBOX_OGLLIBS); do \
		cp $(VBOX_BINDIR)/$$fl $(PROTO_DIR)/usr/lib/$(MACH64); \
		cp $(VBOX_BINDIR.32)/$$fl $(PROTO_DIR)/usr/lib/; \
        done
	$(MKDIR) $(PROTO_DIR)/var/svc/manifest/application/virtualbox
	cp $(VBOX_BINDIR)/vboxservice.xml $(PROTO_DIR)/var/svc/manifest/application/virtualbox
	cp $(VBOX_BINDIR)/vboxmslnk.xml $(PROTO_DIR)/var/svc/manifest/application/virtualbox
	$(MKDIR) $(PROTO_DIR)/etc/fs/vboxfs
	cp $(VBOX_BINDIR)/vboxfsmount $(PROTO_DIR)/etc/fs/vboxfs/mount
	$(MKDIR) $(PROTO_DIR)/etc/xdg/autostart
	cp $(VBOX_BINDIR)/vboxclient.desktop $(PROTO_DIR)/etc/xdg/autostart
	$(MKDIR) $(PROTO_DIR)/$(X11_SERVERDRV_DIR)
	cp $(VBOX_BINDIR)/vboxvideo_drv_system.so $(PROTO_DIR)/$(X11_SERVERDRV_DIR)/vboxvideo_drv.so
	$(MKDIR) $(PROTO_DIR)/lib/opengl/ogl_select
	cp $(VBOX_BINDIR)/vbox_vendor_select $(PROTO_DIR)/lib/opengl/ogl_select
	$(TOUCH) $@

$(BUILD_32_and_64): GMAKE= cd $(@D)/src/VBox/HostDrivers && $(SHELL) -c ". $(@D)/env.sh && kmk KBUILD_VERBOSE=3"

# Sometimes 32-bit build is skipped silently. Better build like this:
#	gmake build install sample-manifest
build:		$(BUILD_32_and_64) 

$(INSTALL_64): GMAKE= cd $(@D)/src/VBox/Installer && $(SHELL) -c ". $(@D)/env.sh && kmk solaris-install VBOX_PATH_SI_SCRATCH_PKG=$(PROTO_DIR)"

install:	$(INSTALL_64) $(INSTALL_ADDITIONS)

test:		$(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES += driver/usb
REQUIRED_PACKAGES += system/header/header-agp
REQUIRED_PACKAGES += system/header/header-audio
REQUIRED_PACKAGES += system/header/header-usb
REQUIRED_PACKAGES += x11/library/libxinerama
REQUIRED_PACKAGES += library/libvncserver

# Auto-generated dependencies
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/gsoap
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/qt5
REQUIRED_PACKAGES += library/sdl
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG) 
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcb
REQUIRED_PACKAGES += x11/library/libxcomposite
REQUIRED_PACKAGES += x11/library/libxcursor
REQUIRED_PACKAGES += x11/library/libxdamage
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxfixes
REQUIRED_PACKAGES += x11/library/libxmu
REQUIRED_PACKAGES += x11/library/libxrandr
REQUIRED_PACKAGES += x11/library/toolkit/libxt
