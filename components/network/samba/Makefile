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

ifeq ($(MACH), sparc)
# parallelize up to 64 concurent tasks for sparc
WAFOPT1 = -j64
else
WAFOPT1 = -j16
endif

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		samba
COMPONENT_VERSION=	4.8.8
TPNO=			20605
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://www.samba.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:3bc97ba7b827526b299e09a1c410f22d3a3c57bb46f1e67e8f93258945f8cf60
COMPONENT_ARCHIVE_URL=	http://us1.samba.org/samba/ftp/stable/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/samba

include $(WS_MAKE_RULES)/prep.mk

# waf
WAF_PATH	=	PATH=$(BUILD_DIR)/samba/buildtools/bin:$(PROTO_DIR)/usr/bin:$$PATH:/usr/perl5/bin
# Verbosed waf produces unreadable output if parallelized.
# Uncomment to enable verbose build.
#override WAFOPT1	=	-v -j1

# Set build dirs for Samba + Winbind / Winbind (without Samba).
BUILD_DIR_SMB		= $(BUILD_DIR)/samba
BUILD_DIR_WINB		= $(BUILD_DIR)/winbind

include $(WS_MAKE_RULES)/ips.mk

# directory to search for "include" in samba.p5m
PKG_OPTIONS += -I $(COMPONENT_DIR)
# Set the pkg... path to search files in ./Solaris/ dir (mainly the SMF manifests are there)
PKG_PROTO_DIRS += $(COMPONENT_DIR)

# Compiler settings
CFLAGS	+=	$($(COMPILER)_C99_ENABLE)

LIBS +=		-lrt -lsec -lcrypt -lmd5 -lsocket -lnsl
# libavahi and libgamin libraries are not available for 64bits
LIBS32 =	-lsendfile -lavahi-common -lavahi-core

#CPPFLAGS +=	-DSAMBA_VERSION_VENDOR_SUFFIX=\\\"Placeholder_for_vendor_suffix\\\"
CPPFLAGS +=	$(CPP_LARGEFILES)
CPPFLAGS +=	$(CPP_XPG6MODE)
CPPFLAGS +=	-I/usr/include/openldap

LDFLAGS.32 +=	-R/usr/lib/samba
LDFLAGS.32 +=	-R/usr/lib/samba/private
LDFLAGS.32 +=	$(LIBS) $(LIBS32)
LDFLAGS.32 +=	-R/usr/gnu/lib

LDFLAGS.64 +=	-m64
LDFLAGS.64 +=	-R/usr/lib/samba/$(MACH64)
LDFLAGS.64 +=	-R/usr/lib/samba/private/$(MACH64)
LDFLAGS.64 +=	$(LIBS)
LDFLAGS.64 +=	-R/usr/gnu/lib/$(MACH64)

#ASLR_MODE =	$(ASLR_ENABLE)
LD_OPTIONS += 	-B direct

# Force use of gnutls-3 pkgconfig during 2.x->3.x transition
GNUTLS_PKG_CONFIG_PATH_32 = /usr/lib/pkgconfig/gnutls-3
GNUTLS_PKG_CONFIG_PATH_64 = /usr/lib/$(MACH64)/pkgconfig/gnutls-3
PKG_CONFIG_PATH = $(GNUTLS_PKG_CONFIG_PATH_$(BITS)):$(PKG_CONFIG_PATH.$(BITS))

LDFLAGS.32 += -L/usr/lib/gnutls-3 -R/usr/lib/gnutls-3
LDFLAGS.64 += -L/usr/lib/$(MACH64)/gnutls-3 -R/usr/lib/$(MACH64)/gnutls-3

# --enable-fhs should not be on
CONFIGURE_OPTIONS =	--exec-prefix=/usr
CONFIGURE_OPTIONS.32 +=	--bindir=/usr/lib/samba/bin
CONFIGURE_OPTIONS.64 +=	--bindir=/usr/lib/samba/bin/$(MACH64)
CONFIGURE_OPTIONS.32 +=	--sbindir=/usr/lib/samba/sbin
CONFIGURE_OPTIONS.64 +=	--sbindir=/usr/lib/samba/sbin/$(MACH64)
CONFIGURE_OPTIONS.32 +=	--libdir=/usr/lib/samba
CONFIGURE_OPTIONS.64 +=	--libdir=/usr/lib/samba/$(MACH64)
CONFIGURE_OPTIONS.32 +=	--with-privatelibdir=/usr/lib/samba/private
CONFIGURE_OPTIONS.64 +=	--with-privatelibdir=/usr/lib/samba/private/$(MACH64)
CONFIGURE_OPTIONS +=	--sysconfdir=/etc/samba
CONFIGURE_OPTIONS.32 +=	--with-pammodulesdir=/usr/lib/samba/security
CONFIGURE_OPTIONS.64 +=	--with-pammodulesdir=/usr/lib/samba/security/$(MACH64)
CONFIGURE_OPTIONS +=	--datarootdir=/usr/lib/samba
CONFIGURE_OPTIONS +=	--mandir=/usr/share/man
CONFIGURE_OPTIONS +=	--htmldir=/usr/share/samba/swat/help
CONFIGURE_OPTIONS +=	--includedir=/usr/include/samba
CONFIGURE_OPTIONS +=	--with-privatedir=/etc/samba/private
CONFIGURE_OPTIONS +=	--localstatedir=/var/samba
CONFIGURE_OPTIONS +=	--with-logfilebase=/var/samba/log
CONFIGURE_OPTIONS +=	--sharedstatedir=/var/samba/com
CONFIGURE_OPTIONS +=	--libexecdir=/usr/lib/samba

