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
# Copyright (c) 2014, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		apache2
COMPONENT_VERSION=	2.4.23
COMPONENT_PROJECT_URL=	http://httpd.apache.org/
COMPONENT_SRC_NAME=	httpd
COMPONENT_ARCHIVE_HASH=	\
    sha256:b71a13f56b8061c6b4086fdcc9ffdddd904449735eadec0f0e2947e33eec91d7
COMPONENT_ARCHIVE_URL=	http://archive.apache.org/dist/httpd/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/apache

TPNO=	30187

CONFIGURE_DEFAULT_DIRS=no
TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# This is baked into the Apache module build configuration and is used by apxs
# to build modules.
LDFLAGS += $(CC_BITS)

PATCH_LEVEL=0

# We will build two separate mod_ssl versions.
COMPONENT_POST_UNPACK_ACTION = (cd $(SOURCE_DIR)/modules; $(CP) -r ssl ssl-fips-140)

# Some patches need configure script re-creation.
COMPONENT_PREP_ACTION +=($(CP) mod_auth_gss/mod_auth_gss.c $(@D)/modules/aaa);
COMPONENT_PREP_ACTION +=($(CP) mod_auth_gss/mod_auth_gss.html $(@D)/docs/manual/mod);
COMPONENT_PREP_ACTION +=(cd $(@D); autoreconf);

CONFIGURE_PREFIX =	$(USRDIR)/apache2/2.4

CONFIGURE_OPTIONS +=	--enable-layout=Solaris
CONFIGURE_OPTIONS +=	--enable-mpms-shared=all
CONFIGURE_OPTIONS +=	--enable-mods-shared=all
# workaround for a known issue with 2.4.23 (should be probably removed with 2.4.24) 
CONFIGURE_OPTIONS +=	--enable-proxy-fdpass
CONFIGURE_OPTIONS +=	--enable-exception-hook
CONFIGURE_OPTIONS +=	--enable-cgi
CONFIGURE_OPTIONS +=	--enable-suexec
CONFIGURE_OPTIONS +=	--with-suexec-caller=webservd
CONFIGURE_OPTIONS +=	--with-apr=$(USRDIR)/apr/1.5/bin/$(MACH64)/apr-1-config
CONFIGURE_OPTIONS +=	--with-apr-util=$(USRDIR)/apr-util/1.5/bin/$(MACH64)/apu-1-config
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS +=	LTFLAGS="--silent --tag=CC"

ifeq   ($(strip $(PARFAIT_BUILD)),yes)
PATH=$(PARFAIT_TOOLS):$(SPRO_VROOT)/bin:$(USRBINDIR):$(GNUBIN)
else
PATH=$(SPRO_VROOT)/bin:$(USRBINDIR):$(GNUBIN)
endif

COMPONENT_POST_INSTALL_ACTION += ($(KSH93) Solaris/customization.sh $(PROTO_DIR))

REQUIRED_PACKAGES += library/apr-15
REQUIRED_PACKAGES += library/apr-util-15
REQUIRED_PACKAGES += library/apr-util-15/apr-ldap
REQUIRED_PACKAGES += library/apr-util-15/dbd-mysql
REQUIRED_PACKAGES += library/apr-util-15/dbd-sqlite
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/nghttp2
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/security/openssl/openssl-fips-140
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += security/kerberos-5
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/gss
REQUIRED_PACKAGES += system/network
REQUIRED_PACKAGES += system/network/ldap/openldap
