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
# Copyright 2020 Michal Nowak
# Copyright 2019 Tim Mooney
# Copyright 2020 Jim Klimov
# Copyright 2021 omnios.org wrt the ctx patches
# Copyright 2022 Daniel Bell

BUILD_STYLE= configure
BUILD_BITS= 64
USE_OPENSSL11= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         VirtualBox
COMPONENT_VERSION=      6.1.40
COMPONENT_REVISION=		2
COMPONENT_SUMMARY=      VirtualBox - general-purpose full virtualizer
COMPONENT_PROJECT_URL=  https://www.virtualbox.org/
COMPONENT_DOWNLOAD_URL= https://download.virtualbox.org/virtualbox/$(COMPONENT_VERSION)
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_URL=  $(COMPONENT_DOWNLOAD_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         system/virtualbox
COMPONENT_CLASSIFICATION=System/Virtualization
COMPONENT_LICENSE=      GPLv2

HASH_DIR= $(COMPONENT_DIR)/hashes
export HASH_DIR

FETCH_KEEP= -n --keep
DEFAULT_HASH_FILES= SHA256SUMS
export DEFAULT_HASH_FILES

# We need the hashfile before even parsing the Makefile since we need the build number from it.
ifeq (,$(wildcard $(HASH_DIR)/SHA256SUMS))
$(shell curl -q -o $(HASH_DIR)/SHA256SUMS $(COMPONENT_DOWNLOAD_URL)/SHA256SUMS)
endif
SDK_BUILD_NUM=$(shell sed -E '/ [ \*]VirtualBoxSDK.*zip/!d;s/(^[0-9a-fA-F]+ [ \*]VirtualBoxSDK-[0-9\.]+-)([0-9]+)(.*$$)/\2/' $(HASH_DIR)/SHA256SUMS)


COMPONENT_NAME_1=       VirtualBoxSDK
COMPONENT_VERSION_1=    $(COMPONENT_VERSION)-$(SDK_BUILD_NUM)
COMPONENT_SRC_1=        $(COMPONENT_NAME_1)-$(COMPONENT_VERSION_1)
COMPONENT_ARCHIVE_URL_1=$(COMPONENT_DOWNLOAD_URL)/$(COMPONENT_ARCHIVE_1)
COMPONENT_ARCHIVE_1=    $(COMPONENT_SRC_1).zip
COMPONENT_LICENSE_1=	GPLv2

UNPACK_ARGS_1=		-r $(COMPONENT_SRC_1)

COMPONENT_POST_UNPACK_ACTION_1 = \
	cd $(COMPONENT_SRC); $(LN) -s ../$(COMPONENT_SRC_1)/sdk .;

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

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

QT5_ROOT=/usr/lib/qt/5.15
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

# Do not allow compiler override in kmk files
LOCAL_CONFIG+= '\nTOOL_GXX3PLAIN_CC  = $(CC)'
LOCAL_CONFIG+= '\nTOOL_GXX3PLAIN_CXX = $(CXX)'
LOCAL_CONFIG+= '\nTOOL_GXX3PLAIN_AS  = $(CC)'
LOCAL_CONFIG+= '\nTOOL_GXX3PLAIN_LD  = $(CXX)'
LOCAL_CONFIG+= '\nTOOL_GCC3PLAIN_CC  = $(CC)'
LOCAL_CONFIG+= '\nTOOL_GCC3PLAIN_CXX = $(CXX)'
LOCAL_CONFIG+= '\nTOOL_GCC3PLAIN_AS  = $(CC)'
LOCAL_CONFIG+= '\nTOOL_GCC3PLAIN_LD  = $(CXX)'

# Set OpenIndiana project as publisher of VirtualBox binaries
VBOX_BUILD_PUBLISHER=OpenIndiana

COMPONENT_PRE_CONFIGURE_ACTION= \
  ( cd $(@D); echo $(LOCAL_CONFIG) > LocalConfig.kmk; $(CP) -a $(SOURCE_DIR)/* $(@D) )

# Note: VirtualBox does not use a fully featured autoconf-style script,
# so we must define the full set of command line options here, not using
# values set via our configure.mk. Same for .32/.64 values added below.
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

CONFIGURE_OPTIONS.32 = --only-additions
CONFIGURE_OPTIONS.32 += --target-arch=x86
CONFIGURE_OPTIONS.64 = --enable-qt5

CONFIGURE_OPTIONS += $(CONFIGURE_OPTIONS.$(BITS))

VBOX_PREFIX   = /opt/VirtualBox
VBOX_LIBDIR   = $(VBOX_PREFIX)/$(MACH64)
VBOX_QT5_LIBS = VirtualBoxVM.so VBoxDbg.so UICommon.so
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

$(INSTALL_64): GMAKE= cd $(@D)/src/VBox/Installer && $(SHELL) -c ". $(@D)/env.sh && kmk solaris-install VBOX_PATH_SI_SCRATCH_PKG=$(PROTO_DIR)"

install:	$(INSTALL_64) $(INSTALL_ADDITIONS)


# Build dependencies
REQUIRED_PACKAGES += driver/usb
REQUIRED_PACKAGES += system/header/header-agp
REQUIRED_PACKAGES += system/header/header-audio
REQUIRED_PACKAGES += system/header/header-usb
REQUIRED_PACKAGES += x11/library/libxinerama
REQUIRED_PACKAGES += library/libvncserver
REQUIRED_PACKAGES += developer/build/onbld
REQUIRED_PACKAGES += developer/object-file

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/gsoap
REQUIRED_PACKAGES += library/libvncserver
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/qt5
REQUIRED_PACKAGES += library/sdl
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcb
REQUIRED_PACKAGES += x11/library/libxcursor
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxmu
REQUIRED_PACKAGES += x11/library/toolkit/libxt