CONFIGURE_OPTIONS +=	--with-static-modules=vfs_solarisacl
CONFIGURE_OPTIONS.32 +=	--with-shared-modules=vfs_worm,vfs_zfsacl,vfs_prealloc,vfs_cacheprime,vfs_commit,idmap_ldap,idmap_tdb2,idmap_rid,idmap_ad,idmap_hash,idmap_adex
CONFIGURE_OPTIONS.64 +=	--with-shared-modules=idmap_ldap,idmap_tdb2,idmap_rid,idmap_ad,idmap_hash,idmap_adex
CONFIGURE_OPTIONS +=	--with-ads
CONFIGURE_OPTIONS +=	--with-winbind
CONFIGURE_OPTIONS +=	--with-ldap
CONFIGURE_OPTIONS +=	--with-libldap=ldap_r
#CONFIGURE_OPTIONS +=	--with-system-mitkrb5
#CONFIGURE_OPTIONS +=	--without-ad-dc

CONFIGURE_OPTIONS +=	--nocache
CONFIGURE_OPTIONS +=	--nopyo
CONFIGURE_OPTIONS +=	--disable-rpath
#CONFIGURE_OPTIONS +=	--disable-gnutls
CONFIGURE_OPTIONS +=	--bundled-libraries=ALL

#CONFIGURE_OPTIONS.32 +=	--with-samfs=$(PROTO_DIR)/opt/SUNWsamfs/lib

CONFIGURE_ENV += 	CC="$(CC)"
CONFIGURE_ENV += 	CPP="$(CC) -E"
CONFIGURE_ENV += 	AWK=gawk
CONFIGURE_ENV += 	PERL=$(PERL)
CONFIGURE_ENV += 	PYTHON=$(PYTHON)
CONFIGURE_ENV += 	python_LDFLAGS="-m$(BITS) -fPIC -DPIC"
CONFIGURE_ENV += 	PYTHONDIR="$(PYTHON_VENDOR_PACKAGES)"
CONFIGURE_ENV += 	PYTHONARCHDIR="$(PYTHON_VENDOR_PACKAGES)/samba"
CONFIGURE_ENV += 	LD="$(LD)"
CONFIGURE_ENV +=	CFLAGS="$(CFLAGS)"
CONFIGURE_ENV.32 +=	CPPFLAGS="$(CPPFLAGS) -I$(COMPONENT_DIR)/Solaris/include"
CONFIGURE_ENV.64 +=	CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_ENV.32 +=	LINKFLAGS="$(LDFLAGS.32)"
CONFIGURE_ENV.64 +=	LINKFLAGS="$(LDFLAGS.64)"
CONFIGURE_ENV.64 +=	MACH64="$(MACH64)"
CONFIGURE_ENV +=	LD_EXEC_OPTIONS="$(LD_EXEC_OPTIONS)"
CONFIGURE_ENV +=	CUPS_CONFIG=$(USRBINDIR)/cups-config
CONFIGURE_ENV +=	PKG_CONFIG_PATH="$(PKG_CONFIG_PATH)"

# Propagation of smb.conf with default settings.
$(PROTO_DIR)/etc/samba/smb.conf-example: $(BUILD_DIR_SMB)/.built
	$(MKDIR) $(@D)
	sed -f $(COMPONENT_DIR)/Solaris/smbconf.sed > $@ \
	   $(BUILD_DIR_SMB)/examples/smb.conf.default

# Build targets for WAF:
# (motivation) Samba started to use WAF (build system from Google) from the 3.x
# (as a parallel build system) but Samba4 discontinued the use of auto tools
# definitively.
# (note) .BDprep target is an additional step between .prep and .configure
# targets. It was added because there were problems with libtool-like phase of
# WAF when the not "prepared well". "waf distclean" on CLONEY'ed BUILD_DIR is
# enough.

# Prepare build dir for Samba + Winbind.
$(BUILD_DIR_SMB)/.BDprep:	$(SOURCE_DIR)/.prep
	# re-create configure dir
	$(MKDIR) $(@D)
	# Clone SOURCE_DIR
	$(CLONEY) $(SOURCE_DIR) $(@D)
	# clenup of clone
	(cd $(@D) ; $(ENV) $(WAF_PATH) $(PYTHON) $(SOURCE_DIR)/buildtools/bin/waf distclean $(WAFOPT1) )
	$(TOUCH) $@

