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
# Copyright (c) 2016, 2017, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS=	    	64
COMPILER=      	       	gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		vinagre
COMPONENT_VERSION=	3.16.0
COMPONENT_PROJECT_URL=  https://wiki.gnome.org/Projects//$(COMPONENT_NAME)
COMPONENT_ARCHIVE_HASH= \
	sha256:93d79e18e71509647fe4bc00a0dcef5382b2e3a79c39d2b18a91334195995c34
COMPONENT_BUGDB=	gnome/remote-desktop

TPNO=			26597

# Needs updated glib2, not available on S11.
include $(WS_MAKE_RULES)/no-evaluation.mk

include $(WS_MAKE_RULES)/gnome-component.mk

# Requires XPG4 or later & C99 compatibility, thus XPG6 or later
CFLAGS += $(XPG6MODE)

# Assumes GNU versions of utilities in PATH (e.g. xgettext).
CONFIGURE_ENV += PATH="$(GNUBIN):$(PATH)"
COMPONENT_BUILD_ENV += PATH="$(GNUBIN):$(PATH)"

# RDP support requires freerdp
CONFIGURE_OPTIONS += --disable-rdp
CONFIGURE_OPTIONS += --with-telepathy=yes

REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk-vnc
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/libsecret
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/telepathy-glib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus-glib
