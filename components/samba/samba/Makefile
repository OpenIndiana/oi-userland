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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#

# parfait seems to spin when looking at the .bc files, so
# for now disable it.
PARFAIT_BUILD=no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		samba
COMPONENT_VERSION=	3.6.4
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://www.samba.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:590ac2fc7f6dd70e947b3aded5fcb4431a5abba4dc3cc1bec566627e132b5914
COMPONENT_ARCHIVE_URL=	http://us1.samba.org/samba/ftp/stable/$(COMPONENT_ARCHIVE)

COMPONENT_NAME_1=		docbook-xsl
COMPONENT_VERSION_1=		1.76.1
COMPONENT_SRC_1=		$(COMPONENT_NAME_1)-$(COMPONENT_VERSION_1)
COMPONENT_ARCHIVE_1=		$(COMPONENT_SRC_1).tar.bz2
COMPONENT_ARCHIVE_HASH_1=	\
    sha256:d6bdfd76f672c810299c71443e5127431ffb87d2c79d818aee72c86eaccd312c
COMPONENT_ARCHIVE_URL_1=	http://sourceforge.net/projects/docbook/files/$(COMPONENT_NAME_1)/$(COMPONENT_VERSION_1)/$(COMPONENT_ARCHIVE_1)

COMPONENT_ARCHIVE_2=		libsam-LGPL.tar
COMPONENT_ARCHIVE_HASH_2=	\
    sha256:4324f2c4a9ba94f1165c5922f166636621681b09d635257d921f6df654e7191e
COMPONENT_ARCHIVE_URL_2=	http://hub.opensolaris.org/bin/download/Project+samqfs/files/libsam%2DLGPL.tar

# Samba does not work properly on i86 when built by studio.
# Samba on SPARC has serious performance drop when built by gcc.
ifeq ($(MACH), sparc)
COMPILER = studio
else
COMPILER = gcc
endif

include ../../../make-rules/prep.mk

SRC_OFFSET =	source3
# Now we override paths to .built
BUILD_DIR_32 = $(BUILD_DIR)/$(MACH32)/$(SRC_OFFSET)
BUILD_DIR_64 = $(BUILD_DIR)/$(MACH64)/$(SRC_OFFSET)

include ../../../make-rules/configure.mk
include ../../../make-rules/ips.mk

CONFIGURE_SCRIPT = $(BUILD_DIR_$(BITS))/configure

PKG_OPTIONS += -I $(COMPONENT_DIR)

DOCS-XML_DIR =	$(SOURCE_DIR)/docs-xml

# Build mozldap if not yet built.
$(COMPONENT_DIR)/../mozldap/build/$(MACH32)/.installed \
$(COMPONENT_DIR)/../mozldap/build/$(MACH64)/.installed:
	$(GMAKE) -C $(COMPONENT_DIR)/../mozldap install

# Clone mozldap libs and headers to $(PROTO_DIR).
# Create also $(PROTO_DIR).
$(PROTO_DIR)/.mozldap:	   $(COMPONENT_DIR)/../mozldap/build/$(MACH32)/.installed \
			   $(COMPONENT_DIR)/../mozldap/build/$(MACH64)/.installed
	$(MKDIR) $(PROTO_DIR)
	$(CLONEY) $(COMPONENT_DIR)/../mozldap/build/prototype/$(MACH) $(PROTO_DIR)
	$(TOUCH) $@

# Solve dependencies before the 32bits configure.
$(BUILD_DIR_32)/.configured: $(DOCS-XML_DIR)/.built $(PROTO_DIR)/.mozldap \
			$(PROTO_DIR)/opt/SUNWsamfs/lib/libsam.so

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

# Depend on $(PROTO_DIR)/.mozldap because this target creates $(PROTO_DIR).
$(PROTO_DIR)/opt/SUNWsamfs/lib/libsam.so: Solaris/libsam.c \
		$(COMPONENT_ARCHIVE_2) $(PROTO_DIR)/.mozldap
	$(MKDIR) $(PROTO_DIR)/opt/SUNWsamfs/lib
	$(CC.studio.32) -G $(studio_PIC) -hlibsam.so Solaris/libsam.c \
		-o $(PROTO_DIR)/opt/SUNWsamfs/lib/libsam.so
	cd $(BUILD_DIR) ; $(UNPACK) $(UNPACK_ARGS) ../$(COMPONENT_ARCHIVE_2)

CFLAGS.studio	+=	$(studio_C99_ENABLE)
CFLAGS.gcc	+=	-std=c99

CPPFLAGS +=	$(CPP_LARGEFILES)
CPPFLAGS +=	$(CPP_XPG6MODE)
CPPFLAGS +=	-I$(PROTOUSRINCDIR)/samba -I$(PROTOUSRINCDIR)/samba/ldap6 -I$(BUILD_DIR_$(BITS))/include

LIBS +=		-lrt -lsocket -lnsl
# libavahi is not for 64bits but we do not need it
LIBS32 =	-lsendfile -lavahi-common -lavahi-core

LDFLAGS.32 +=	-L $(PROTOUSRLIBDIR)
LDFLAGS.32 +=	-L $(PROTOUSRLIBDIR)/samba -R/usr/lib/samba
LDFLAGS.32 +=	-L $(PROTO_DIR)/opt/SUNWsamfs/lib
LDFLAGS.32 +=	$(LIBS) $(LIBS32)

