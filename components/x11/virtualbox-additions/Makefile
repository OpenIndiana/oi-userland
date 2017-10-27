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
COMPONENT_VERSION=      5.2.0
COMPONENT_SUMMARY=      VirtualBox - Guest Additions 
COMPONENT_PROJECT_URL=  http://www.virtualbox.org/
COMPONENT_FMRI=         system/virtualization/virtualbox-additions
COMPONENT_CLASSIFICATION= System/Virtualization
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_URL= \
  http://download.virtualbox.org/virtualbox/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE) 
COMPONENT_ARCHIVE_HASH= \
  sha256:26fc73aee2df18142e4129beed1175fbd7eed69a9b6b150bcff7d9b92f4ade54
COMPONENT_LICENSE=      GPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

X11_SERVERMODS_DIR=/usr/lib/xorg/modules
X11_SERVERLIBS_DIR=/usr/lib/xorg

CONFIGURE_SCRIPT=$(@D)/configure

# Build for the system Xorg (only possibility for 1.19) or for any guest up to 1.18
USE_SYSTEM_X11=1

LOCAL_CONFIG+='\nVBOX_ONLY_ADDITIONS = 1'
LOCAL_CONFIG+='\nVBOX_WITH_DRAG_AND_DROP_GH = 1'
LOCAL_CONFIG+='\nVBOX_WITH_X11_ADDITIONS = 1'
LOCAL_CONFIG+='\nVBOX_GCC_std = -std=c++11'
LOCAL_CONFIG+='\nSDK_VBOX_OPENSSL_INCS = /usr/include/openssl'

ifeq ($(strip $(USE_SYSTEM_X11)), 1)
LOCAL_CONFIG+='\nVBOX_USE_SYSTEM_XORG_HEADERS = $(USE_SYSTEM_X11)'
LOCAL_CONFIG+='\nVBOX_USE_SYSTEM_GL_HEADERS = $(USE_SYSTEM_X11)'
endif

COMPONENT_PRE_CONFIGURE_ACTION= \
  ( cd $(@D); echo $(LOCAL_CONFIG) > LocalConfig.kmk; $(CP) -a $(SOURCE_DIR)/* $(@D) )

GMAKE= $(SHELL) -c '. env.sh && kmk'
COMPONENT_BUILD_GMAKE_ARGS=
COMPONENT_BUILD_ARGS=
COMPONENT_BUILD_TARGETS=

CONFIGURE_OPTIONS = --with-gcc="$(CC)"
CONFIGURE_OPTIONS+= --with-g++="$(CXX)"
CONFIGURE_OPTIONS+= --disable-alsa
CONFIGURE_OPTIONS+= --disable-docs
CONFIGURE_OPTIONS+= --disable-python
CONFIGURE_OPTIONS+= --disable-xpcom
CONFIGURE_OPTIONS+= --only-additions

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

