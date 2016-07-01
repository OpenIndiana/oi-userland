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

BUILD_BITS =           32_and_64
# All components using gobject-introspection must be built with gcc as
# gobject-introspection does not produce correct results when using Studio.
COMPILER =		gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		librsvg
COMPONENT_VERSION=	2.40.12
COMPONENT_MAJOR_MINOR=	$(basename $(COMPONENT_VERSION))
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Projects/LibRsvg
COMPONENT_ARCHIVE_HASH=	\
    sha256:ffe40c4378bf3899f4d679a475726bab03a127a5bdccddec86404cc329ffb550
COMPONENT_BUGDB=        library/librsvg

TPNO=			26339

# Needs gobject-introspection, not available on S11.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_32_and_64=
INSTALL_32_and_64=
PUBLISH_STAMP=
endif

include $(WS_MAKE_RULES)/gnome-component.mk

CONFIGURE_OPTIONS += --disable-Bsymbolic
CONFIGURE_OPTIONS += --disable-static
# Required for other components.
CONFIGURE_OPTIONS += --enable-introspection
CONFIGURE_OPTIONS += --enable-vala

# Requires a reconf due to patch to configure.ac.
COMPONENT_PREP_ACTION += (cd $(@D); autoreconf -fiv);

# for the tests
unexport SHELLOPTS
# Ignore whether the test code was already built or not
COMPONENT_TEST_TRANSFORMS += "-e '/^  CC.*/d'"
COMPONENT_TEST_TRANSFORMS += "-e '/^make.* is up to date\.$$/d'"

REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += developer/vala
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libcroco
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/python-34
REQUIRED_PACKAGES += system/library/math
