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

# Samba does not work properly on i386 when built by studio with -xO3+.
ifeq ($(MACH), sparc)
# parallelize up to 64 concurent tasks for sparc
WAFOPT1 = -j64
else
# parallelize up to 16 concurent tasks for i386
WAFOPT1 = -j16
endif

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		samba
COMPONENT_VERSION=	4.4.16
COMPONENT_REVISION=	1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_SUMMARY=	A library that permits GPLv2 applications to manipulate CIFS/SMB network resources
COMPONENT_PROJECT_URL=	http://www.samba.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:2681f6d9d838d90273f151539331a2051b2292fc8784d4bbc416caae5d0c438e
COMPONENT_ARCHIVE_URL=	http://us1.samba.org/samba/ftp/stable/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	library/samba/libsmbclient
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/prep.mk

# waf
WAF_PATH	=	PATH=$(BUILD_DIR)/samba/buildtools/bin:$(PROTO_DIR)/usr/bin:$$PATH:/usr/perl5/bin
# Verbosed waf produces unreadable output if parallelized.
# Uncomment to enable verbose build.
#override WAFOPT1	=	-v -j1

include $(WS_MAKE_RULES)/ips.mk

# Compiler settings
CFLAGS	+=	$($(COMPILER)_C99_ENABLE)

LIBS +=		-lrt -lsec -lcrypt -lmd5 -lsocket -lnsl

LDFLAGS.32 +=   -R/usr/lib/libsmbclient
LDFLAGS.32 +=   -R/usr/lib/libsmbclient/private
LDFLAGS += $(LDFLAGS.$(BITS))

CPPFLAGS +=	$(CPP_LARGEFILES)
CPPFLAGS +=	$(CPP_XPG6MODE)
CPPFLAGS +=	-I/usr/include/openldap

LD_OPTIONS += 	-B direct

# Force use of gnutls-3 pkgconfig during 2.x->3.x transition
GNUTLS_PKG_CONFIG_PATH_32 = /usr/lib/pkgconfig/gnutls-3
GNUTLS_PKG_CONFIG_PATH_64 = /usr/lib/$(MACH64)/pkgconfig/gnutls-3
PKG_CONFIG_PATH = $(GNUTLS_PKG_CONFIG_PATH_$(BITS)):$(PKG_CONFIG_PATH.$(BITS))

LDFLAGS.32 += -L/usr/lib/gnutls-3 -R/usr/lib/gnutls-3
LDFLAGS.64 += -L/usr/lib/$(MACH64)/gnutls-3 -R/usr/lib/$(MACH64)/gnutls-3

# !!! Note, this is not a configure.mk-based Makefile !!!
CONFIGURE_OPTIONS =	--prefix=/usr
CONFIGURE_OPTIONS +=	--sysconfdir=/etc/samba
CONFIGURE_OPTIONS +=	--includedir=/usr/include/libsmbclient
CONFIGURE_OPTIONS +=	--with-privatedir=/etc/samba/private
CONFIGURE_OPTIONS +=	--localstatedir=/var/samba
CONFIGURE_OPTIONS +=	--with-logfilebase=/var/samba/log
CONFIGURE_OPTIONS +=	--sharedstatedir=/var/samba/com
CONFIGURE_OPTIONS.32 += --libdir=/usr/lib/libsmbclient
CONFIGURE_OPTIONS.64 += --libdir=/usr/lib/libsmbclient/$(MACH64)
CONFIGURE_OPTIONS +=	--with-static-modules=
CONFIGURE_OPTIONS +=	--with-shared-modules=
CONFIGURE_OPTIONS +=	--with-ads
CONFIGURE_OPTIONS +=	--with-winbind
CONFIGURE_OPTIONS +=	--with-ldap
CONFIGURE_OPTIONS +=	--with-libldap=ldap_r
CONFIGURE_OPTIONS +=	--nocache
CONFIGURE_OPTIONS +=	--nopyo
CONFIGURE_OPTIONS +=	--disable-rpath
CONFIGURE_OPTIONS +=	--disable-rpath-private-install 
CONFIGURE_OPTIONS +=	--bundled-libraries=ALL

