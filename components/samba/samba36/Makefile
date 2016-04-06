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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		samba
COMPONENT_VERSION=	3.6.25
COMPONENT_REVISION=	2
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://www.samba.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:8f2c8a7f2bd89b0dfd228ed917815852f7c625b2bc0936304ac3ed63aaf83751
COMPONENT_ARCHIVE_URL=	http://us1.samba.org/samba/ftp/stable/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/samba

include $(WS_MAKE_RULES)/prep.mk

ifeq ($(strip $(USERLAND_ARCHIVES)),)
  DISTFILES_LOCATION=../
else
  DISTFILES_LOCATION=$(USERLAND_ARCHIVES)
endif

SRC_OFFSET =	source3
# Now we override paths to .built
BUILD_DIR_32 = $(BUILD_DIR)/$(MACH32)/$(SRC_OFFSET)
BUILD_DIR_64 = $(BUILD_DIR)/$(MACH64)/$(SRC_OFFSET)

include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# dirs to search for "include" in samba.p5m
PKG_OPTIONS += -I $(COMPONENT_DIR)
PKG_OPTIONS += -I $(COMPONENT_DIR)/../samba
# Set search path for pkg files
PKG_PROTO_DIRS += $(COMPONENT_DIR)

CONFIGURE_SCRIPT = $(BUILD_DIR_$(BITS))/configure

# Solve dependencies before the 32bits configure.
$(BUILD_DIR_32)/.configured: $(PROTO_DIR)/opt/SUNWsamfs/lib/libsam.so

# Start 64bits configure after the 32bits one is finished
# to have all dependecies solved.
$(BUILD_DIR_64)/.configured: $(BUILD_DIR_32)/.configured

# re-create configure dir with respect of SRC_OFFSET
# (target $(BUILD_DIR_64)/.configured does not know about
# the lower level of directories)
COMPONENT_PRE_CONFIGURE_ACTION = \
	$(RM) -r $(BUILD_DIR)/$(MACH$(BITS)) ; \
	$(MKDIR) $(BUILD_DIR)/$(MACH$(BITS)) ;

# Clone SOURCE_DIR and remove links to all of the files generated
# from *.in to distinguish then between the 32/64bits builds.
COMPONENT_PRE_CONFIGURE_ACTION += \
	( $(CLONEY) $(SOURCE_DIR) $(BUILD_DIR)/$(MACH$(BITS)) ; \
	  find $(@D)/.. -name '*.in' | sed -e 's/.in$$//' | xargs $(RM) ) ;

# finish preparation
COMPONENT_PRE_CONFIGURE_ACTION += \
	( cd $(@D) ; $(CONFIG_SHELL) autogen.sh )

COMPONENT_PRE_BUILD_ACTION = $(ENV) ; echo $(COMPONENT_BUILD_ENV)

# It should create $(PROTO_DIR).
$(PROTO_DIR)/opt/SUNWsamfs/lib/libsam.so: ../samba/Solaris/libsam.c
	$(MKDIR) $(PROTO_DIR)/opt/SUNWsamfs/lib
	$(CC) -shared -fPIC -DPIC -Wl,-hlibsam.so ../samba/Solaris/libsam.c \
		-I$(COMPONENT_DIR)/../samba/Solaris/include \
		-o $(PROTO_DIR)/opt/SUNWsamfs/lib/libsam.so

CFLAGS.studio	+=	$(studio_C99_ENABLE)
CFLAGS.gcc	+=	-std=c99

SAMBA36DIR	=	/usr/lib/samba/samba36
CONFIGURE_PREFIX =	$(SAMBA36DIR)
SAMBA36INCDIR	=	$(SAMBA36DIR)/include

#CPPFLAGS +=	-DSAMBA_VERSION_VENDOR_SUFFIX=\\\"Placeholder_for_vendor_suffix\\\"
CPPFLAGS +=	$(CPP_LARGEFILES)
CPPFLAGS +=	$(CPP_XPG6MODE)
CPPFLAGS +=	-I$(PROTO_DIR)$(SAMBA36INCDIR) -I$(USRINCDIR)/samba/ldap6 -I$(BUILD_DIR_$(BITS))/include

