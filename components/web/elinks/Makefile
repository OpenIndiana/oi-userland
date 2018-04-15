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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright 2018 Harry Liebel <hliebel@gmail.com>
#

PREFERRED_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		elinks
COMPONENT_VERSION=	0.11.7
COMPONENT_REVISION=	1
COMPONENT_FMRI=		web/browser/elinks
COMPONENT_PROJECT_URL=	http://elinks.or.cz/
COMPONENT_SUMMARY=	Advanced text-mode WWW browser
COMPONENT_DESCRIPTION=	ELinks is a feature-rich program for browsing the web in text mode.  It is like enhanced Lynx and Links.
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:456db6f704c591b1298b0cd80105f459ff8a1fc07a0ec1156a36c4da6f898979
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)download/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION= Applications/Internet
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE= $(COMPONENT_NAME).license

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

CONFIGURE_OPTIONS += --enable-bittorrent
CONFIGURE_OPTIONS += --enable-html-highlight
CONFIGURE_OPTIONS += --enable-256-colors
CONFIGURE_OPTIONS += --without-gnutls
CONFIGURE_OPTIONS += --without-lua
CONFIGURE_OPTIONS += --without-spidermonkey
CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS) -I/usr/include/js"

ASLR_MODE = $(ASLR_ENABLE)

# common targets
build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