CONFIGURE_ENV += 	CC="$(CC)"
CONFIGURE_ENV += 	CPP="$(CC) -E"
CONFIGURE_ENV += 	AWK=gawk
CONFIGURE_ENV += 	PERL=$(PERL)
CONFIGURE_ENV += 	LD="$(LD)"
CONFIGURE_ENV +=	CFLAGS="$(CFLAGS)"
CONFIGURE_ENV +=     	CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_ENV += 	LDFLAGS="$(LDFLAGS)"
CONFIGURE_ENV +=	LD_EXEC_OPTIONS="$(LD_EXEC_OPTIONS)"
CONFIGURE_ENV +=	CUPS_CONFIG=$(USRBINDIR)/cups-config
CONFIGURE_ENV +=	PKG_CONFIG_PATH="$(PKG_CONFIG_PATH)"

# Build targets for WAF:
# (motivation) Samba started to use WAF (build system from Google) from the 3.x
# (as a parallel build system) but Samba4 discontinued the use of auto tools
# definitively.
# (note) .BDprep target is an additional step between .prep and .configure
# targets. It was added because there were problems with libtool-like phase of
# WAF when the not "prepared well". "waf distclean" on CLONEY'ed BUILD_DIR is
# enough.

# Prepare build dir for Samba
$(BUILD_DIR_32)/.BDprep:	$(SOURCE_DIR)/.prep
	# re-create configure dir
	$(MKDIR) $(@D)
	# Clone SOURCE_DIR
	$(CLONEY) $(SOURCE_DIR) $(@D)
	# clenup of clone
	(cd $(@D) ; $(ENV) $(WAF_PATH) $(PYTHON) $(SOURCE_DIR)/buildtools/bin/waf distclean $(WAFOPT1) )
	$(TOUCH) $@

# Configure of Samba
$(BUILD_DIR_32)/.configured:	$(BUILD_DIR_32)/.BDprep
	(cd $(@D) ; $(ENV) $(WAF_PATH) $(CONFIGURE_ENV) \
		$(CONFIGURE_ENV.32) $(PYTHON) $(SOURCE_DIR)/buildtools/bin/waf configure $(WAFOPT1) $(CONFIGURE_OPTIONS) $(CONFIGURE_OPTIONS.32) )
	$(TOUCH) $@

# Build of Samba + Winbind.
$(BUILD_DIR_32)/.built:	$(BUILD_DIR_32)/.configured
	(cd $(@D) ; $(ENV) $(WAF_PATH) LD_EXEC_OPTIONS="$(LD_EXEC_OPTIONS)" $(PYTHON) $(SOURCE_DIR)/buildtools/bin/waf build $(WAFOPT1) --targets=smbclient)
	$(TOUCH) $@

# Install of Samba + Winbind.
$(BUILD_DIR_32)/.installed:	$(BUILD_DIR_32)/.built
	(cd $(@D) ; $(ENV) $(WAF_PATH) LD_EXEC_OPTIONS="$(LD_EXEC_OPTIONS)" $(PYTHON) $(SOURCE_DIR)/buildtools/bin/waf install $(WAFOPT1) --targets=smbclient --destdir=$(PROTO_DIR) )
	$(TOUCH) $@

$(BUILD_DIR)/.pc.fixed:	$(INSTALL_32)
	$(GSED) -i -e '/^Libs/s:-L$${libdir}:-L$${libdir} -R$${libdir}:' $(PROTO_DIR)/usr/lib/libsmbclient/pkgconfig/*.pc
	$(TOUCH) $@

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32) $(BUILD_DIR)/.pc.fixed

test:		$(NO_TESTS)

clean::
	$(RM) -r $(BUILD_DIR)

REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/security/libgcrypt
