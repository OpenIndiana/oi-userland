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

BUILD_BITS =			64_and_32
BUILD_STYLE =			waf

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		samba
COMPONENT_FMRI =		service/network/samba
COMPONENT_VERSION =		4.12.5
COMPONENT_SRC =			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL =		http://www.samba.org/
COMPONENT_ARCHIVE =             $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH = 	sha256:54b41cc6378acae20dd155ba55d78ff171875c2eaa3f05f87b485d3d6891b815
COMPONENT_ARCHIVE_URL =		http://us1.samba.org/samba/ftp/stable/$(COMPONENT_ARCHIVE)
COMPONENT_SUMMARY =		samba - A Windows SMB/CIFS fileserver for UNIX
COMPONENT_LICENSE =		GPLv3
COMPONENT_LICENSE_FILE = 	$(COMPONENT_NAME).license
COMPONENT_CLASSIFICATION =	System/File System

TEST_TARGET =		$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

PERL_VERSION = 5.24
PYTHON_VERSION = 3.5
PY3_CYTHON_NAMING =\#

# set WAF and adapt PATH for building
WAF =	$(PYTHON) $(SOURCE_DIR)/buildtools/bin/waf

# directory to search for "include" in samba.p5m
PKG_OPTIONS +=		-I$(COMPONENT_DIR)
# Set the pkg... path to search files in ./Solaris/ dir (mainly the SMF manifests are there)
PKG_PROTO_DIRS +=	$(COMPONENT_DIR)

$(BUILD_DIR_32)/%:	MACHLIBDIR=
$(BUILD_DIR_64)/%:	MACHLIBDIR=/$(MACH64)

CFLAGS +=	$($(COMPILER)_C99_ENABLE) -D_POSIX_PTHREAD_SEMANTICS
CPPFLAGS +=	$(CPP_LARGEFILES) $(CPP_XPG6MODE) 
CPPFLAGS +=	-I/usr/include/openldap

LDFLAGS +=	-R/usr/lib/samba$(MACHLIBDIR)
LDFLAGS +=	-R/usr/lib/samba/private$(MACHLIBDIR)
LDFLAGS +=	-L$(GNULIB.$(BITS)) -R$(GNULIB.$(BITS))

LDFLAGS +=      -lrt -lsec -lcrypt -lmd5 -lsocket -lnsl -lsendfile
LDFLAGS +=      -lldap_r -lsendfile -lavahi-common -lavahi-core 

LD_OPTIONS +=	-B direct

#
# set everything for target configure.
#
CONFIGURE_PREFIX =	/usr/lib/samba

CONFIGURE_ENV +=	CPP="$(CC) -E"
CONFIGURE_ENV +=	CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_ENV +=	CUPS_CONFIG=$(USRBINDIR)/cups-config
CONFIGURE_ENV +=	PATH=$(GNUBIN.$(BITS)):$(USRBINDIR.$(BITS)):$(PATH.gnu)
CONFIGURE_ENV +=	PERL=$(PERL)
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
CONFIGURE_OPTIONS +=	--without-systemd

CONFIGURE_OPTIONS.64 += --python=$(PYTHON)
CONFIGURE_OPTIONS +=	--nopyo
CONFIGURE_OPTIONS +=	--nopycache
CONFIGURE_OPTIONS +=	--disable-rpath
CONFIGURE_OPTIONS +=	--bundled-libraries=ALL

CONFIGURE_OPTIONS +=	--disable-spotlight

CONFIGURE_OPTIONS.32 +=	--disable-python
CONFIGURE_OPTIONS.32 +=	--without-ad-dc

$(BUILD_32):	COMPONENT_BUILD_TARGETS= --targets=nss_winbind,pamwinbind 

# do not do waf install for winbind only - override the recipe
$(INSTALL_32): $(BUILD_32)
	/bin/sh -c "cd $(@D)  &&\
	    $(INSTALL) -d $(PROTO_DIR)/usr/lib/samba$(MACHLIBDIR)  &&\
	    $(INSTALL) -m 0555 -t $(PROTO_DIR)/usr/lib/samba$(MACHLIBDIR) bin/shared/!(pam_*).so* && \
	    $(INSTALL) -d $(PROTO_DIR)/usr/lib/samba/security$(MACHLIBDIR) && \
	    $(INSTALL) -m 0555 -t $(PROTO_DIR)/usr/lib/samba/security$(MACHLIBDIR) bin/shared/pam_*.so* && \
	    $(INSTALL) -d $(PROTO_DIR)/usr/lib/samba/private$(MACHLIBDIR) && \
	    $(INSTALL) -m 0555 -t $(PROTO_DIR)/usr/lib/samba/private$(MACHLIBDIR) bin/shared/private/*.so*"
	$(TOUCH) $@

#
# set everything for target build.
#
COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) $(PROTO_DIR)$(ETCDIR)/samba ; \
	(sed -f $(COMPONENT_DIR)/Solaris/smbconf.sed \
		> $(PROTO_DIR)$(ETCDIR)/samba/smb.conf.default $(BUILD_DIR_64)/examples/smb.conf.default) 

# Build dependencies
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += library/perl-5/parse-yapp-524

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += database/lmdb
REQUIRED_PACKAGES += library/file-monitor/gamin
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += library/jansson
REQUIRED_PACKAGES += library/libarchive
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/security/gpgme
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/libgcrypt
REQUIRED_PACKAGES += system/network/avahi
