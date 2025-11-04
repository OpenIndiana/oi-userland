#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2016, 2023, Oracle and/or its affiliates.
#

BUILD_STYLE= meson
BUILD_BITS= 64_and_32
USE_DEFAULT_TEST_TRANSFORMS= yes
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= dbus
COMPONENT_VERSION= 1.16.2
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= Simple IPC library based on messages
COMPONENT_PROJECT_URL= https://dbus.freedesktop.org
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:0ba2a1a4b16afe7bceb2c07e9ce99a8c2c3508e5dec290dbb643384bd6beb7e2
COMPONENT_ARCHIVE_URL= $(COMPONENT_PROJECT_URL)/releases/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL= $(COMPONENT_ARCHIVE_URL).asc
COMPONENT_FMRI= system/library/dbus
COMPONENT_CLASSIFICATION= System/Services
COMPONENT_LICENSE= dbus, GPLv2

COMPONENT_FMRI.dbus-x11 =	$(COMPONENT_FMRI)/dbus-x11
COMPONENT_SUMMARY.dbus-x11 =	$(COMPONENT_SUMMARY) - X11

COMPONENT_FMRI.libdbus =	system/library/libdbus
COMPONENT_SUMMARY.libdbus =	$(COMPONENT_SUMMARY)

COMPONENT_FMRI.libdbus-32 =	$(COMPONENT_FMRI.libdbus)/32
COMPONENT_SUMMARY.libdbus-32 =	$(COMPONENT_SUMMARY.libdbus) (32-bit)

# https://release-monitoring.org/api/project/$(COMPONENT_ANITYA_ID) will answer a JSON object with project information
COMPONENT_ANITYA_ID= 5356

include $(WS_MAKE_RULES)/common.mk

CFLAGS += $(XPG6MODE)
CPPFLAGS += -D_REENTRANT

CONFIGURE_OPTIONS += -Druntime_dir=$(VARDIR)/run
CONFIGURE_OPTIONS += -Ddbus_user=root
CONFIGURE_OPTIONS += -Depoll=disabled
CONFIGURE_OPTIONS += -Dinotify=disabled
CONFIGURE_OPTIONS += -Dc_link_args=-lsocket

# We do not need to build these for 32-bit.  They are either overwritten by the
# 64-bit build, or unused.
CONFIGURE_OPTIONS.32 += -Ddoxygen_docs=disabled
CONFIGURE_OPTIONS.32 += -Dtools=false
CONFIGURE_OPTIONS.32 += -Dtraditional_activation=false
CONFIGURE_OPTIONS.32 += -Dxml_docs=disabled

# enable-tests activates more tests but is said to be unsafe for deployments. Thus, we don't use it here.
#CONFIGURE_OPTIONS += --enable-tests

# Drop 32-bit binaries and files that will be overwritten by 64-bit build
# anyway.
COMPONENT_POST_INSTALL_ACTION.32 += $(RM) -r $(PROTOUSRBINDIR32) ;
COMPONENT_POST_INSTALL_ACTION.32 += $(RM) -r $(PROTOETCDIR) ;
COMPONENT_POST_INSTALL_ACTION.32 += $(RM) -r $(PROTOUSRINCDIR) ;
COMPONENT_POST_INSTALL_ACTION.32 += $(RM) -r $(PROTOUSRSHAREDIR) ;

# Install additional files
COMPONENT_POST_INSTALL_ACTION.64 += $(INSTALL) -Dt $(PROTOETCDIR)/X11/xinit/xinitrc.d $(COMPONENT_DIR)/files/0070.dbus ;
COMPONENT_POST_INSTALL_ACTION.64 += $(INSTALL) -D $(COMPONENT_DIR)/files/auth_attr $(PROTOETCSECDIR)/auth_attr.d/system:library:dbus ;
COMPONENT_POST_INSTALL_ACTION.64 += $(INSTALL) -D $(COMPONENT_DIR)/files/prof_attr $(PROTOETCSECDIR)/prof_attr.d/system:library:dbus ;
COMPONENT_POST_INSTALL_ACTION.64 += $(INSTALL) -Dt $(PROTOLIBDIR)/svc/manifest/system $(COMPONENT_DIR)/files/dbus.xml ;
COMPONENT_POST_INSTALL_ACTION.64 += $(INSTALL) -Dt $(PROTOLIBDIR)/svc/method $(COMPONENT_DIR)/files/svc-dbus ;
COMPONENT_POST_INSTALL_ACTION.64 += $(INSTALL) -Dt $(PROTOUSRSHAREMANDIR)/man3lib $(COMPONENT_DIR)/files/libdbus-1.3lib ;

# Manually added build dependencies
REQUIRED_PACKAGES += developer/documentation-tool/doxygen
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += text/xmlto

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
