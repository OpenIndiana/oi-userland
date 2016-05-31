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

BUILD_BITS = 64_and_32
COMPILER=gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libnotify
COMPONENT_VERSION=	0.7.6
COMPONENT_ARCHIVE_HASH=	\
	sha256:0ef61ca400d30e28217979bfa0e73a7406b19c32dd76150654ec5b2bdf47d837
COMPONENT_BUGDB=        gnome/libraries

TPNO=			24758

# Tests do not work on Solaris yet
TEST_TARGET= $(SKIP_TEST)

include $(WS_MAKE_RULES)/gnome-component.mk

CONFIGURE_OPTIONS += --includedir=/usr/include/$(COMPONENT_NAME)-4/
CONFIGURE_OPTIONS.32 += --libdir=/usr/lib/$(COMPONENT_NAME)-4/
CONFIGURE_OPTIONS.64 += --libdir=/usr/lib/$(MACH64)/$(COMPONENT_NAME)-4/

CONFIGURE_OPTIONS += --disable-static
# Required for other components.
CONFIGURE_OPTIONS += --program-suffix=-4
CONFIGURE_OPTIONS += --enable-introspection
CONFIGURE_OPTIONS += --disable-docbook-docs
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --with-pic

# Required due to patches.
COMPONENT_PREP_ACTION += (cd $(@D); autoreconf -fiv);

REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += developer/documentation-tool/xmlto
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/glib2
