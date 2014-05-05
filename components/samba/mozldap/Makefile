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

COMPONENT_NAME=		mozldap
COMPONENT_VERSION=	6.0.7
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://wiki.mozilla.org/LDAP_C_SDK/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:ec9884b56b31961d287190323764af7f3b00ad2658d5f3005fa8dc71c637e54c
COMPONENT_ARCHIVE_URL=	ftp://ftp.mozilla.org/pub/mozilla.org/directory/c-sdk/releases/v$(COMPONENT_VERSION)/src/$(COMPONENT_ARCHIVE)

include ../../../make-rules/prep.mk
include ../../../make-rules/configure.mk

# Define a private space
PATCH_LEVEL =	0
SRC_OFFSET =	c-sdk
CONFIGURE_SCRIPT = $(SOURCE_DIR)/$(SRC_OFFSET)/configure

MPS_INCDIR =	$(USRINCDIR)/mps

MPS_LIBDIR.32 =	$(USRLIBDIR)/mps
MPS_LIBDIR.64 =	$(USRLIBDIR)/mps/$(MACH64)
MPS_LIBDIR =	$(MPS_LIBDIR.$(BITS))

CONFIGURE_OPTIONS += --sysconfdir=/etc/samba
CONFIGURE_OPTIONS += --with-nss-inc=$(MPS_INCDIR)
CONFIGURE_OPTIONS += --with-nspr-inc=$(MPS_INCDIR)
CONFIGURE_OPTIONS += --enable-optimize
CONFIGURE_OPTIONS += --with-native-threads
CONFIGURE_OPTIONS += --enable-ipv6
CONFIGURE_OPTIONS += --with-dist-prefix=$(PROTO_DIR)
CONFIGURE_OPTIONS += --with-nss-lib=$(MPS_LIBDIR)
CONFIGURE_OPTIONS += --with-nspr-lib=$(MPS_LIBDIR)
CONFIGURE_OPTIONS += --with-dist-libdir=$(PROTO_DIR)/$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS += --with-rpath=$(MPS_LIBDIR)

CONFIGURE_OPTIONS.64 += --enable-64bit

CONFIGURE_OPTIONS += AR=/usr/ccs/bin/ar
CONFIGURE_OPTIONS += PERL="$(PERL)"
CONFIGURE_OPTIONS += BUILD_OPT=1 NS_USE_GCC=0

COMPONENT_PREP_ACTION = \
 ( cd $(SOURCE_DIR)/$(SRC_OFFSET) ; autoconf -f )

# common targets
build:		$(BUILD_32_and_64)

include ../../../make-rules/shared-targets.mk

# mozldap proto looks to ugly after "gmake install ..."
# so some cleanup is needed
COMPONENT_POST_INSTALL_ACTION = \
 $(RM) -r $(PROTOUSRINCDIR)/samba ; $(MKDIR) $(PROTOUSRINCDIR)/samba ; \
 test -d $(PROTOUSRINCDIR)/samba/ldap6 || $(MV) $(PROTO_DIR)/public/ldap $(PROTOUSRINCDIR)/samba/ldap6 ; \
 $(RM) -r $(PROTO_DIR)/public $(PROTO_DIR)/etc $(PROTOBINDIR) ; \
 $(RM) $(PROTOUSRLIBDIR)/*.a $(PROTOUSRLIBDIR64)/*.a

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../../make-rules/depend.mk
