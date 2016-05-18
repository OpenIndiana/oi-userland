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

include ../../make-rules/shared-macros.mk

# Samba does not work properly on i386 when built by studio with -xO3+.
ifeq ($(MACH), sparc)
# standard options
else
# Both SPRO_VROOT and studio_OPT vars must use the override keyword otherwise
# Userland will ignore it and use its default value.
# To use the older 12.3 compiler instead of the default 12.4 compiler uncomment
# the following line.
#override SPRO_VROOT = $(SPRO_ROOT)/solarisstudio12.3
override studio_OPT = -xO1
endif

COMPONENT_NAME=		samba
COMPONENT_VERSION=	4.1.23
TPNO=			27625
COMPONENT_ARCHIVE_HASH= sha256:2c33291bf5454ba05e8b5fdc2c57ee010cf44d077e57a307ad2e7be9fac27cd2
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://www.samba.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://download.samba.org/pub/samba/stable/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/samba

include $(WS_MAKE_RULES)/prep.mk

# waf
WAF_PATH	=	PATH=$(BUILD_DIR)/samba/buildtools/bin:$(PROTO_DIR)/usr/bin:$$PATH
# Verbosed waf produces unreadable output if parallelized.
# Uncomment to enable verbose build.
#override WAFOPT1	=	-v -j1

# Set build dirs for Samba + Winbind / Winbind (without Samba).
BUILD_DIR_SMB		= $(BUILD_DIR)/samba
BUILD_DIR_WINB		= $(BUILD_DIR)/winbind

# Depends on S12-only libraries from Desktop to build.
ifeq ($(BUILD_TYPE), evaluation)
PUBLISH_STAMP=
endif
include $(WS_MAKE_RULES)/ips.mk

# directory to search for "include" in samba.p5m
PKG_OPTIONS += -I $(COMPONENT_DIR)

# Oracle HSM is not supported on 12.0 yet but the libsam.so target should rather be commented out than removed
# (note) change compiler bitness here when Samba became 64bits
#$(PROTO_DIR)/opt/SUNWsamfs/lib/$(MACH64)/libsam.so: Solaris/libsam.c
#	$(MKDIR) $(@D)
#	$(CC.studio.64) -m64 -G $(studio_PIC) -hlibsam.so Solaris/libsam.c \
#		-I$(COMPONENT_DIR)/Solaris/include \
#		-o $@

# Samba 4 needs extension of krb5 API, which is implemented in a Samba private
# library libgssapi_krb5.so.  Once MIT Kerberos is updated in Solaris 12 to
# version 1.9 or higher this extension will no longer be needed
# see Bug 18308792 for details.
$(PROTO_DIR)/usr/lib/samba/libgssapi_krb5.so: Solaris/dummy.c
	$(MKDIR) $(@D)
	$(CC.studio.32) -m32 -G $(studio_PIC) -hlibgssapi_krb5.so Solaris/dummy.c \
		-R/usr/lib/gss \
		-M$(COMPONENT_DIR)/Solaris/gssapi_krb5-mapfile-vers \
		-o $@

$(PROTO_DIR)/usr/lib/samba/$(MACH64)/libgssapi_krb5.so: Solaris/dummy.c
	$(MKDIR) $(@D)
	$(CC.studio.64) -m64 -G $(studio_PIC) -hlibgssapi_krb5.so Solaris/dummy.c \
		-R/usr/lib/gss/$(MACH64) \
		-M$(COMPONENT_DIR)/Solaris/gssapi_krb5-mapfile-vers \
		-o $@

$(PROTO_DIR)/usr/include/gssapi/gssapi_krb5.h: Solaris/gssapi_krb5.h
	$(MKDIR) $(@D)
	$(CP) Solaris/gssapi_krb5.h $@

$(PROTO_DIR)/usr/bin/krb5-config:	Solaris/krb5-config
	$(MKDIR) $(@D)
	sed -e "s#_SAMBA_BUILD_PROTO_#$(PROTO_DIR)#" \
	   $(COMPONENT_DIR)/Solaris/krb5-config > $@
	$(CHMOD) 755 $@

