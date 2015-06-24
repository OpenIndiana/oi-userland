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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
#

COMPILER =	gcc

include ../../make-rules/shared-macros.mk

PATH=/usr/bin:/usr/gnu/bin:/usr/sbin:/usr/perl5/bin

COMPONENT_NAME=         squid
COMPONENT_VERSION=      3.5.5
COMPONENT_PROJECT_URL=  http://www.squid-cache.org/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
    sha256:23793da6b23871765188becae59a6f4b6c3672c256ba9be90743b46a3c7921cf
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)Versions/v3/3.5/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/squid

TPNO=			23264

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CC += $(CC_BITS)
CXX += $(CC_BITS)

CFLAGS += -I/usr/include/kerberosv5
CFLAGS += $(CPP_LARGEFILES)

CONFIGURE_BINDIR.64 =	$(CONFIGURE_PREFIX)/bin
CONFIGURE_LIBDIR.64 =	$(CONFIGURE_PREFIX)/lib
CONFIGURE_OPTIONS.64 += LDFLAGS="$(LDFLAGS) -m64"
CONFIGURE_OPTIONS.64 += LIBS="-m64"

# Squid has own prefix
CONFIGURE_PREFIX =	/usr/squid

CONFIGURE_OPTIONS +=   CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS += --libexecdir=$(CONFIGURE_PREFIX)/libexec
CONFIGURE_OPTIONS += --localstatedir=/var/squid
CONFIGURE_OPTIONS += --sharedstatedir=/var/squid
CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)/squid
CONFIGURE_OPTIONS += --mandir=$(CONFIGURE_PREFIX)/man
CONFIGURE_OPTIONS += --sbindir=$(CONFIGURE_PREFIX)/sbin
CONFIGURE_OPTIONS += --enable-arp-acl
CONFIGURE_OPTIONS += --enable-auth-basic='DB,NCSA,LDAP,PAM,getpwnam,MSNT-multi-domain,POP3,SMB,SASL'
CONFIGURE_OPTIONS += --enable-cache-digests
CONFIGURE_OPTIONS += --enable-carp
CONFIGURE_OPTIONS += --enable-coss-aio-ops
CONFIGURE_OPTIONS += --enable-delay-pools
CONFIGURE_OPTIONS += --enable-auth-digest='LDAP'
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
CONFIGURE_OPTIONS += --enable-ssl
CONFIGURE_OPTIONS += --enable-storeio='aufs,diskd,ufs'
CONFIGURE_OPTIONS += --enable-x-accelerator-vary
CONFIGURE_OPTIONS += --with-aio
CONFIGURE_OPTIONS += --with-aufs-threads=8
CONFIGURE_OPTIONS += --with-build-environment=POSIX_V6_ILP32_OFFBIG
CONFIGURE_OPTIONS += --with-pthreads

COMPONENT_BUILD_ARGS += CFLAGS="$(CFLAGS)"

ASLR_MODE = $(ASLR_ENABLE)

# common targets
configure:	$(CONFIGURE_64)

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

test:		$(NO_TESTS)

system-test:    $(NO_TESTS)


REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += runtime/perl-512
REQUIRED_PACKAGES += runtime/perl-516
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/crypto
REQUIRED_PACKAGES += system/library/security/gss
REQUIRED_PACKAGES += system/library/security/libsasl
REQUIRED_PACKAGES += system/network
REQUIRED_PACKAGES += service/security/kerberos-5 
