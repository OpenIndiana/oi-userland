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
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME =        curl
COMPONENT_VERSION=      7.26.0
COMPONENT_REVISION=	1
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  http://curl.haxx.se/
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:79ccce9edb8aee17d20ad4d75e1f83a789f8c2e71e68f468e1bf8abf8933193f
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)download/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/curl

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATCH_LEVEL = 0

GSSAPI_LIBDIR_32 = /usr/lib
GSSAPI_LIBDIR_64 = /usr/lib/$(MACH64)

CFLAGS += $(CPP_LARGEFILES)
CFLAGS += `pkg-config --cflags libidn`
CPPFLAGS += `pkg-config --cflags libidn`

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

CONFIGURE_OPTIONS += --localstatedir=/var --enable-shared --disable-static
CONFIGURE_OPTIONS += --enable-http --enable-ftp
CONFIGURE_OPTIONS += --enable-file --enable-dict
CONFIGURE_OPTIONS += --enable-manual --disable-libgcc
CONFIGURE_OPTIONS += --enable-rtsp --enable-proxy
CONFIGURE_OPTIONS += --enable-telnet --enable-tftp --enable-pop3
CONFIGURE_OPTIONS += --enable-imap --enable-smtp
CONFIGURE_OPTIONS += --enable-ipv6 --enable-nonblocking
CONFIGURE_OPTIONS += --enable-thread --enable-verbose
CONFIGURE_OPTIONS += --disable-sspi --enable-crypto-auth
CONFIGURE_OPTIONS += --enable-cookies --disable-hidden-symbols
CONFIGURE_OPTIONS += --disable-soname-bump
CONFIGURE_OPTIONS += --enable-ldap --with-random=/dev/urandom
CONFIGURE_OPTIONS += --with-ssl --with-ldap-lib=ldap
CONFIGURE_OPTIONS += --with-lber-lib=sldap
CONFIGURE_OPTIONS += --with-gssapi-includes=/usr/include/gssapi
CONFIGURE_OPTIONS += --with-gssapi-libs=$(GSSAPI_LIBDIR_$(BITS))
CONFIGURE_OPTIONS += --with-gssapi=/usr --without-ca-bundle
CONFIGURE_OPTIONS += --with-ca-path=/etc/openssl/certs
CONFIGURE_OPTIONS += --with-zlib=/usr --with-libidn=/usr
CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS += --without-libssh2
CONFIGURE_OPTIONS += "curl_disallow_getifaddrs=yes"

LINT_FLAGS += -I$(SOURCE_DIR)/include

ASLR_MODE = $(ASLR_ENABLE)

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include ../../make-rules/depend.mk