# Compiler settings
CFLAGS.studio	+=	$(studio_C99_ENABLE)

LIBS +=		-lrt -lsec -lcrypt -lmd5 -lsocket -lnsl
# More libs needed by smbd (libavahi, libgamin, ...)
LIBS4SMBD =	-lsendfile -lavahi-common -lavahi-core

#CPPFLAGS +=	-DSAMBA_VERSION_VENDOR_SUFFIX=\\\"Placeholder_for_vendor_suffix\\\"
CPPFLAGS +=	$(CPP_LARGEFILES)
CPPFLAGS +=	$(CPP_XPG6MODE)
CPPFLAGS +=	-I/usr/include/openldap

LDFLAGS +=	-m$(BITS)
LDFLAGS +=	-R/usr/lib/samba$(MACHLIBDIR)
LDFLAGS +=	-R/usr/lib/samba/private$(MACHLIBDIR)
LDFLAGS +=	$(LIBS)
$(BUILD_DIR_SMB)/.configured:	LDFLAGS +=	$(LIBS4SMBD)

ASLR_MODE =	$(ASLR_ENABLE)
LD_OPTIONS += 	$(LD_B_DIRECT)

# --enable-fhs should not be on
CONFIGURE_OPTIONS =	--exec-prefix=/usr
CONFIGURE_OPTIONS +=	--bindir=/usr/lib/samba/bin
CONFIGURE_OPTIONS +=	--sbindir=/usr/lib/samba/sbin
CONFIGURE_OPTIONS +=	--libdir=/usr/lib/samba$(MACHLIBDIR)
CONFIGURE_OPTIONS +=	--with-privatelibdir=/usr/lib/samba/private$(MACHLIBDIR)
CONFIGURE_OPTIONS +=	--sysconfdir=/etc/samba
CONFIGURE_OPTIONS +=	--with-pammodulesdir=/usr/lib/samba/security$(MACHLIBDIR)
CONFIGURE_OPTIONS +=	--datarootdir=/usr/lib/samba
CONFIGURE_OPTIONS +=	--mandir=/usr/share/man
CONFIGURE_OPTIONS +=	--htmldir=/usr/share/samba/swat/help
CONFIGURE_OPTIONS +=	--includedir=/usr/include/samba
CONFIGURE_OPTIONS +=	--with-privatedir=/etc/samba/private
CONFIGURE_OPTIONS +=	--localstatedir=/var/samba
CONFIGURE_OPTIONS +=	--with-logfilebase=/var/samba/log
CONFIGURE_OPTIONS +=	--sharedstatedir=/var/samba/com
CONFIGURE_OPTIONS +=	--libexecdir=/usr/lib/samba

CONFIGURE_OPTIONS +=	--with-static-modules=
$(BUILD_DIR_SMB)/.configured:	CONFIGURE_OPTIONS += \
	--with-shared-modules=vfs_worm,vfs_zfsacl,vfs_prealloc,vfs_cacheprime,vfs_commit,idmap_ldap,idmap_tdb2,idmap_rid,idmap_ad,idmap_hash,idmap_adex,vfs_solarisacl
$(BUILD_DIR_WINB)/.configured:	CONFIGURE_OPTIONS += \
	--with-shared-modules=idmap_ldap,idmap_tdb2,idmap_rid,idmap_ad,idmap_hash,idmap_adex
CONFIGURE_OPTIONS +=	--with-ads
CONFIGURE_OPTIONS +=	--with-winbind
CONFIGURE_OPTIONS +=	--enable-nss-wrapper
CONFIGURE_OPTIONS +=	--with-ldap
CONFIGURE_OPTIONS +=	--with-libldap=ldap_r
CONFIGURE_OPTIONS +=	--with-system-mitkrb5
CONFIGURE_OPTIONS +=	--without-ad-dc

CONFIGURE_OPTIONS +=	--nocache
CONFIGURE_OPTIONS +=	--nopyo
CONFIGURE_OPTIONS +=	--disable-rpath
CONFIGURE_OPTIONS +=	--disable-gnutls
CONFIGURE_OPTIONS +=	--bundled-libraries=ALL

