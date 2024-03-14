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

BUILD_BITS= 64_and_32
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= dbus
COMPONENT_VERSION= 1.14.10
COMPONENT_SUMMARY= Simple IPC library based on messages
COMPONENT_PROJECT_URL= https://dbus.freedesktop.org
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:ba1f21d2bd9d339da2d4aa8780c09df32fea87998b73da24f49ab9df1e36a50f
COMPONENT_ARCHIVE_URL= $(COMPONENT_PROJECT_URL)/releases/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL= $(COMPONENT_ARCHIVE_URL).asc
COMPONENT_FMRI= system/library/dbus
COMPONENT_CLASSIFICATION= System/Services
COMPONENT_LICENSE= dbus, GPLv2

# https://release-monitoring.org/api/project/$(COMPONENT_ANITYA_ID) will answer a JSON object with project information
COMPONENT_ANITYA_ID= 5356

include $(WS_MAKE_RULES)/common.mk

# Needed for "gmake test" to work successfully.
unexport SHELLOPTS

# Will break parallel 32/64-bit builds; needs update when that happens.
CONFIGURE_BINDIR.32 = $(CONFIGURE_PREFIX)/bin

CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --with-dbus-daemondir=$(USRLIBEXECDIR)
CONFIGURE_OPTIONS += --with-dbus-user=root
CONFIGURE_OPTIONS += --libexecdir=$(USRLIBEXECDIR)
CONFIGURE_OPTIONS += --localstatedir=$(VARDIR)
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-xml-docs		# needs text/xmlto
CONFIGURE_OPTIONS += --enable-doxygen-docs	# needs developer/documentation-tool/doxygen 
CONFIGURE_OPTIONS += --enable-evports
CONFIGURE_OPTIONS += --enable-year2038
# enable-tests activates more tests but is said to be unsafe for deployments. Thus, we don't use it here.
#CONFIGURE_OPTIONS += --enable-tests

# Makefile.am files of this component are not compatible with Solaris make.
# Use GNU make to avoid the configuration error when makefile fragments are processed.
CONFIGURE_OPTIONS += MAKE=$(GMAKE)

# GNU Build System files have to be regenerated for automake 1.16.
# It can be removed when the upstream starts to use a newer automake version.
COMPONENT_PREP_ACTION= ( cd $(@D) && PATH="$(PATH)" autoreconf -fiv )

# Manually added build dependencies
REQUIRED_PACKAGES += developer/build/autoconf-archive
REQUIRED_PACKAGES += developer/documentation-tool/doxygen
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += text/xmlto

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
