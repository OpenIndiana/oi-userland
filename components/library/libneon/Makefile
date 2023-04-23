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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
# Copyright 2022 Friedrich Kink
#

BUILD_BITS= 64_and_32
USE_OPENSSL11= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			neon
COMPONENT_VERSION=		0.32.5
COMPONENT_SUMMARY=		Neon is a HTTP and WebDAV client library with a C interface
COMPONENT_PROJECT_URL=	https://notroj.github.io/$(COMPONENT_NAME)
COMPONENT_SRC= 			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 		$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:4872e12f802572dedd4b02f870065814b2d5141f7dbdaf708eedab826b51a58a
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			library/neon
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=		GPLv2

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION += ( $(CLONEY) $(SOURCE_DIR) $(@D); )

CPPFLAGS += $(CPP_LARGEFILES)

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

CONFIGURE_OPTIONS += --localstatedir=/var
CONFIGURE_OPTIONS += --mandir=/usr/share/man
CONFIGURE_OPTIONS += --infodir=/usr/share/info
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-webdav
CONFIGURE_OPTIONS += --enable-threadsafe-ssl=posix
CONFIGURE_OPTIONS += --enable-nls
CONFIGURE_OPTIONS += --disable-warnings
CONFIGURE_OPTIONS += --disable-ld-version-script
CONFIGURE_OPTIONS += --with-zlib
CONFIGURE_OPTIONS += --with-ssl=openssl
CONFIGURE_OPTIONS += --with-libproxy
CONFIGURE_OPTIONS += --with-gssapi
CONFIGURE_OPTIONS += --with-libxml2
CONFIGURE_OPTIONS += --with-expat
CONFIGURE_OPTIONS += --with-pic

COMPONENT_TEST_ENV += PATH="$(PATH.gnu)"
COMPONENT_TEST_TRANSFORMS= \
	' -n ' \
	' -e "/passed/p" ' \
	' -e "/FAIL -/p" ' \
	' -e "/WARNING:/p" ' \
	' -e "/SKIPPED -/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/libproxy
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/gss