LIBS +=		-lrt -lsocket -lnsl
# libavahi is not for 64bits but we do not need it
LIBS32 =	-lsendfile -lavahi-common -lavahi-core

LDFLAGS +=	-L $(PROTO_DIR)$(CONFIGURE_LIBDIR.$(BITS)) -R$(CONFIGURE_LIBDIR.$(BITS))

LDFLAGS.32 +=	-L $(PROTO_DIR)/opt/SUNWsamfs/lib
LDFLAGS.32 +=	$(LIBS) $(LIBS32)

LDFLAGS.64 +=	$(LIBS)

ifeq ($(COMPILER), studio)
LDFLAGS +=	$(LDFLAGS.$(BITS)) $(LD_OPTIONS)
else
LDFLAGS +=      $(LDFLAGS.$(BITS)) $(LD_OPTIONS:%=-Xlinker %)
endif

CONFIGURE_OPTIONS +=	--includedir=$(SAMBA36INCDIR)
CONFIGURE_OPTIONS +=	--sysconfdir=/etc/samba
CONFIGURE_OPTIONS +=	--with-configdir=/etc/samba
CONFIGURE_OPTIONS +=	--with-privatedir=/etc/samba/private
CONFIGURE_OPTIONS +=	--with-swatdir=$(SAMBA36DIR)/swat
CONFIGURE_OPTIONS +=	--localstatedir=/var/samba
CONFIGURE_OPTIONS +=	--with-lockdir=/var/samba/locks
CONFIGURE_OPTIONS +=	--with-piddir=/var/samba/locks
CONFIGURE_OPTIONS +=	--with-logfilebase=/var/samba/log
CONFIGURE_OPTIONS +=	--enable-shared=yes
CONFIGURE_OPTIONS +=	--enable-static=no
CONFIGURE_OPTIONS.32 +=	--with-static-modules=vfs_solarisacl
CONFIGURE_OPTIONS.32 += --with-shared-modules=vfs_worm,vfs_zfsacl,vfs_aio_pthread,vfs_samfs,vfs_prealloc,vfs_cacheprime,vfs_commit,idmap_ldap,idmap_tdb2,idmap_rid,idmap_ad,idmap_hash,idmap_adex
CONFIGURE_OPTIONS.64 +=	--with-static-modules=
CONFIGURE_OPTIONS.64 += --with-shared-modules=
CONFIGURE_OPTIONS +=	--with-readline
CONFIGURE_OPTIONS +=	--enable-cups
CONFIGURE_OPTIONS +=	--with-aio-support
CONFIGURE_OPTIONS +=	--with-acl-support
CONFIGURE_OPTIONS +=	--with-ads
CONFIGURE_OPTIONS +=	--with-ldap
CONFIGURE_OPTIONS +=	--with-automount
CONFIGURE_OPTIONS +=	--with-dnsupdate=no
CONFIGURE_OPTIONS +=	--with-pam
CONFIGURE_OPTIONS +=	--with-winbind

CONFIGURE_OPTIONS += 	LD="$(LD)"
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS.32 +=	CPPFLAGS="$(CPPFLAGS) -I$(COMPONENT_DIR)/../samba/Solaris/include"
CONFIGURE_OPTIONS.64 +=	CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_OPTIONS +=	LDFLAGS="$(LDFLAGS)"
CONFIGURE_OPTIONS.32 +=	LIBS="$(LIBS) $(LIBS32)"
CONFIGURE_OPTIONS.64 +=	LIBS="$(LIBS)"
CONFIGURE_OPTIONS +=	LDAP_LIBS="-lldap60 -lssldap60"
CONFIGURE_OPTIONS +=	CUPS_CONFIG=$(USRBINDIR)/cups-config
CONFIGURE_OPTIONS.32 +=	SAMFS_LIBS="-R/opt/SUNWsamfs/lib -lsam"

# Samba targets
$(BUILD_32): COMPONENT_BUILD_TARGETS = showlayout all libsmbclient modules smbtorture
$(BUILD_64): COMPONENT_BUILD_TARGETS = showlayout nss_modules pam_modules pam_smbpass wins pam_winbind
$(INSTALL_32): COMPONENT_INSTALL_TARGETS = showlayout install-everything
$(INSTALL_64): COMPONENT_INSTALL_TARGETS = showlayout installpammodules

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk
