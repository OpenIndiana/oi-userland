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

include ../../../make-rules/shared-macros.mk

#  Motivation:
# Application released under GPLv2 can not link GPLv3 libraries so the original
# libsmbclient API from samba 3.0.x released under the GPLv2 should also be
# provided for such apps.
# Currently only JDS part called gnome-VFS is using libsmbclient under the
# LSARC/2006/350/commitment.materials/materials/contracts/PSARC-2000-488-samba.txt
#
COMPONENT_NAME=		samba
COMPONENT_VERSION=	3.0.37
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://www.samba.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:bb67c0e13d4ccbd84b9200c8739393fdd9b3145b5aad216934dc670f0fcea266
COMPONENT_ARCHIVE_URL=	http://www.samba.org/samba/ftp/stable/$(COMPONENT_ARCHIVE)

include ../../../make-rules/prep.mk

SRC_OFFSET =	source
BUILD_DIR_32 = $(BUILD_DIR)/$(MACH32)/$(SRC_OFFSET)

include ../../../make-rules/configure.mk
include ../../../make-rules/ips.mk

CONFIGURE_SCRIPT = $(BUILD_DIR_32)/configure

# Build mozldap if not yet built.
$(COMPONENT_DIR)/../mozldap/build/$(MACH32)/.installed \
$(COMPONENT_DIR)/../mozldap/build/$(MACH64)/.installed:
	$(GMAKE) -C $(COMPONENT_DIR)/../mozldap install

# Clone mozldap libs and headers to $(PROTO_DIR).
# Create also $(PROTO_DIR).
$(PROTO_DIR)/.mozldap:	$(COMPONENT_DIR)/../mozldap/build/$(MACH32)/.installed \
			$(COMPONENT_DIR)/../mozldap/build/$(MACH64)/.installed
	$(MKDIR) $(PROTO_DIR)
	$(CLONEY) $(COMPONENT_DIR)/../mozldap/build/prototype/$(MACH) $(PROTO_DIR)
	$(TOUCH) $@

# Hook dependency on mozldap here.
$(BUILD_DIR_32)/.configured:	$(PROTO_DIR)/.mozldap

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
	  find $(@D)/.. -name '*.in' | sed -e 's/.in$$//' | xargs $(RM) ) ; \

# create bin ...Samba forgot to create it if it is not doing full build
COMPONENT_PRE_CONFIGURE_ACTION += \
	$(MKDIR) $(@D)/bin ;

# finish preparation
COMPONENT_PRE_CONFIGURE_ACTION += \
	( cd $(@D) ; $(CONFIG_SHELL) autogen.sh )

# local settings
CPPFLAGS +=	-I$(PROTOINCDIR)/samba/ldap6
LDFLAGS +=	-L $(PROTOUSRLIBDIR)
LIBS +=		-lrt -lsocket -lnsl
CFLAGS +=	$(studio_C99_ENABLE)
CFLAGS +=	$(CFLAGS.studio)

CONFIGURE_PREFIX = /usr/sfw
CONFIGURE_OPTIONS +=	--with-configdir=/etc/sfw
CONFIGURE_OPTIONS +=	--with-privatedir=/etc/sfw/private
CONFIGURE_OPTIONS +=	--with-lockdir=/var/samba/locks
CONFIGURE_OPTIONS +=	--with-piddir=/var/samba/locks
CONFIGURE_OPTIONS +=	--with-logfilebase=/var/samba/log
CONFIGURE_OPTIONS +=	--without-readline
CONFIGURE_OPTIONS +=	--enable-shared=yes
CONFIGURE_OPTIONS +=	--enable-static=no
CONFIGURE_OPTIONS +=	--with-static-modules=
CONFIGURE_OPTIONS +=	--with-shared-modules=
CONFIGURE_OPTIONS +=	--with-acl-support
CONFIGURE_OPTIONS +=	--with-ldap
CONFIGURE_OPTIONS +=	--with-krb5
CONFIGURE_OPTIONS +=	--with-ads
CONFIGURE_OPTIONS +=	--with-pam
CONFIGURE_OPTIONS +=	--with-automount
CONFIGURE_OPTIONS +=	--with-libsmbclient
CONFIGURE_OPTIONS +=	--with-sys-quotas=no
CONFIGURE_OPTIONS +=	--with-acl-support
CONFIGURE_OPTIONS +=	--with-aio-support
CONFIGURE_OPTIONS +=	--with-winbind

CONFIGURE_OPTIONS +=	LD="$(LD)"
CONFIGURE_OPTIONS +=	CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS +=	LDFLAGS="$(LDFLAGS)"
CONFIGURE_OPTIONS +=	LIBS="$(LIBS)"
CONFIGURE_OPTIONS +=	LDAP_LIBS=-lldap60
CONFIGURE_OPTIONS +=	CUPS_CONFIG=$(USRBINDIR)/cups-config

COMPONENT_BUILD_TARGETS = libsmbclient
COMPONENT_INSTALL_TARGETS = installclientlib

# common targets
build:		$(BUILD_32)

include ../../../make-rules/shared-targets.mk

install:	$(INSTALL_32)

test:		$(NO_TESTS)

clean::
	$(GMAKE) -C $(COMPONENT_DIR)/../mozldap clean

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../../make-rules/depend.mk
