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
COMPONENT_VERSION=      5.2.18
COMPONENT_SUMMARY=      VirtualBox - Host drivers
COMPONENT_PROJECT_URL=  http://www.virtualbox.org/
COMPONENT_FMRI=         driver/virtualbox
COMPONENT_CLASSIFICATION= System/Virtualization
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_URL= \
  http://download.virtualbox.org/virtualbox/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE) 
COMPONENT_ARCHIVE_HASH= \
  sha256:ed0a7efd56c7f39fae79c7ec3321473da412ef0d7914457b66f42679d513efcf
COMPONENT_LICENSE=      GPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

X11_SERVERMODS_DIR=/usr/lib/xorg/modules
X11_SERVERLIBS_DIR=/usr/lib/xorg

VBOX_DIR_REL=	lib/virtualbox
VBOX_DIR=	$(CONFIGURE_PREFIX)/$VBOX_DIR_REL

CONFIGURE_SCRIPT=$(@D)/configure

# Build for the system Xorg (only possibility for 1.19) or for any guest up to 1.18
USE_SYSTEM_X11=1

#GMAKE= cd $(@D)/src/VBox/HostDrivers && $(SHELL) -c ". $(@D)/env.sh && kmk"
COMPONENT_BUILD_GMAKE_ARGS=
COMPONENT_BUILD_ARGS=
COMPONENT_BUILD_TARGETS=

LOCAL_CONFIG+='\nVBOX_WITH_VBOXDRV = 1'
LOCAL_CONFIG+='\nVBOX_WITH_NETFLT = 1'
LOCAL_CONFIG+='\nVBOX_WITH_NETADP = 1'
LOCAL_CONFIG+='\nVBOX_WITH_ADDITIONS ='
LOCAL_CONFIG+='\nVBOX_GCC_std = -std=c++11'

# Disable DTrace, needs patching
LOCAL_CONFIG+='\nVBOX_WITH_DTRACE_R3 ='
LOCAL_CONFIG+='\nVBOX_WITH_DTRACE_R3_MAIN ='
LOCAL_CONFIG+='\nVBOX_WITH_DTRACE_R0DRV ='
LOCAL_CONFIG+='\nVBOX_WITH_DTRACE_RC ='
LOCAL_CONFIG+='\nVBOX_WITH_NATIVE_DTRACE ='

COMPONENT_POST_UNPACK_ACTION = ( cp $(COMPONENT_DIR)/files/Makefile $(COMPONENT_SRC))

COMPONENT_PRE_CONFIGURE_ACTION= \
  ( cd $(@D); echo $(LOCAL_CONFIG) > LocalConfig.kmk; $(CP) -a $(SOURCE_DIR)/* $(@D) )


CONFIGURE_OPTIONS = --with-gcc="$(CC)"
CONFIGURE_OPTIONS+= --with-g++="$(CXX)"
CONFIGURE_OPTIONS+= --build-headless
CONFIGURE_OPTIONS+= --disable-alsa
CONFIGURE_OPTIONS+= --disable-dbus
CONFIGURE_OPTIONS+= --disable-docs
CONFIGURE_OPTIONS+= --disable-pulse
CONFIGURE_OPTIONS+= --disable-python
CONFIGURE_OPTIONS+= --disable-sdl-ttf
CONFIGURE_OPTIONS+= --disable-libvpx
CONFIGURE_OPTIONS+= --nofatal

$(BUILD_64): GMAKE= cd $(@D)/src/VBox/HostDrivers && $(SHELL) -c ". $(@D)/env.sh && kmk"

build:		$(BUILD_64) 

install:	$(INSTALL_64)

test:		$(NO_TESTS)

