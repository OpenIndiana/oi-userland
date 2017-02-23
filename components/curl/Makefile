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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME =        curl
COMPONENT_VERSION=      7.45.0
COMPONENT_PROJECT_URL=  http://curl.haxx.se/
COMPONENT_ARCHIVE_HASH= \
    sha256:02c78c8060d587422e2826f622c729189b56084bba365140f13af3d402b6cb6b
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)download/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/curl
COMPONENT_ANITYA_ID=	381

TPNO=			25724

include $(WS_MAKE_RULES)/common.mk

PATCH_LEVEL = 0

CFLAGS += $(CPP_LARGEFILES)
CFLAGS += `pkg-config --cflags libidn`
CPPFLAGS += `pkg-config --cflags libidn`
CPPFLAGS += "-I/usr/include/openldap"

# Enable adiheap and adistack security extensions
ADIHEAP_MODE =	$(ADIHEAP_ENABLE)
ADISTACK_MODE =	$(ADISTACK_ENABLE)

CONFIGURE_OPTIONS += --localstatedir=$(VARDIR) --enable-shared --disable-static
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
CONFIGURE_OPTIONS += --with-ssl --with-ldap-lib=ldap_r-2.4
CONFIGURE_OPTIONS += --with-lber-lib=lber-2.4
CONFIGURE_OPTIONS += --with-gssapi-includes=$(USRINCDIR)/gssapi
CONFIGURE_OPTIONS += --with-gssapi-libs=$(USRLIB)
CONFIGURE_OPTIONS += --with-gssapi=$(USRDIR) --without-ca-bundle
CONFIGURE_OPTIONS += --with-ca-path=$(ETCDIR)/openssl/certs
CONFIGURE_OPTIONS += --with-zlib=$(USRDIR) --with-libidn=$(USRDIR)
CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS += --with-libssh2
CONFIGURE_OPTIONS += --with-nghttp2
CONFIGURE_OPTIONS += "curl_disallow_getifaddrs=yes"

LINT_FLAGS += -I$(SOURCE_DIR)/include

# The additional curl specific set of transforms to be applied to the
# test results to try to normalize them.
COMPONENT_TEST_TRANSFORMS += \
	'-e "s|^.*$(CC).*$$|XXX_CC_XXX|g" ' \
	'-e "s|^.*source=.*libtool=no.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^.*DEPDIR=.deps.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^make.*: Leaving directory.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^make.*: Entering directory.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^make.*: Nothing to be done for.*$$|XXX_CC_XXX|g" ' \
	'-e "/^XXX_CC_XXX$$/d" ' \
	'-e "s|\(^/bin/bash ../../libtool\).*|\1|" ' \
	'-e "s|\(^libtool: link:\).*|\1|" ' \
	'-e "s|remaining: ..:..|remaining: xx:xx|" ' \
	'-e "s|\(^TESTDONE: 994 tests were considered during\).*|\1|" ' \
	'-e "s|\(^\* curl $(COMPONENT_VERSION)\).*|\1|" ' \
	'-e "s|\(^\* Host:\).*|\1|" ' \
	'-e "s|\(^\* System: SunOS\).*|\1|" ' \
	'-e "s|\(^Connection from 127.0.0.1 port\).*|\1|" ' \
	'-e "s|\(^Failed none for\).*|\1|" ' \
	'-e "s|\(^Found matching DSA key:\).*|\1|" ' \
	'-e "s|\(^Failed publickey for\).*|\1|" ' \
	'-e "/^debug.:/d" ' \
	'-e "/^monitor debug.:/d" '

REQUIRED_PACKAGES += library/libidn
REQUIRED_PACKAGES += library/libssh2
REQUIRED_PACKAGES += library/nghttp2
$(SOLARIS_11_ONLY)REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += security/kerberos-5
REQUIRED_PACKAGES += shell/ksh93
ifeq ($(OS_VERSION),5.11)
REQUIRED_PACKAGES += system/library/security/gss
endif
REQUIRED_PACKAGES += system/network/ldap/openldap
