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
USE_PARALLEL_BUILD= yes
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= dbus
COMPONENT_VERSION= 1.16.2
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

# https://release-monitoring.org/api/project/$(COMPONENT_ANITYA_ID) will answer a JSON object with project information
COMPONENT_ANITYA_ID= 5356

include $(WS_MAKE_RULES)/common.mk

CFLAGS += $(XPG6MODE)
CPPFLAGS += -D_REENTRANT

# Will break parallel 32/64-bit builds; needs update when that happens.
CONFIGURE_BINDIR.32 = $(CONFIGURE_PREFIX)/bin

CONFIGURE_OPTIONS += -Ddbus_daemondir=$(USRLIBEXECDIR)
CONFIGURE_OPTIONS += -Druntime_dir=/var/run
CONFIGURE_OPTIONS += -Ddbus_user=root
CONFIGURE_OPTIONS += -Depoll=disabled
CONFIGURE_OPTIONS += -Dinotify=disabled
CONFIGURE_OPTIONS += -Dc_link_args=-lsocket

# enable-tests activates more tests but is said to be unsafe for deployments. Thus, we don't use it here.
#CONFIGURE_OPTIONS += --enable-tests

# Manually added build dependencies
REQUIRED_PACKAGES += developer/documentation-tool/doxygen
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += text/xmlto

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/expat/32
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
