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
# Copyright (c) 2023,2024 Friedrich Kink
#

BUILD_BITS=             64
OPENSSL_VERSION=	3.1
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         squid
COMPONENT_VERSION=      6.10
COMPONENT_REVISION=     1
COMPONENT_SUMMARY=      Squid Web Proxy Cache
COMPONENT_DESCRIPTION=	Squid is a caching proxy for the Web supporting HTTP, HTTPS, FTP, and more.
COMPONENT_PROJECT_URL=  https://www.squid-cache.org/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)Versions/v6/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:0b07b187e723f04770dd25beb89aec12030a158696aa8892d87c8b26853408a7
COMPONENT_ARCHIVE_1=    $(COMPONENT_NAME)-langpack-20240307.tar.gz
COMPONENT_ARCHIVE_URL_1=$(COMPONENT_PROJECT_URL)Versions/langpack/$(COMPONENT_ARCHIVE_1)
COMPONENT_ARCHIVE_HASH_1= sha256:5cd2ac5c5aa718090487909d623fa20b076f0bb628a4eff96842c8fa1dd5427f
COMPONENT_FMRI=         web/proxy/squid
COMPONENT_CLASSIFICATION=Web Services/Application and Web Servers
COMPONENT_LICENSE=      GPLv2
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

PATH   = $(PATH.gnu)
CFLAGS += $(CPP_LARGEFILES)

#incorporate official translations
COMPONENT_PREP_ACTION=	( cd $(COMPONENT_SRC)/errors; $(GTAR) xf $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_1))

# Squid has own prefix
CONFIGURE_PREFIX =	/usr/squid

CONFIGURE_BINDIR = $(CONFIGURE_PREFIX)/bin
CONFIGURE_SBINDIR = $(CONFIGURE_PREFIX)/sbin

CONFIGURE_OPTIONS += LDFLAGS="-lldap-2.6"
CONFIGURE_OPTIONS += CPPFLAGS="-I/usr/include/openldap"
CONFIGURE_OPTIONS += --libexecdir=$(CONFIGURE_PREFIX)/libexec
CONFIGURE_OPTIONS += --localstatedir=/var/squid
CONFIGURE_OPTIONS += --sharedstatedir=/var/squid
CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)/squid
CONFIGURE_OPTIONS += --with-swapdir=/var/squid/cache
CONFIGURE_OPTIONS += --mandir=$(CONFIGURE_PREFIX)/man
CONFIGURE_OPTIONS += --with-default-user=webservd
CONFIGURE_OPTIONS += --enable-arp-acl
CONFIGURE_OPTIONS += --enable-auth
CONFIGURE_OPTIONS += --enable-auth-basic
CONFIGURE_OPTIONS += --enable-auth-digest
CONFIGURE_OPTIONS += --enable-auth-negotiate
CONFIGURE_OPTIONS += --enable-auth-ntlm
CONFIGURE_OPTIONS += --enable-basic-auth-helpers='DB,NCSA,YP,LDAP,PAM,getpwnam,MSNT,POP3,multi-domain-NTLM,SMB,SASL'
CONFIGURE_OPTIONS += --enable-cache-digests
CONFIGURE_OPTIONS += --enable-large-cache-files
CONFIGURE_OPTIONS += --enable-carp
CONFIGURE_OPTIONS += --enable-coss-aio-ops
CONFIGURE_OPTIONS += --enable-delay-pools
CONFIGURE_OPTIONS += --enable-digest-auth-helpers='ldap,password'
CONFIGURE_OPTIONS += --enable-external-acl-helpers='delayer,file_userip,session,unix_group,wbinfo_group,LDAP_group'
CONFIGURE_OPTIONS += --enable-follow-x-forwarded-for
CONFIGURE_OPTIONS += --enable-forward-log
CONFIGURE_OPTIONS += --enable-forw-via-db
CONFIGURE_OPTIONS += --enable-htcp
CONFIGURE_OPTIONS += --enable-icmp
CONFIGURE_OPTIONS += --enable-large-cache-files
CONFIGURE_OPTIONS += --enable-multicast-miss
CONFIGURE_OPTIONS += --enable-negotiate-auth-helpers='squid_kerb_auth'
CONFIGURE_OPTIONS += --enable-ntlm-auth-helpers='smb_lm,fakeauth,no_check'
CONFIGURE_OPTIONS += --enable-ntlm-fail-open
CONFIGURE_OPTIONS += --enable-referer-log
CONFIGURE_OPTIONS += --enable-removal-policies='heap,lru'
CONFIGURE_OPTIONS += --enable-snmp
CONFIGURE_OPTIONS += --enable-ssl
CONFIGURE_OPTIONS += --enable-ssl-crtd
#CONFIGURE_OPTIONS += --enable-devpoll
CONFIGURE_OPTIONS += --enable-zph-qos
CONFIGURE_OPTIONS += --enable-icap-client
CONFIGURE_OPTIONS += --with-openssl=$(OPENSSL_PREFIX)
CONFIGURE_OPTIONS += --enable-storeio='aufs,diskd,ufs'
CONFIGURE_OPTIONS += --enable-storeid-rewrite-helpers=file
CONFIGURE_OPTIONS += --enable-inline
CONFIGURE_OPTIONS += --enable-useragent-log
CONFIGURE_OPTIONS += --enable-log-daemon-helpers='DB,file'
CONFIGURE_OPTIONS += --enable-x-accelerator-vary
CONFIGURE_OPTIONS += --enable-translation
CONFIGURE_OPTIONS += --enable-gnuregex
CONFIGURE_OPTIONS += --enable-htpc
CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)/squid

CONFIGURE_OPTIONS += --with-aio
CONFIGURE_OPTIONS += --with-tbd
CONFIGURE_OPTIONS += --with-aufs-threads=8
CONFIGURE_OPTIONS += --with-large-files
CONFIGURE_OPTIONS += --with-build-environment=POSIX_V6_LP64_OFF64
CONFIGURE_OPTIONS += --with-pthreads
# the following option is not documented but without kerberos does not work
CONFIGURE_OPTIONS += --with-solaris-krb5
CONFIGURE_OPTIONS += --with-xml2
CONFIGURE_OPTIONS += --enable-static=no
CONFIGURE_OPTIONS += --without-cap
CONFIGURE_OPTIONS += --without-heimdal-krb5
CONFIGURE_OPTIONS += --without-mit-krb5
CONFIGURE_OPTIONS += --without-gnugss
CONFIGURE_OPTIONS += --without-systemd
CONFIGURE_OPTIONS += --without-gnutls
# These are needed for Cisco integration
CONFIGURE_OPTIONS += --enable-wccp
CONFIGURE_OPTIONS += --enable-wccpv2

COMPONENT_TEST_TARGETS = -k check
COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/=====/p" ' \
	'-e "/squidconf/d" ' \
	'-e "/^\# TOTAL/p" ' \
	'-e "/SKIP/p" ' \
	'-e "/PASS/p" ' \
	'-e "/FAIL/p" ' \
	'-e "/ERROR/p" '

# Build dependencies (manually added)
REQUIRED_PACKAGES += developer/cppunit

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/nettle
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/tdb
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += service/security/kerberos-5
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/gss
REQUIRED_PACKAGES += system/library/security/libsasl
