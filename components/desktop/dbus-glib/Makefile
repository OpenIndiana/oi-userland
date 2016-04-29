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
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS =            64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		dbus-glib
COMPONENT_VERSION=	0.102
COMPONENT_PROJECT_URL=	http://dbus.freedesktop.org
COMPONENT_ARCHIVE_HASH= \
    sha256:6964ed585bb8149a14ab744b5ded5e77cf71ec5446e6dcc5fcf5eebcc52df29c
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/releases/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/dbus

TPNO=			25523

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
include $(WS_MAKE_RULES)/common.mk

ASLR_MODE = $(ASLR_ENABLE)

CONFIGURE_OPTIONS +=	--sysconfdir="$(ETCDIR)"
CONFIGURE_OPTIONS +=	--libexecdir="$(USRLIB)"
CONFIGURE_OPTIONS +=	--localstatedir="$(VARDIR)"
CONFIGURE_OPTIONS +=	--disable-static
CONFIGURE_OPTIONS += 	--enable-gtk-doc
CONFIGURE_OPTIONS += 	--enable-tests

# Needed for "gmake test" to work successfully.
unexport SHELLOPTS

REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library/dbus
REQUIRED_PACKAGES += system/library/libdbus