LDFLAGS.64 +=	-L $(PROTOUSRLIBDIR)/$(MACH64)
LDFLAGS.64 +=	-L $(PROTOUSRLIBDIR)/samba/$(MACH64) -R/usr/lib/samba/$(MACH64)
LDFLAGS.64 +=	$(LIBS)

ifeq ($(COMPILER), studio)
LDFLAGS +=	$(LDFLAGS.$(BITS)) $(LD_OPTIONS)
else
LDFLAGS +=      $(LDFLAGS.$(BITS)) $(LD_OPTIONS:%=-Xlinker %)
endif

CONFIGURE_LIBDIR.32 = /usr/lib/samba
CONFIGURE_LIBDIR.64 = /usr/lib/samba/$(MACH64)
CONFIGURE_OPTIONS +=	--includedir=/usr/include/samba
CONFIGURE_OPTIONS +=	--sysconfdir=/etc/samba
CONFIGURE_OPTIONS +=	--with-configdir=/etc/samba
CONFIGURE_OPTIONS +=	--with-privatedir=/etc/samba/private
CONFIGURE_OPTIONS +=	--with-swatdir=/usr/share/samba/swat
CONFIGURE_OPTIONS +=	--localstatedir=/var/samba
CONFIGURE_OPTIONS +=	--with-lockdir=/var/samba/locks
CONFIGURE_OPTIONS +=	--with-piddir=/var/samba/locks
CONFIGURE_OPTIONS +=	--with-logfilebase=/var/samba/log
CONFIGURE_OPTIONS +=	--enable-shared=yes
CONFIGURE_OPTIONS +=	--enable-static=no
CONFIGURE_OPTIONS +=	--with-static-modules=vfs_solarisacl
CONFIGURE_OPTIONS.32 += --with-shared-modules=vfs_zfsacl,vfs_samfs,vfs_prealloc,vfs_cacheprime,vfs_commit,idmap_ldap,idmap_tdb2,idmap_rid,idmap_ad,idmap_hash,idmap_adex
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
CONFIGURE_OPTIONS.32 +=	CPPFLAGS="$(CPPFLAGS) -I$(BUILD_DIR)/libsam-LGPL/include"
CONFIGURE_OPTIONS.64 +=	CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_OPTIONS +=	LDFLAGS="$(LDFLAGS)"
CONFIGURE_OPTIONS.32 +=	LIBS="$(LIBS) $(LIBS32)"
CONFIGURE_OPTIONS.64 +=	LIBS="$(LIBS)"
CONFIGURE_OPTIONS +=	LDAP_LIBS=-lldap60
CONFIGURE_OPTIONS +=	CUPS_CONFIG=$(USRBINDIR)/cups-config
CONFIGURE_OPTIONS.32 +=	SAMFS_LIBS="-R/opt/SUNWsamfs/lib -lsam"

# download recent docbook-xsl and unpack it
$(BUILD_DIR)/$(COMPONENT_SRC_1)/.docbook-xsl-prep: $(COMPONENT_ARCHIVE_1) \
		$(SOURCE_DIR)/.prep $(PROTO_DIR)/.mozldap
	cd $(BUILD_DIR) ; $(UNPACK) $(UNPACK_ARGS) ../$(COMPONENT_ARCHIVE_1)
	cd $(DOCS-XML_DIR) ; $(GMAKE) clobber
	$(TOUCH) $@

# create also the: $(DOCS-XML_DIR)/configure and $(DOCS-XML_DIR)/build/catalog.xml
# needed to buils docs from XML sources
$(DOCS-XML_DIR)/Makefile.settings: $(BUILD_DIR)/$(COMPONENT_SRC_1)/.docbook-xsl-prep
	cd $(@D) ; $(GMAKE) configure \
		BUILDDIR=$(@D) \
		DOCBOOKXSLVER=$(COMPONENT_VERSION_1) \
		DOCBOOKXSLDIR=$(BUILD_DIR)/$(COMPONENT_SRC_1)

# Build docs from DocBook XML sources.
$(DOCS-XML_DIR)/.built: $(DOCS-XML_DIR)/Makefile.settings
	cd $(@D) ; \
	env - XML_CATALOG_FILES="catalog.xml file:///$(@D)/build/catalog.xml" \
		$(GMAKE) smbdotconf/parameters.all.xml manpages3 htmlman3
	$(TOUCH) $@

$(PROTO_DIR)/etc/samba/smb.conf-example: $(BUILD_32)
	$(MKDIR) $(@D)
	sed -f $(COMPONENT_DIR)/Solaris/smbconf.sed > $@ \
	   $(BUILD_DIR)/$(MACH32)/examples/smb.conf.default

# Samba targets
$(BUILD_32): COMPONENT_BUILD_TARGETS = showlayout all libsmbclient modules smbtorture
$(BUILD_64): COMPONENT_BUILD_TARGETS = showlayout nss_modules pam_modules pam_smbpass wins pam_winbind
$(INSTALL_32): COMPONENT_INSTALL_TARGETS = showlayout install-everything
$(INSTALL_64): COMPONENT_INSTALL_TARGETS = showlayout installpammodules

# common targets
build:		$(BUILD_32_and_64)

include ../../../make-rules/shared-targets.mk

install:	$(PROTO_DIR)/etc/samba/smb.conf-example $(INSTALL_32_and_64)

test:		$(NO_TESTS)

clean::
	$(GMAKE) -C $(COMPONENT_DIR)/../mozldap clean

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../../make-rules/depend.mk
