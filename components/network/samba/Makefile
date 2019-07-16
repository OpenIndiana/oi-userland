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
# Copyright 2019 Rouven Weiler
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		samba
COMPONENT_FMRI =		service/network/samba
COMPONENT_VERSION =		4.10.6
COMPONENT_SRC =			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL =		http://www.samba.org/
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH = 	sha256:9efbeb52db1203dc779b118f1c48c161e569f7a6af5101e745497ee6296eef42
COMPONENT_ARCHIVE_URL =		http://us1.samba.org/samba/ftp/stable/$(COMPONENT_ARCHIVE)
COMPONENT_SUMMARY =		samba - A Windows SMB/CIFS fileserver for UNIX
COMPONENT_LICENSE =		GPLv3
COMPONENT_LICENSE_FILE = 	$(COMPONENT_NAME).license
COMPONENT_CLASSIFICATION =	System/File System

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/waf.mk
include $(WS_MAKE_RULES)/ips.mk

PYTHON_VERSION = 3.5
PY3_CYTHON_NAMING =\#

# set WAF and adapt PATH for building
WAF =	$(PYTHON) $(SOURCE_DIR)/buildtools/bin/waf

# directory to search for "include" in samba.p5m
PKG_OPTIONS +=		-I$(COMPONENT_DIR)
# Set the pkg... path to search files in ./Solaris/ dir (mainly the SMF manifests are there)
PKG_PROTO_DIRS +=	$(COMPONENT_DIR)

CFLAGS +=	$($(COMPILER)_C99_ENABLE)
CPPFLAGS +=	$(CPP_LARGEFILES) $(CPP_XPG6MODE) -I/usr/include/openldap

LDFLAGS.64 +=   -L/usr/lib/$(MACH64)/gnutls-3 -R/usr/lib/$(MACH64)/gnutls-3
LDFLAGS.64 +=	-L/usr/lib/samba/$(MACH64) -R/usr/lib/samba/$(MACH64)
LDFLAGS.64 +=	-L/usr/lib/samba/private/$(MACH64) -R/usr/lib/samba/private/$(MACH64)
LDFLAGS.64 +=	-L/usr/gnu/lib/$(MACH64) -R/usr/gnu/lib/$(MACH64)

LDFLAGS +=      -lrt -lsec -lcrypt -lmd5 -lsocket -lnsl -lsendfile $(LD_FLAGS.$(BITS))
LDFLAGS +=      -lldap_r -lsendfile -lavahi-common -lavahi-core $(LDFLAGS.$(BITS))

LD_OPTIONS +=	-B direct

# Force use of gnutls-3 pkgconfig during 2.x->3.x transition
PKG_CONFIG_PATH =		$(PKG_CONFIG_PATH.$(BITS))/gnutls-3:$(PKG_CONFIG_PATH.$(BITS))

#
# set everything for target configure.
#
CONFIGURE_PREFIX =	/usr/lib/samba

CONFIGURE_ENV +=	CPP="$(CC) -E"
CONFIGURE_ENV +=	CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_ENV +=	CUPS_CONFIG=$(USRBINDIR)/cups-config
CONFIGURE_ENV +=	PYTHONARCHDIR=$(PYTHON_VENDOR_PACKAGES)/samba

# --enable-fhs should not be on
CONFIGURE_OPTIONS +=	--prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS +=    --exec-prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS.64 += --bindir=$(CONFIGURE_PREFIX)/bin/$(MACH64)
CONFIGURE_OPTIONS.64 += --sbindir=$(CONFIGURE_PREFIX)/sbin/$(MACH64)
CONFIGURE_OPTIONS.64 += --libdir=$(CONFIGURE_PREFIX)/$(MACH64)
CONFIGURE_OPTIONS.64 += --with-privatelibdir=$(CONFIGURE_PREFIX)/private/$(MACH64)
CONFIGURE_OPTIONS +=    --sysconfdir=$(ETCDIR)/samba
CONFIGURE_OPTIONS.64 += --with-pammodulesdir=$(CONFIGURE_PREFIX)/security/$(MACH64)
CONFIGURE_OPTIONS +=    --datarootdir=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS +=    --mandir=$(USRSHAREMANDIR)
CONFIGURE_OPTIONS +=    --htmldir=/usr/share/samba/swat/help
CONFIGURE_OPTIONS +=    --includedir=$(USRINCDIR)/samba
CONFIGURE_OPTIONS +=    --with-privatedir=$(ETCDIR)/samba/private
CONFIGURE_OPTIONS +=    --localstatedir=$(VARDIR)/samba
CONFIGURE_OPTIONS +=    --with-logfilebase=$(VARDIR)/samba/log
CONFIGURE_OPTIONS +=    --sharedstatedir=$(VARDIR)/samba/com
CONFIGURE_OPTIONS.64 +=	--libexecdir=$(CONFIGURE_PREFIX)/libexec/$(MACH64)
CONFIGURE_OPTIONS +=	--with-bind-dns-dir=$(CONFIGURE_PREFIX)/bind-dns

CONFIGURE_OPTIONS.64 +=	--with-static-modules=vfs_solarisacl
CONFIGURE_OPTIONS.64 +=	--with-shared-modules=vfs_worm,vfs_zfsacl,vfs_prealloc,vfs_cacheprime,vfs_commit,idmap_ldap,idmap_tdb2,idmap_rid,idmap_ad,idmap_hash,idmap_adex
CONFIGURE_OPTIONS +=	--with-ads
CONFIGURE_OPTIONS +=	--with-winbind
CONFIGURE_OPTIONS +=	--with-ldap
CONFIGURE_OPTIONS +=	--with-libldap=ldap_r

CONFIGURE_OPTIONS +=	--nopyo
CONFIGURE_OPTIONS +=    --nopycache
CONFIGURE_OPTIONS +=	--disable-rpath
CONFIGURE_OPTIONS +=	--bundled-libraries=ALL
CONFIGURE_OPTIONS +=	--python=$(PYTHON)

#
# set everything for target build.
#
COMPONENT_BUILD_ARGS += $(WAF_BUILD_OPTIONS) 

COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) $(PROTO_DIR)$(ETCDIR)/samba ; \
	(sed -f $(COMPONENT_DIR)/Solaris/smbconf.sed \
		> $(PROTO_DIR)$(ETCDIR)/samba/smb.conf.default $(BUILD_DIR_64)/examples/smb.conf.default) 

#
# common targets
#
build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

system-test:    $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += database/lmdb
REQUIRED_PACKAGES += library/file-monitor/gamin
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/jansson
REQUIRED_PACKAGES += library/libarchive
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/security/gpgme
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/libgcrypt
REQUIRED_PACKAGES += system/network/avahi
