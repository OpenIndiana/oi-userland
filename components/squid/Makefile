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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
COMPILER= gcc
include ../../make-rules/shared-macros.mk

PATH=$(USRBINDIR):$(GNUBIN):$(USRSBINDIR):$(USRDIR)/perl5/bin

COMPONENT_NAME=         squid
COMPONENT_VERSION=      3.5.18
COMPONENT_PROJECT_URL=  http://www.squid-cache.org/
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
    sha256:812ba5ec74ebdc1bea1b3013b636f9dfcb7a6f5271b2783961009c215879af82
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)Versions/v3/3.5/$(COMPONENT_ARCHIVE)

TPNO=			28337

# Enable adiheap and adistack security extensions
ADIHEAP_MODE =	$(ADIHEAP_ENABLE)
ADISTACK_MODE =	$(ADISTACK_ENABLE)

TEST_TARGET= $(TEST_64)
include $(WS_MAKE_RULES)/common.mk

# Look for gnutls-3 pkg-config & libraries before the defaults
PKG_CONFIG_PATH.64 := $(PKG_CONFIG_PATH.64)/gnutls-3:$(PKG_CONFIG_PATH.64)
LDFLAGS += -L$(USRLIBDIR64)/gnutls-3

CFLAGS += -I$(USRINCDIR)/kerberosv5
CFLAGS += $(CPP_LARGEFILES)
# <getopt.h> changed between 11 & 12.
ifeq ($(OS_VERSION), 5.11)
CXXFLAGS +=	-Wno-write-strings
endif

CONFIGURE_LIBDIR.64 =	$(CONFIGURE_PREFIX)/lib

# Squid has own prefix
CONFIGURE_PREFIX =	$(USRDIR)/squid

CONFIGURE_OPTIONS += --libexecdir=$(CONFIGURE_PREFIX)/libexec
CONFIGURE_OPTIONS += --localstatedir=$(VARDIR)/squid
CONFIGURE_OPTIONS += --sharedstatedir=$(VARDIR)/squid
CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)/squid
CONFIGURE_OPTIONS += --mandir=$(CONFIGURE_PREFIX)/man
CONFIGURE_OPTIONS += --sbindir=$(CONFIGURE_PREFIX)/sbin
CONFIGURE_OPTIONS += --enable-arp-acl
CONFIGURE_OPTIONS += --enable-auth-basic='DB,NCSA,NIS,LDAP,PAM,getpwnam,MSNT-multi-domain,POP3,SMB,SMB_LM,SASL'
CONFIGURE_OPTIONS += --enable-cache-digests
CONFIGURE_OPTIONS += --enable-carp
CONFIGURE_OPTIONS += --enable-coss-aio-ops
CONFIGURE_OPTIONS += --enable-delay-pools
CONFIGURE_OPTIONS += --enable-auth-digest='file,LDAP'
CONFIGURE_OPTIONS += --enable-external-acl-helpers='file_userip,unix_group,LDAP_group,wbinfo_group'
CONFIGURE_OPTIONS += --enable-follow-x-forwarded-for
CONFIGURE_OPTIONS += --enable-forward-log
CONFIGURE_OPTIONS += --enable-forw-via-db
CONFIGURE_OPTIONS += --enable-htcp
CONFIGURE_OPTIONS += --enable-icmp
CONFIGURE_OPTIONS += --enable-large-cache-files
CONFIGURE_OPTIONS += --enable-multicast-miss
CONFIGURE_OPTIONS += --enable-auth-negotiate='kerberos'
CONFIGURE_OPTIONS += --enable-auth-ntlm='smb_lm,fake'
CONFIGURE_OPTIONS += --enable-ntlm-fail-open
CONFIGURE_OPTIONS += --enable-removal-policies='heap,lru'
CONFIGURE_OPTIONS += --enable-snmp
CONFIGURE_OPTIONS += --enable-storeio='aufs,diskd,ufs'
CONFIGURE_OPTIONS += --enable-x-accelerator-vary
CONFIGURE_OPTIONS += --with-aio
CONFIGURE_OPTIONS += --with-aufs-threads=8
CONFIGURE_OPTIONS += --with-build-environment=POSIX_V6_LP64_OFF64
# Due to the current licensing of squid and openssl, gnutls/nettle
# must be enabled and used instead of openssl for tls and/or other
# crypto support.
CONFIGURE_OPTIONS += --with-gnutls
CONFIGURE_OPTIONS += --with-nettle
CONFIGURE_OPTIONS += --with-pthreads
CONFIGURE_OPTIONS += --disable-arch-native
CONFIGURE_OPTIONS += PERL=$(PERL)

# Appends the following line to the end of the squid.conf configuration
# file. This line is necessary for running squid for testing. 
# This starts up squid as user webservd. 
COMPONENT_POST_INSTALL_ACTION += \
	(cd $(PROTO_DIR)/etc/squid ; \
 	echo '\ncache_effective_user webservd' >> squid.conf)

# Adjust '#!/usr/bin/perl'
PERL_SCRIPTS= $(PROTOUSRDIR)/squid/libexec/helper-mux.pl

# To test manually follow along in the book
# Squid Proxy Server 3.1 Beginner's Guide Page 34
#
# Add this to the top of /etc/squid/squid.conf:
# cache_dir ufs /var/squid/cache/ 500 16 256
# acl my_machine src 192.0.2.21 # Replace with your desktop's IP address
# http_access allow my_machine
#
# You will probably need to remove or comment out the following lines or Squid
# will fail to start:
#	# acl manager proto cache_object
#
# Make sure apache is running.
#	# svcs apache22
# Start squid:
#	# svcadm enable squid
# On your desktop set your web browser to proxy through this squid:
# Edit -> Preferences -> Advanced -> Network -> Settings
#	Check: Manual proxy configuration
#	HTTP Proxy: <squid servers IP address>    Port: 3128
#   Save
# Enter <squid server URL> in your web browser.  You should be accessing squid
# and seeing files stored in the http server on that machine.
# Enter <squid server URL>:897 in your web browser and squid should complain.
# Squid is working properly.

# squid tests use cppunit. Currently this requires a version of cppunit
# installed that have been built with the GNU version 5.3 compilers.

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/=====/p" ' \
	'-e "/TOTAL/p" ' \
	'-e "/SKIP/p" ' \
	'-e "/PASS/p" ' \
	'-e "/FAIL/p" ' \
	'-e "/Can not open file/d" ' \
	'-e "/ERROR/p" '

REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/security/nettle
REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += security/kerberos-5
ifeq ($(OS_VERSION),5.11)
REQUIRED_PACKAGES += service/security/kerberos-5
endif
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/crypto
ifeq ($(OS_VERSION),5.11)
REQUIRED_PACKAGES += system/library/security/gss
endif
REQUIRED_PACKAGES += system/library/security/libsasl
REQUIRED_PACKAGES += system/library/security/libsasl2
REQUIRED_PACKAGES += system/network
REQUIRED_PACKAGES += system/network/ldap/openldap
