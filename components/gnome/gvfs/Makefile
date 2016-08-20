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

BUILD_BITS =            32_and_64
COMPILER =              gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gvfs
COMPONENT_VERSION=	1.26.0
COMPONENT_PROJECT_URL=  https://wiki.gnome.org/Projects/gvfs
COMPONENT_ARCHIVE_HASH= \
	sha256:6d43e8b33a5c1588525875f9d3979b515f648da1d567d0ce3d337a18f5ff8c32
COMPONENT_BUGDB=	gnome/libraries

TPNO=			25202

# Needs updated glib2, not available on S11.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_32_and_64=
INSTALL_32_and_64=
PUBLISH_STAMP=
endif

include $(WS_MAKE_RULES)/gnome-component.mk

# Assumes GNU xgettext in PATH.
CONFIGURE_ENV += PATH=$(GNUBIN):$(PATH)

# Requires a reconf due to 01-major-minor.patch changing configure.ac.
COMPONENT_PREP_ACTION += (cd $(@D); autoreconf -iv);

# Assumes GNU xgettext is first in $PATH.
COMPONENT_BUILD_ENV += PATH="$(GNUBIN):$(PATH)"

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-archive
CONFIGURE_OPTIONS += --enable-avahi
CONFIGURE_OPTIONS += --enable-bash-completion
CONFIGURE_OPTIONS += --enable-documentation
CONFIGURE_OPTIONS += --enable-goa
CONFIGURE_OPTIONS += --disable-gphoto2
CONFIGURE_OPTIONS += --enable-gtk
CONFIGURE_OPTIONS += --enable-http
CONFIGURE_OPTIONS += --enable-keyring
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --with-pic

REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/libsecret
REQUIRED_PACKAGES += library/libarchive
REQUIRED_PACKAGES += library/libsoup
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library/security/libgcrypt
REQUIRED_PACKAGES += system/network/avahi
REQUIRED_PACKAGES += library/gnome/gcr
