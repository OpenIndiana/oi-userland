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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

PATH=/usr/bin:/usr/gnu/bin:/usr/sbin:/usr/perl5/bin

COMPONENT_NAME=		squid
COMPONENT_VERSION=	2.7.STABLE9
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:6d90fe06468b662b2eefd7ffeb47b9a78f0a871d
COMPONENT_ARCHIVE_URL=	http://www.squid-cache.org/Versions/v2/2.7/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

IPS_COMPONENT_VERSION=	2.7.9

CFLAGS += -I/usr/include/kerberosv5
CFLAGS += -DSOLARIS_11
CFLAGS += -D__BIG_ENDIAN__
CFLAGS += $(CPP_LARGEFILES)
CFLAGS += $(studio_FEATURES_EXTENSIONS)


# Squid has own prefix
CONFIGURE_PREFIX =	/usr/squid

CONFIGURE_OPTIONS +=   CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS += --libexecdir=$(CONFIGURE_PREFIX)/libexec
CONFIGURE_OPTIONS += --localstatedir=/var/squid
CONFIGURE_OPTIONS += --sharedstatedir=/var/squid
CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)/squid
CONFIGURE_OPTIONS += --mandir=$(CONFIGURE_PREFIX)/man
CONFIGURE_OPTIONS += --enable-arp-acl
CONFIGURE_OPTIONS += --enable-auth='basic,digest,negotiate,ntlm'
CONFIGURE_OPTIONS += --enable-basic-auth-helpers='DB,NCSA,YP,LDAP,PAM,getpwnam,MSNT,POP3,multi-domain-NTLM,SMB,SASL'
CONFIGURE_OPTIONS += --enable-cache-digests
CONFIGURE_OPTIONS += --enable-carp
CONFIGURE_OPTIONS += --enable-coss-aio-ops
CONFIGURE_OPTIONS += --enable-delay-pools
CONFIGURE_OPTIONS += --enable-digest-auth-helpers='ldap,password'
CONFIGURE_OPTIONS += --enable-external-acl-helpers='ip_user,unix_group,ldap_group,wbinfo_group'
CONFIGURE_OPTIONS += --enable-follow-x-forwarded-for
CONFIGURE_OPTIONS += --enable-forward-log
CONFIGURE_OPTIONS += --enable-forw-via-db
CONFIGURE_OPTIONS += --enable-htcp
CONFIGURE_OPTIONS += --enable-icmp
CONFIGURE_OPTIONS += --enable-large-cache-files
CONFIGURE_OPTIONS += --enable-multicast-miss
CONFIGURE_OPTIONS += --enable-negotiate-auth-helpers='squid_kerb_auth'
CONFIGURE_OPTIONS += --enable-ntlm-auth-helpers='SMB,fakeauth,no_check'
CONFIGURE_OPTIONS += --enable-ntlm-fail-open
CONFIGURE_OPTIONS += --enable-referer-log
CONFIGURE_OPTIONS += --enable-removal-policies='heap,lru'
CONFIGURE_OPTIONS += --enable-snmp
CONFIGURE_OPTIONS += --enable-ssl
CONFIGURE_OPTIONS += --enable-storeio='aufs,coss,diskd,ufs,null'
CONFIGURE_OPTIONS += --enable-useragent-log
CONFIGURE_OPTIONS += --enable-x-accelerator-vary
CONFIGURE_OPTIONS += --with-aio
CONFIGURE_OPTIONS += --with-aufs-threads=8
CONFIGURE_OPTIONS += --with-large-files
CONFIGURE_OPTIONS += --with-build-environment=POSIX_V6_ILP32_OFFBIG
CONFIGURE_OPTIONS += --with-pthreads

COMPONENT_POST_BUILD_ACTION= \
		(cd $(@D) ; $(PERL) -pi \
                -e 'print q{visible_hostname localhost} if $$. == 1;' \
                -e 's/^\# +cache_effective_user.*/cache_effective_user webservd/g;' \
                -e 's/^\# +dns_testnames.*/dns_testnames localhost/g' \
               		src/squid.conf.default )


PKG_PROTO_DIRS +=       $(SOURCE_DIR)
PKG_PROTO_DIRS +=       $(COMPONENT_DIR)


include ../../make-rules/shared-targets.mk

# common targets
build:		$(BUILD_32) 

install:	$(INSTALL_32) 
		sed -f oracleman-stability $(BUILD_DIR_32)/doc/squid.8 \
			> $(PROTOUSRDIR)/squid/man/man8/squid.8
		sed -f oracleman-stability $(BUILD_DIR_32)/doc/cachemgr.cgi.8 \
			> $(PROTOUSRDIR)/squid/man/man8/cachemgr.cgi.8
		sed -f oracleman-stability $(SOURCE_DIR)/helpers/basic_auth/NCSA/ncsa_auth.8 \
			> $(PROTOUSRDIR)/squid/man/man8/ncsa_auth.8
		sed -f oracleman-stability $(SOURCE_DIR)/helpers/basic_auth/PAM/pam_auth.8 \
			> $(PROTOUSRDIR)/squid/man/man8/pam_auth.8
		sed -f oracleman-stability $(BUILD_DIR_32)/helpers/basic_auth/DB/squid_db_auth.8 \
			> $(PROTOUSRDIR)/squid/man/man8/squid_db_auth.8
		sed -f oracleman-stability $(SOURCE_DIR)/helpers/basic_auth/LDAP/squid_ldap_auth.8 \
			> $(PROTOUSRDIR)/squid/man/man8/squid_ldap_auth.8
		sed -f oracleman-stability $(SOURCE_DIR)/helpers/external_acl/ldap_group/squid_ldap_group.8 \
			> $(PROTOUSRDIR)/squid/man/man8/squid_ldap_group.8
		sed -f oracleman-stability $(SOURCE_DIR)/helpers/external_acl/unix_group/squid_unix_group.8 \
			> $(PROTOUSRDIR)/squid/man/man8/squid_unix_group.8
		
test:
	@echo "no tests available"


BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
