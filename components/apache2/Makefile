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
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		httpd
COMPONENT_VERSION=	2.2.22
COMPONENT_PROJECT_URL=	http://httpd.apache.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:74c1ffffefe1a502339b004ad6488fbd858eb425a05968cd67c05695dbc0fe7c
COMPONENT_ARCHIVE_URL=	http://archive.apache.org/dist/httpd/$(COMPONENT_ARCHIVE)

CONFIGURE_DEFAULT_DIRS=no

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATCH_LEVEL=0

# Some patches need configure script re-creation.
COMPONENT_PREP_ACTION +=($(CP) mod_sed/* $(@D)/modules/filters);
COMPONENT_PREP_ACTION +=($(CP) mod_auth_gss/mod_auth_gss.c $(@D)/modules/aaa);
COMPONENT_PREP_ACTION +=($(CP) mod_auth_gss/mod_auth_gss.html $(@D)/docs/manual/mod);
COMPONENT_PREP_ACTION +=(cd $(@D); autoreconf);

VARIANT_PREFORK =	$(BUILD_DIR)/prefork
VARIANT_WORKER =	$(BUILD_DIR)/worker

VARIANTS = $(VARIANT_WORKER) $(VARIANT_PREFORK)

BUILD_32 = $(VARIANTS:%=%/$(MACH32)/.built)
BUILD_64 = $(VARIANTS:%=%/$(MACH64)/.built)

INSTALL_32 = $(VARIANTS:%=%/$(MACH32)/.installed)
INSTALL_64 = $(VARIANTS:%=%/$(MACH64)/.installed)

$(VARIANT_PREFORK)/$(MACH64)/.configured: BITS=64
$(VARIANT_WORKER)/$(MACH64)/.configured:  BITS=64

$(VARIANT_PREFORK)/%/.configured: CONFIGURE_OPTIONS += --with-mpm=prefork
$(VARIANT_WORKER)/%/.configured:  CONFIGURE_OPTIONS += --with-mpm=worker

# pipefail wouldn't allow APR-util version check
CONFIGURE_ENV += SHELLOPTS=

CONFIGURE_PREFIX =	/usr/apache2/2.2

CONFIGURE_OPTIONS +=	--enable-mods-shared=all
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
CONFIGURE_OPTIONS +=	--enable-deflate
CONFIGURE_OPTIONS +=	--enable-cgid
CONFIGURE_OPTIONS +=	--enable-cgi
CONFIGURE_OPTIONS +=	--enable-authnz-ldap
CONFIGURE_OPTIONS +=	--enable-ldap
CONFIGURE_OPTIONS +=	--enable-ssl
CONFIGURE_OPTIONS +=	--enable-exception-hook
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS) -DSSL_EXPERIMENTAL -DSSL_ENGINE"
CONFIGURE_OPTIONS +=	LTFLAGS="--silent --tag=CC"
CONFIGURE_OPTIONS.32 +=	--enable-layout=Solaris-Apache2
CONFIGURE_OPTIONS.64 +=	--enable-layout=Solaris-Apache2-$(MACH64)
CONFIGURE_OPTIONS.32 +=	--with-apr=/usr/apr/1.3/bin/apr-1-config
CONFIGURE_OPTIONS.64 +=	--with-apr=/usr/apr/1.3/bin/$(MACH64)/apr-1-config
CONFIGURE_OPTIONS.32 +=	--with-apr-util=/usr/apr-util/1.3/bin/apu-1-config
CONFIGURE_OPTIONS.64 +=	--with-apr-util=/usr/apr-util/1.3/bin/$(MACH64)/apu-1-config

PATH=$(SPRO_VROOT)/bin:/usr/bin:/usr/gnu/bin

build: $(BUILD_32_and_64)

AP_CONFIG_LAYOUT_H=include/ap_config_layout.h

install: $(INSTALL_32_and_64)
	# Some files installed in proto area need to be fixed.
	$(KSH93) Solaris/customization.sh $(PROTO_DIR) $(MACH64)
	# Common header files for 32 and 64 bit variants are needed.
	/usr/bin/diff -D __$(MACH64) \
	  $(VARIANT_PREFORK)/$(MACH32)/$(AP_CONFIG_LAYOUT_H) \
	  $(VARIANT_PREFORK)/$(MACH64)/$(AP_CONFIG_LAYOUT_H) \
	  > $(PROTO_DIR)$(CONFIGURE_PREFIX)/$(AP_CONFIG_LAYOUT_H) ; true

test: $(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
