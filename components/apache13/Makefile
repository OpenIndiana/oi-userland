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

COMPONENT_NAME=		apache
COMPONENT_VERSION=	1.3.41
COMPONENT_PROJECT_URL=	http://httpd.apache.org/
COMPONENT_SUMMARY=	Apache Web Server V1.3
COMPONENT_SRC=		$(COMPONENT_NAME)_$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
   sha256:4b016d3998f822af7a1a515e9626590f5473a4dd5c3e8466f20a6a86a2a63adc
COMPONENT_ARCHIVE_URL=	http://archive.apache.org/dist/httpd/$(COMPONENT_ARCHIVE)

MODSSL_VERSION=2.8.31
COMPONENT_SRC_1= mod_ssl-$(MODSSL_VERSION)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_1=	$(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_URL_1= http://www.modssl.org/source/$(COMPONENT_ARCHIVE_1)
COMPONENT_ARCHIVE_HASH_1= sha256:dc3e7fef57e53a9ab8b1a541d712ea94630ffe5f1d1eb291d5fa19a80c71dd4d
COMPONENT_POST_UNPACK_ACTION_1 += ($(GPATCH) -d $(COMPONENT_SRC_1) $(GPATCH_FLAGS) <  $(PATCH_DIR)/mod_ssl-openssl1.0.patch )
CLEAN_PATHS+=$(COMPONENT_SRC_1)

MODPERL_VERSION=1.31
COMPONENT_SRC_2=mod_perl-$(MODPERL_VERSION)
COMPONENT_ARCHIVE_2=$(COMPONENT_SRC_2).tar.gz
COMPONENT_ARCHIVE_URL_2=https://archive.apache.org/dist/perl/$(COMPONENT_ARCHIVE_2)
COMPONENT_ARCHIVE_HASH_2= sha256:0bc7d2638139b7ac9742e27051513efb332504093eca84488ca15585b14860c1
COMPONENT_POST_UNPACK_ACTION_2 += ($(GPATCH) -d $(COMPONENT_SRC_2) $(GPATCH_FLAGS) <  $(PATCH_DIR)/mod_perl-bug38084.patch ; \
				$(GPATCH) -d $(COMPONENT_SRC_2) $(GPATCH_FLAGS) <  $(PATCH_DIR)/mod_perl-perl5.14.patch )
CLEAN_PATHS+=$(COMPONENT_SRC_2)

MODJK_VERSION=1.2.27
COMPONENT_SRC_3=tomcat-connectors-$(MODJK_VERSION)-src
COMPONENT_ARCHIVE_3=$(COMPONENT_SRC_3).tar.gz
COMPONENT_ARCHIVE_URL_3=http://archive.apache.org/dist/tomcat/tomcat-connectors/jk/source/$(COMPONENT_ARCHIVE_3)
COMPONENT_ARCHIVE_HASH_3= sha256:9ea66964194734a16416303ecc92a3b88b764caf17a6406254109e15d9ad3407
CLEAN_PATHS+=$(COMPONENT_SRC_3)

PATCH_EACH_ARCHIVE=1
PATCHDIR_PATCHES += $(PATCH_DIR)/apache-apachectl.patch
PATCHDIR_PATCHES += $(PATCH_DIR)/apache-getline.patch
PATCHDIR_PATCHES += $(PATCH_DIR)/apache-manpage.patch

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_SSL= $(BUILD_DIR)/.configured_ssl
CONFIGURE_MODPERL= $(BUILD_DIR)/.configured_perl
INSTALL_MODPERL= $(BUILD_DIR)/.installed_modperl
CONFIGURE_TOMCATCON= $(BUILD_DIR)/.configured_tomcatcon
BUILD_TOMCATCON= $(BUILD_DIR)/.built_tomcatcon
INSTALL_TOMCATCON= $(BUILD_DIR)/.installed_tomcatcon
BUILD_AUTH_GSS= $(BUILD_DIR)/.built_auth_gss
INSTALL_AUTH_GSS= $(BUILD_DIR)/.installed_auth_gss
FINAL_CLEANUP= $(BUILD_DIR)/.final_cleanup


# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CP) -a $(SOURCE_DIR)/* $(@D))

CFLAGS += -DUSE_SO_LINGER -DHARD_SERVER_LIMIT=2048 -DSSL_EXPERIMENTAL_PERDIRCA_IGNORE -DSSL_EXPERIMENTAL_PROXY_IGNORE

CONFIGURE_PREFIX =	/usr/apache

CONFIGURE_SCRIPT =	$(@D)/configure

CONFIGURE_OPTIONS =	--prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS +=	--mandir=$(CONFIGURE_PREFIX)/share/man 
CONFIGURE_OPTIONS +=	--bindir=$(CONFIGURE_PREFIX)/bin
CONFIGURE_OPTIONS +=	--sbindir=$(CONFIGURE_PREFIX)/bin
CONFIGURE_OPTIONS +=	--libexecdir=$(CONFIGURE_PREFIX)/libexec
CONFIGURE_OPTIONS +=	--sysconfdir=/etc/apache
CONFIGURE_OPTIONS +=	--datadir=/var/apache
CONFIGURE_OPTIONS +=	--includedir=$(CONFIGURE_PREFIX)/include
CONFIGURE_OPTIONS +=	--cgidir=/var/apache/cgi-bin
CONFIGURE_OPTIONS +=	--localstatedir=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS +=	--runtimedir=/var/run/apache
CONFIGURE_OPTIONS +=	--logfiledir=/var/apache/logs
CONFIGURE_OPTIONS +=	--proxycachedir=/var/apache/proxy
CONFIGURE_OPTIONS +=	--with-perl=$(PERL)
CONFIGURE_OPTIONS +=	--verbose
CONFIGURE_OPTIONS +=	--enable-module=all
CONFIGURE_OPTIONS +=	--enable-module=ssl
CONFIGURE_OPTIONS +=	--enable-shared=ssl
CONFIGURE_OPTIONS +=	--disable-module=auth_db
CONFIGURE_OPTIONS +=	--enable-rule=EAPI
CONFIGURE_OPTIONS +=	--enable-rule=SSL_SDBM
CONFIGURE_OPTIONS +=	--enable-rule=SSL_EXPERIMENTAL
CONFIGURE_OPTIONS +=	--enable-suexec
CONFIGURE_OPTIONS +=	--suexec-caller=nobody
CONFIGURE_OPTIONS +=	--suexec-safepath=/usr/bin
CONFIGURE_OPTIONS +=	--enable-shared=max
CONFIGURE_OPTIONS +=	--activate-module=src/modules/perl/libperl.a
CONFIGURE_OPTIONS +=	--enable-shared=perl

SSL_CONFIGURE_SCRIPT = $(COMPONENT_DIR)/$(COMPONENT_SRC_1)/configure
SSL_CONFIGURE_OPTIONS = --with-apache=$(SOURCE_DIR)
SSL_CONFIGURE_ENV = CC=$(CC)
SSL_CONFIGURE_ENV += CFLAGS="$(CFLAGS) -DPIC -fPIC"
SSL_CONFIGURE_ENV += LDFLAGS="$(LDFLAGS)"
SSL_CONFIGURE_ENV += LDDLFLAGS="$(LDFLAGS) -shared"
SSL_CONFIGURE_ENV += MAKE=$(GMAKE)
SSL_CONFIGURE_ENV += PERL=$(PERL)

AP_PERL5LIB=/usr/apache/perl5/$(PERL_VERSION)/i86pc-solaris
ROOTAP_PERL5LIB = $(PROTO_DIR)/$(AP_PERL5LIB)
MODPERL_CONFIGURE_OPTIONS = INSTALLDIRS=perl
MODPERL_CONFIGURE_OPTIONS += USE_APACI=1
MODPERL_CONFIGURE_OPTIONS += APACHE_SRC=$(SOURCE_DIR)/src
MODPERL_CONFIGURE_OPTIONS += DO_HTTPD=1
MODPERL_CONFIGURE_OPTIONS += PREP_HTTPD=1
MODPERL_CONFIGURE_OPTIONS += EVERYTHING=1
MODPERL_CONFIGURE_OPTIONS += INSTALLSITELIB=$(ROOTAP_PERL5LIB)
MODPERL_CONFIGURE_OPTIONS += INSTALLARCHLIB=$(ROOTAP_PERL5LIB)
MODPERL_CONFIGURE_OPTIONS += INSTALLSITEARCH=$(ROOTAP_PERL5LIB)
MODPERL_CONFIGURE_OPTIONS += INSTALLPRIVLIB=$(ROOTAP_PERL5LIB)
MODPERL_CONFIGURE_OPTIONS += SITEARCHEXP=$(ROOTAP_PERL5LIB)
MODPERL_CONFIGURE_OPTIONS += SITELIBEXP=$(ROOTAP_PERL5LIB)
MODPERL_CONFIGURE_OPTIONS += INSTALLMAN1DIR=$(PROTO_DIR)/usr/apache/man/man1
MODPERL_CONFIGURE_OPTIONS += INSTALLMAN3DIR=$(PROTO_DIR)/usr/apache/man/man3
MODPERL_CONFIGURE_ENV = CC=$(CC)
MODPERL_CONFIGURE_ENV += CFLAGS="$(CFLAGS) -DPIC -fPIC"
MODPERL_CONFIGURE_ENV += LDFLAGS="$(LDFLAGS)"
MODPERL_CONFIGURE_ENV += LDDLFLAGS="$(LDFLAGS) -shared"
MODPERL_CONFIGURE_ENV += MAKE=$(GMAKE)
MODPERL_CONFIGURE_ENV += PERL=$(PERL)

AUTH_GSS_BUILD_ENV =  $(COMPONENT_BUILD_ENV)
AUTH_GSS_BUILD_ENV += CC=$(CC)
AUTH_GSS_BUILD_ENV += LD=$(LD)
AUTH_GSS_BUILD_ENV += MAKE=$(GMAKE)

TOMCATCON_CONFIGURE_SCRIPT = $(BUILD_DIR)/mod_jk/native/configure
TOMCATCON_CONFIGURE_OPTIONS = --with-apxs=$(PROTO_DIR)/usr/apache/bin/apxs
TOMCATCON_CONFIGURE_ENV = CC=$(CC)
TOMCATCON_CONFIGURE_ENV += CFLAGS="$(CFLAGS)"
TOMCATCON_CONFIGURE_ENV += MAKE=$(GMAKE)

PATH=/usr/bin:/usr/gnu/bin

$(BUILD_DIR_32)/.configured:	$(CONFIGURE_SSL) $(CONFIGURE_MODPERL)

$(CONFIGURE_SSL): 	$(SOURCE_DIR)/.prep
	([ -d $(@D)/mod_ssl ] && $(RM) -r $(@D)/mod_ssl; $(MKDIR) $(@D)/mod_ssl)
	$(CLONEY) $(COMPONENT_DIR)/$(COMPONENT_SRC_1) $(@D)/mod_ssl
	(cd $(@D)/mod_ssl; $(ENV) $(SSL_CONFIGURE_ENV) $(CONFIG_SHELL) \
                $(SSL_CONFIGURE_SCRIPT) $(SSL_CONFIGURE_OPTIONS))
	$(TOUCH) $@

$(CONFIGURE_MODPERL):	$(SOURCE_DIR)/.prep
	($(RM) -r $(@D)/mod_perl ; $(MKDIR) $(@D)/mod_perl)
	$(CLONEY) $(COMPONENT_DIR)/$(COMPONENT_SRC_2) $(@D)/mod_perl
	(cd $(@D)/mod_perl ; $(MODPERL_COMPONENT_CONFIGURE_ENV) $(PERL) $(PERL_FLAGS) \
	                        Makefile.PL $(PERL_STUDIO_OVERWRITE) $(MODPERL_CONFIGURE_OPTIONS))
	$(COMPONENT_POST_CONFIGURE_ACTION)
	$(TOUCH) $@

$(CONFIGURE_TOMCATCON): 	$(SOURCE_DIR)/.prep
	([ -d $(@D)/mod_jk ] && $(RM) -r $(@D)/mod_jk; $(MKDIR) $(@D)/mod_jk)
	$(CLONEY) $(COMPONENT_DIR)/$(COMPONENT_SRC_3) $(@D)/mod_jk
	(cd $(@D)/mod_jk/native; $(ENV) $(TOMCATCON_CONFIGURE_ENV) $(CONFIG_SHELL) \
                $(TOMCATCON_CONFIGURE_SCRIPT) $(TOMCATCON_CONFIGURE_OPTIONS))
	$(TOUCH) $@

$(INSTALL_MODPERL):	$(CONFIGURE_MODPERL)
	(cd $(@D)/mod_perl ; $(ENV) $(COMPONENT_BUILD_ENV) \
	        $(GMAKE) install )
	$(TOUCH) $@

$(BUILD_TOMCATCON):	$(CONFIGURE_TOMCATCON) $(INSTALL_32)
	(cd $(@D)/mod_jk/native ; $(ENV) $(COMPONENT_BUILD_ENV) \
		$(GMAKE) )

$(INSTALL_TOMCATCON):	$(BUILD_TOMCATCON)
	$(CP) $(@D)/mod_jk/native/apache-1.3/mod_jk.so $(PROTO_DIR)/usr/apache/libexec
	$(CP) $(COMPONENT_DIR)/Solaris/jk.conf $(PROTO_DIR)/etc/apache
	$(CP) $(COMPONENT_DIR)/Solaris/workers.properties $(PROTO_DIR)/etc/apache
	$(TOUCH) $@

$(BUILD_AUTH_GSS):	$(SOURCE_DIR)/.prep
	([ -d $(@D)/mod_auth_gss ] && $(RM) -r $(@D)/mod_auth_gss; $(MKDIR) $(@D)/mod_auth_gss)
	$(CLONEY) $(COMPONENT_DIR)/mod_auth_gss $(@D)/mod_auth_gss
	(cd $(@D)/mod_auth_gss ; $(ENV) $(AUTH_GSS_BUILD_ENV) \
	        $(GMAKE) SERVER=$(SOURCE_DIR) all )
	$(TOUCH) $@

$(INSTALL_AUTH_GSS):	$(BUILD_AUTH_GSS)
	(cd $(@D)/mod_auth_gss ; $(ENV) $(AUTH_GSS_BUILD_ENV) \
	        $(GMAKE) SERVER=$(SOURCE_DIR) DESTDIR=$(PROTO_DIR) install )
	$(TOUCH) $@

$(FINAL_CLEANUP):	$(INSTALL_32) $(INSTALL_TOMCATCON) $(INSTALL_AUTH_GSS)
	$(GSED) -f $(COMPONENT_DIR)/Solaris/httpdconf.sed -i $(PROTO_DIR)/etc/apache/httpd.conf
	$(RM) $(PROTO_DIR)/etc/apache/*.default
	$(TOUCH) $@


$(BUILD_32):	$(INSTALL_MODPERL)

COMPONENT_INSTALL_ARGS += root=$(PROTO_DIR)

build: $(BUILD_32) $(BUILD_AUTH_GSS)

install: $(INSTALL_32) $(INSTALL_TOMCATCON) $(INSTALL_AUTH_GSS) $(FINAL_CLEANUP)

test: $(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
