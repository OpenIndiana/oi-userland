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

BUILD_BITS =		64_and_32
USE_OPENSSL11=          yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =	libneon
COMPONENT_VERSION =	0.32.4
COMPONENT_SRC_NAME = 	neon
COMPONENT_SUMMARY=	The Neon WebDAV library
COMPONENT_DESCRIPTION=	An HTTP and WebDAV client library, with a C interface
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_FMRI=		library/neon
COMPONENT_PROJECT_URL=	https://notroj.github.io/$(COMPONENT_SRC_NAME)/
COMPONENT_SRC = $(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE = $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH = sha256:b1e2120e4ae07df952c4a858731619733115c5f438965de4fab41d6bf7e7a508
COMPONENT_ARCHIVE_URL = https://notroj.github.io/$(COMPONENT_SRC_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =     GPLv2
COMPONENT_LICENSE_FILE =$(COMPONENT_NAME).license

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION += (  $(CLONEY) $(SOURCE_DIR) $(@D); )

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
CONFIGURE_OPTIONS += --with-libxml2
CONFIGURE_OPTIONS += --with-expat

COMPONENT_TEST_ENV +=	PATH="$(PATH.gnu)"

# Auto-generated dependencies
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/libproxy
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/gss