#$(BUILD_DIR_SMB)/.configured:	CONFIGURE_OPTIONS +=	--with-samfs=$(PROTO_DIR)/opt/SUNWsamfs/lib

CONFIGURE_ENV += 	CC="$(CC)"
CONFIGURE_ENV += 	CPP="$(CC) -E"
CONFIGURE_ENV += 	AWK=gawk
CONFIGURE_ENV += 	PERL=$(PERL)
CONFIGURE_ENV += 	PYTHONDIR="$(PYTHON_VENDOR_PACKAGES)"
CONFIGURE_ENV += 	PYTHONARCHDIR="$(PYTHON_VENDOR_PACKAGES)/samba"
CONFIGURE_ENV += 	LD="$(LD)"
CONFIGURE_ENV +=	CFLAGS="$(CFLAGS)"
CONFIGURE_ENV +=	CPPFLAGS="$(CPPFLAGS) -I$(PROTO_DIR)/usr/include -I$(COMPONENT_DIR)/Solaris/include"
CONFIGURE_ENV +=	LINKFLAGS="$(LD_OPTIONS) $(LDFLAGS)"
CONFIGURE_ENV.64 +=	MACH64="$(MACH64)"
CONFIGURE_ENV +=	LD_EXEC_OPTIONS="$(LD_EXEC_OPTIONS)"
CONFIGURE_ENV +=	CUPS_CONFIG=$(USRBINDIR)/cups-config

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
$(BUILD_DIR_SMB)/.BDprep:	$(SOURCE_DIR)/.prep $(PROTO_DIR)/usr/include/gssapi/gssapi_krb5.h \
		$(PROTO_DIR)/usr/bin/krb5-config
	# re-create configure dir
	$(MKDIR) $(@D)
	# Clone SOURCE_DIR
	$(CLONEY) $(SOURCE_DIR) $(@D)
	# clenup of clone
	(cd $(@D) ; $(ENV) $(WAF_PATH) waf distclean $(WAFOPT1) )
	$(TOUCH) $@

# Configure of Samba + Winbind.
$(BUILD_DIR_SMB)/.configured:	$(BUILD_DIR_SMB)/.BDprep $(PROTO_DIR)/usr/lib/samba/$(MACH64)/libgssapi_krb5.so
	(cd $(@D) ; $(ENV) $(WAF_PATH) $(CONFIGURE_ENV) $(CONFIGURE_ENV.$(BITS)) \
		waf configure $(WAFOPT1) $(CONFIGURE_OPTIONS) $(CONFIGURE_OPTIONS.$(BITS)) )
	$(TOUCH) $@

# Depends on S12-only libraries from Desktop to build.
ifeq ($(BUILD_TYPE), evaluation)
$(BUILD_DIR_SMB)/.built:
$(BUILD_DIR_SMB)/.installed:
$(BUILD_DIR_WINB)/.built:
$(BUILD_DIR_WINB)/.installed:
PUBLISH_STAMP=
else

# Build of Samba + Winbind.
$(BUILD_DIR_SMB)/.built:	$(BUILD_DIR_SMB)/.configured
	(cd $(@D) ; $(ENV) $(WAF_PATH) LD_EXEC_OPTIONS="$(LD_EXEC_OPTIONS)" waf build $(WAFOPT1) )
	$(TOUCH) $@

# Install of Samba + Winbind.
$(BUILD_DIR_SMB)/.installed:	$(BUILD_DIR_SMB)/.built
	(cd $(@D) ; $(ENV) $(WAF_PATH) LD_EXEC_OPTIONS="$(LD_EXEC_OPTIONS)" waf install $(WAFOPT1) --destdir=$(PROTO_DIR) )
	$(PYTHON) -m compileall $(PROTO_DIR)/$(PYTHON_VENDOR_PACKAGES)/
	$(TOUCH) $@

