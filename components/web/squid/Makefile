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
#

include ../../../make-rules/shared-macros.mk

PATH=/usr/bin:/usr/gnu/bin:/usr/sbin:/usr/perl5/bin

COMPONENT_NAME=         squid
COMPONENT_VERSION=      3.5.28
COMPONENT_SUMMARY=	Squid Web Proxy Cache
COMPONENT_DESCRIPTION=	Squid is a caching proxy for the Web supporting HTTP, HTTPS, FTP, and more.
COMPONENT_PROJECT_URL=  http://www.squid-cache.org/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:fd41b622e65c661ada9a98b0338c59e6f2d2ffdb367fe5c8c7212c535e298ed8
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)Versions/v3/3.5/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		web/proxy/squid
COMPONENT_CLASSIFICATION=	Web Services/Application and Web Servers
COMPONENT_LICENSE=	GPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION =        ( cd $(@D) &&\
					libtoolize --copy --force &&\
					aclocal -I acinclude &&\
					automake -c -f -a &&\
					autoconf)

CFLAGS += -I/usr/include/kerberosv5
CFLAGS += $(CPP_LARGEFILES)

# Squid has own prefix
CONFIGURE_PREFIX =	/usr/squid

CONFIGURE_BINDIR.64 = $(CONFIGURE_PREFIX)/bin
CONFIGURE_SBINDIR.64 = $(CONFIGURE_PREFIX)/sbin

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
CONFIGURE_OPTIONS += --enable-storeio='aufs,diskd,ufs'
CONFIGURE_OPTIONS += --enable-useragent-log
CONFIGURE_OPTIONS += --enable-x-accelerator-vary
CONFIGURE_OPTIONS += --with-aio
CONFIGURE_OPTIONS += --with-aufs-threads=8
CONFIGURE_OPTIONS += --with-large-files
CONFIGURE_OPTIONS += --with-build-environment=POSIX_V6_ILP32_OFFBIG
CONFIGURE_OPTIONS += --with-pthreads

# common targets
build:		$(BUILD_64) 

install:	$(INSTALL_64) 

# configure says it needs cppunit to test with.
# After some work I can get cppunit to build but it quickly
# falls over during test so giving up.
# I don't think the test suite really tests squid's functionality anyways.
#
# To test manually follow along in the book
# Squid Proxy Server 3.1 Beginner's Guide Page 34
#
# Add this to the top of /etc/squid/squid.conf:
# cache_dir ufs /var/squid/cache/ 500 16 256
# acl my_machine src 192.0.2.21 # Replace with your desktop's IP address
# http_access allow my_machine
#
# Make sure apache is running.
#	# svcs apache24
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
# installed that have been built with the GNU compilers.

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/=====/p" ' \
	'-e "/TOTAL/p" ' \
	'-e "/SKIP/p" ' \
	'-e "/PASS/p" ' \
	'-e "/FAIL/p" ' \
	'-e "/Can not open file/d" ' \
	'-e "/ERROR/p" '

test:	$(TEST_64)

# Build dependencies
REQUIRED_PACKAGES += developer/cppunit

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += database/berkeleydb-5
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/nettle
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += service/security/kerberos-5
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/gss
REQUIRED_PACKAGES += system/library/security/libsasl
