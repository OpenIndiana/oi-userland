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
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS =            64_and_32
# All components using gobject-introspection must be built with gcc as
# gobject-introspection does not produce correct results when using Studio.
COMPILER =              gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gupnp
COMPONENT_VERSION=	0.20.14
COMPONENT_PROJECT_URL=  https://wiki.gnome.org/Projects/GUPnP
COMPONENT_ARCHIVE_HASH= \
	sha256:77ffb940ba77c4a6426d09d41004c75d92652dcbde86c84ac1c847dbd9ad59bd
COMPONENT_BUGDB=        gnome/libraries

TPNO=			25395

# Tests don't work on Solaris yet
TEST_TARGET = $(SKIP_TEST)

# Contains a single Python script written for Python 2.x/3.x; prefer 3.4.
PYTHON=3.4
PYTHON_VERSIONS=3.4

# Needs gobject-introspection and gssdp, not available on S11.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_32_and_64=
INSTALL_32_and_64=
PUBLISH_STAMP=
endif

include $(WS_MAKE_RULES)/gnome-component.mk

# uuid detection fails due to Solaris bug 15586738.
CONFIGURE_OPTIONS += ac_cv_search_uuid_to_string=generic
CONFIGURE_ENV += UUID_CFLAGS="-I/usr/include/uuid"
CONFIGURE_ENV.32 += UUID_LIBS="-luuid"
CONFIGURE_ENV.64 += UUID_LIBS="-L/usr/lib/$(MACH64) -luuid"

CONFIGURE_OPTIONS += --disable-static
# Required for documentation.
CONFIGURE_OPTIONS += --enable-gtk-doc
# Required for other components.
CONFIGURE_OPTIONS += --enable-introspection
CONFIGURE_OPTIONS += --enable-largefile
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --with-pic

REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += developer/vala
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/desktop/gssdp
REQUIRED_PACKAGES += library/libsoup
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += runtime/python-34