# Prepare build dir for Winbind (without Samba) for different bitness.
$(BUILD_DIR_WINB)/.BDprep:	$(SOURCE_DIR)/.prep $(PROTO_DIR)/usr/include/gssapi/gssapi_krb5.h \
		$(PROTO_DIR)/usr/bin/krb5-config
	# re-create configure dir
	$(MKDIR) $(@D)
	# Clone SOURCE_DIR
	$(CLONEY) $(SOURCE_DIR) $(@D)
	# clenup of clone
	(cd $(@D) ; $(ENV) $(WAF_PATH) waf distclean $(WAFOPT1) )
	$(TOUCH) $@

# Configure of Winbind (without Samba) for different bitness.
$(BUILD_DIR_WINB)/.configured:	$(BUILD_DIR_WINB)/.BDprep $(PROTO_DIR)/usr/lib/samba/libgssapi_krb5.so
	(cd $(@D) ; $(ENV) $(WAF_PATH) $(CONFIGURE_ENV) $(CONFIGURE_ENV.$(BITS)) \
		waf configure $(WAFOPT1) $(CONFIGURE_OPTIONS) $(CONFIGURE_OPTIONS.$(BITS)) )
	$(TOUCH) $@

# Build of Winbind (without Samba) for different bitness.
WB_TARGETS =	--targets=nss_winbind,pamsmbpass,pamwinbind
$(BUILD_DIR_WINB)/.built:	$(BUILD_DIR_WINB)/.configured
	(cd $(@D) ; $(ENV) $(WAF_PATH) LD_EXEC_OPTIONS="$(LD_EXEC_OPTIONS)" waf build $(WAFOPT1) \
	    $(WB_TARGETS) )
	$(TOUCH) $@

# Installf Winbind (without Samba) for different bitness.
$(BUILD_DIR_WINB)/.installed:	$(BUILD_DIR_WINB)/.built
	/bin/sh -c "cd $(@D) ; \
	    $(INSTALL) -d $(PROTO_DIR)/usr/lib/samba$(MACHLIBDIR) ; \
	    $(INSTALL) -m 0555 -t $(PROTO_DIR)/usr/lib/samba$(MACHLIBDIR) bin/shared/!(pam_*).so* ; \
	    $(INSTALL) -d $(PROTO_DIR)/usr/lib/samba/security$(MACHLIBDIR) ; \
	    $(INSTALL) -m 0555 -t $(PROTO_DIR)/usr/lib/samba/security$(MACHLIBDIR) bin/shared/pam_*.so* ; \
	    $(INSTALL) -d $(PROTO_DIR)/usr/lib/samba/private$(MACHLIBDIR) ; \
	    $(INSTALL) -m 0555 -t $(PROTO_DIR)/usr/lib/samba/private$(MACHLIBDIR) bin/shared/private/*.so* \
	"
	$(TOUCH) $@
endif

# Set appropriate bitnesses for Samba + Winbind / Winbind (without Samba).
$(BUILD_DIR_SMB)/.configured:	BITS=64
$(BUILD_DIR_SMB)/.configured:	MACHLIBDIR=/$(MACH64)	
$(BUILD_DIR_WINB)/.configured:	BITS=32
$(BUILD_DIR_WINB)/.configured $(BUILD_DIR_WINB)/.installed:	MACHLIBDIR=

# common targets
build:		$(BUILD_DIR_SMB)/.built $(BUILD_DIR_WINB)/.built

include $(WS_MAKE_RULES)/shared-targets.mk

install:	$(BUILD_DIR_SMB)/.installed $(BUILD_DIR_WINB)/.installed

test:		$(NO_TESTS)

system-test:    $(NO_TESTS)

clean::
	$(RM) -r $(BUILD_DIR)

REQUIRED_PACKAGES += library/file-monitor/gamin
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += service/security/kerberos-5
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/crypto
REQUIRED_PACKAGES += system/library/security/gss
REQUIRED_PACKAGES += system/library/security/libsasl
REQUIRED_PACKAGES += system/library/security/libsasl2
REQUIRED_PACKAGES += system/linker
REQUIRED_PACKAGES += system/network
REQUIRED_PACKAGES += system/network/avahi
REQUIRED_PACKAGES += system/network/ldap/openldap