# Configure of Samba + Winbind.
$(BUILD_DIR_SMB)/.configured:	$(BUILD_DIR_SMB)/.BDprep
	(cd $(@D) ; $(ENV) $(WAF_PATH) $(CONFIGURE_ENV) \
		$(CONFIGURE_ENV.32) $(PYTHON) $(SOURCE_DIR)/buildtools/bin/waf configure $(WAFOPT1) $(CONFIGURE_OPTIONS) $(CONFIGURE_OPTIONS.32) )
	$(TOUCH) $@

# Build of Samba + Winbind.
$(BUILD_DIR_SMB)/.built:	$(BUILD_DIR_SMB)/.configured
	(cd $(@D) ; $(ENV) $(WAF_PATH) LD_EXEC_OPTIONS="$(LD_EXEC_OPTIONS)" $(PYTHON) $(SOURCE_DIR)/buildtools/bin/waf build $(WAFOPT1) )
	$(TOUCH) $@

# Install of Samba + Winbind.
$(BUILD_DIR_SMB)/.installed:	$(BUILD_DIR_SMB)/.built
	(cd $(@D) ; $(ENV) $(WAF_PATH) LD_EXEC_OPTIONS="$(LD_EXEC_OPTIONS)" $(PYTHON) $(SOURCE_DIR)/buildtools/bin/waf install $(WAFOPT1) --destdir=$(PROTO_DIR) )
	$(PYTHON) -m compileall $(PROTO_DIR)/$(PYTHON_VENDOR_PACKAGES)/
	$(TOUCH) $@

# Prepare build dir for Winbind (without Samba) for different bitness.
$(BUILD_DIR_WINB)/.BDprep:	$(SOURCE_DIR)/.prep
	# re-create configure dir
	$(MKDIR) $(@D)
	# Clone SOURCE_DIR
	$(CLONEY) $(SOURCE_DIR) $(@D)
	# clenup of clone
	(cd $(@D) ; $(ENV) $(WAF_PATH) $(PYTHON) $(SOURCE_DIR)/buildtools/bin/waf distclean $(WAFOPT1) )
	$(TOUCH) $@

# Configure of Winbind (without Samba) for different bitness.
#$(BUILD_DIR_WINB)/.configured:	$(BUILD_DIR_WINB)/.BDprep $(PROTO_DIR)/usr/lib/samba/$(MACH64)/libgssapi_krb5.so
$(BUILD_DIR_WINB)/.configured:	$(BUILD_DIR_WINB)/.BDprep
	(cd $(@D) ; $(ENV) $(WAF_PATH) $(CONFIGURE_ENV) \
		$(CONFIGURE_ENV.64) $(PYTHON) $(SOURCE_DIR)/buildtools/bin/waf configure $(WAFOPT1) $(CONFIGURE_OPTIONS) $(CONFIGURE_OPTIONS.64) )
	$(TOUCH) $@

# Build of Winbind (without Samba) for different bitness.
WB_TARGETS =	--targets=nss_winbind,pamwinbind
$(BUILD_DIR_WINB)/.built:	$(BUILD_DIR_WINB)/.configured
	(cd $(@D) ; $(ENV) $(WAF_PATH) LD_EXEC_OPTIONS="$(LD_EXEC_OPTIONS)" $(PYTHON) $(SOURCE_DIR)/buildtools/bin/waf build $(WAFOPT1) \
	    $(WB_TARGETS) )
	$(TOUCH) $@

# Installf Winbind (without Samba) for different bitness.
$(BUILD_DIR_WINB)/.installed:	$(BUILD_DIR_WINB)/.built
	(cd $(@D) ; \
	    $(INSTALL) -d $(PROTO_DIR)/usr/lib/samba/$(MACH64) ; \
	    $(INSTALL) -m 0555 -t $(PROTO_DIR)/usr/lib/samba/$(MACH64) bin/shared/*.so* ; \
	    $(INSTALL) -d $(PROTO_DIR)/usr/lib/samba/private/$(MACH64) ; \
	    $(INSTALL) -m 0555 -t $(PROTO_DIR)/usr/lib/samba/private/$(MACH64) bin/shared/private/*.so* \
	)
	$(TOUCH) $@

# Set appropriate bitnesses for Samba + Winbind / Winbind (without Samba).
$(BUILD_DIR_SMB)/.configured:	BITS=32
$(BUILD_DIR_WINB)/.configured:	BITS=64

# common targets
build:		$(BUILD_DIR_SMB)/.built $(BUILD_DIR_WINB)/.built

include $(WS_MAKE_RULES)/shared-targets.mk

install:	$(BUILD_DIR_SMB)/.installed $(BUILD_DIR_WINB)/.installed

test:		$(NO_TESTS)

system-test:    $(NO_TESTS)

clean::
	$(RM) -r $(BUILD_DIR)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/file-monitor/gamin
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/jansson
REQUIRED_PACKAGES += library/libarchive
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += library/python/chardet-27
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/security/gpgme
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/libgcrypt
REQUIRED_PACKAGES += system/network/avahi
