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
# Copyright (c) 2015, 2017, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		uhttpmock
COMPONENT_VERSION=	0.5.3
COMPONENT_REVISION=	2
COMPONENT_SUMMARY=	A library for mocking web service APIs which use HTTP or HTTPS
COMPONENT_PROJECT_URL=	https://gitlab.com/uhttpmock/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:90843223c3a30bdb7f1eb3442373a03fee425af85a9df289cd687698ccff112f
COMPONENT_ARCHIVE_URL=	https://tecnocode.co.uk/downloads/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_FMRI=	library/uhttpmock
COMPONENT_LICENSE= LGPLv2.1
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = (cd $(@D) && autoreconf -fi)

# Tell g-ir-scanner not to cache results in homedir of user running the build
COMPONENT_BUILD_ENV += GI_SCANNER_DISABLE_CACHE=""

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-gtk-doc
# Required for other components.
CONFIGURE_OPTIONS += --enable-introspection
CONFIGURE_OPTIONS += --enable-shared
# Required for other components.
CONFIGURE_OPTIONS += --enable-vala
CONFIGURE_OPTIONS += --with-pic

COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

COMPONENT_TEST_ARGS =   -k -i
COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/TOTAL:/p" ' \
	'-e "/SKIP:/p" ' \
	'-e "/PASS:/p" ' \
	'-e "/FAIL:/p" ' \
	'-e "/ERROR:/p" ' \
	'-e "/  \//p" ' \

# Build dependencies
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libsoup
REQUIRED_PACKAGES += system/library
