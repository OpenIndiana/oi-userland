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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2019, Michal Nowak
# Copyright (c) 2023, Niklas Poslovski
#

USE_OPENSSL11= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		apache2
COMPONENT_VERSION=	2.4.55
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	https://httpd.apache.org/
COMPONENT_SRC_NAME=	httpd
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:5276ea8bc6fff31eed5c82132ae51a0b2ee05f9e6b61a00fa877f6cadab3b638
COMPONENT_ARCHIVE_URL=	https://archive.apache.org/dist/httpd/$(COMPONENT_ARCHIVE)

CONFIGURE_DEFAULT_DIRS=no

TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATCH_LEVEL=0

# Some patches need configure script re-creation.
COMPONENT_PREP_ACTION +=($(CP) mod_auth_gss/mod_auth_gss.c $(@D)/modules/aaa);
COMPONENT_PREP_ACTION +=($(CP) mod_auth_gss/mod_auth_gss.html $(@D)/docs/manual/mod);
COMPONENT_PREP_ACTION +=(cd $(@D); autoreconf);

CFLAGS += -DSSL_EXPERIMENTAL -DSSL_ENGINE

# pipefail wouldn't allow APR-util version check
CONFIGURE_ENV += SHELLOPTS=

CONFIGURE_PREFIX =	/usr/apache2/2.4

CONFIGURE_OPTIONS +=	--enable-mods-shared=all
CONFIGURE_OPTIONS +=	--enable-mpms-shared=all
CONFIGURE_OPTIONS +=	--enable-so
CONFIGURE_OPTIONS +=	--enable-suexec
CONFIGURE_OPTIONS +=	--with-suexec-caller=webservd
CONFIGURE_OPTIONS +=	--enable-proxy
CONFIGURE_OPTIONS +=	--enable-proxy-connect
CONFIGURE_OPTIONS +=	--enable-proxy-ftp
CONFIGURE_OPTIONS +=	--enable-proxy-http
CONFIGURE_OPTIONS +=	--enable-proxy-ajp
CONFIGURE_OPTIONS +=	--enable-proxy-balancer
CONFIGURE_OPTIONS +=	--enable-cache
CONFIGURE_OPTIONS +=	--enable-file-cache
CONFIGURE_OPTIONS +=	--enable-disk-cache
CONFIGURE_OPTIONS +=	--enable-mem-cache
CONFIGURE_OPTIONS +=	--enable-brotli
CONFIGURE_OPTIONS +=	--enable-deflate
CONFIGURE_OPTIONS +=	--enable-cgid
CONFIGURE_OPTIONS +=	--enable-cgi
CONFIGURE_OPTIONS +=	--enable-authnz-ldap
CONFIGURE_OPTIONS +=	--enable-ldap
CONFIGURE_OPTIONS +=	--enable-ssl
CONFIGURE_OPTIONS +=	--enable-exception-hook
CONFIGURE_OPTIONS +=	LTFLAGS="--silent --tag=CC"
CONFIGURE_OPTIONS +=	--enable-layout=Solaris-Apache2
CONFIGURE_OPTIONS +=	CC="$(CC) -m$(BITS)"
CONFIGURE_OPTIONS +=	--with-apr=/usr/apr/bin/apr-1-config
CONFIGURE_OPTIONS +=	--with-apr-util=/usr/apr-util/bin/apu-1-config

install: $(INSTALL_64)
	# Some files installed in proto area need to be fixed.
	$(KSH93) Solaris/customization.sh $(PROTO_DIR)
	$(TOUCH) $(BUILD_DIR)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/apr
REQUIRED_PACKAGES += library/apr-util
REQUIRED_PACKAGES += library/apr-util/apr-ldap
REQUIRED_PACKAGES += library/apr-util/dbd-mysql
REQUIRED_PACKAGES += library/apr-util/dbd-sqlite
REQUIRED_PACKAGES += library/brotli
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/nghttp2
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/pcre2
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/gss
