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

COMPONENT_NAME=		openldap
COMPONENT_VERSION=	2.4.44
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	OpenLDAP is an open source implementation of the Lightweight Directory Access Protocol
COMPONENT_PROJECT_URL=	http://www.openldap.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH= \
    sha256:d7de6bf3c67009c95525dde3a0212cc110d0a70b92af2af8e3ee800e81b88400
COMPONENT_ARCHIVE_URL=	ftp://ftp.openldap.org/pub/OpenLDAP/openldap-release/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	library/openldap
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=	openldap license

SDFVER=			sdf-2.001
SDFBLIB=		$(BUILD_DIR_32)/${SDFVER}/blib

COMPONENT_ARCHIVE_1= $(SDFVER).tar.gz
COMPONENT_ARCHIVE_HASH_1= \
    sha256:6f9bcdc884a9f450208c740e45effdfeb7e65c689f57b05d3c15208193a8a6ea
COMPONENT_ARCHIVE_URL_1= ftp://ftp.eenet.ee/pub/cpan/authors/id/I/IA/IANC/$(COMPONENT_ARCHIVE_1)


include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk


COMPONENT_PRE_CONFIGURE_ACTION = \
        ($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_PRE_BUILD_ACTION = \
	 ( $(CP) $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_1) $(BUILD_DIR_32); \
	 cd $(BUILD_DIR_32); \
	 gzip -dc $(COMPONENT_ARCHIVE_1) | tar xopf -; \
	 rm $(COMPONENT_ARCHIVE_1); \
	  cd $(SDFVER); $(PERL) Makefile.PL; \
		$(GMAKE))

# we need to enable large file support and build PIC for our shared libraries
CFLAGS += $(CPP_LARGEFILES) $(CC_PIC)

CONFIGURE_ENV += "ac_cv_lib_net_main=no"
CONFIGURE_ENV += "ac_cv_lib_net_socket==no"
CONFIGURE_ENV += "ac_cv_lib_inet_socket==no"

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS.32 += --libexecdir=/usr/lib
CONFIGURE_OPTIONS.64 += --libexecdir=/usr/lib/$(MACH64)
CONFIGURE_OPTIONS += --localstatedir=/var/openldap
CONFIGURE_OPTIONS += --includedir=$(USRINCDIR)/openldap
CONFIGURE_OPTIONS += --docdir=$(USRSHAREDOCDIR)
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-overlays
CONFIGURE_OPTIONS += --disable-dynamic
CONFIGURE_OPTIONS += --enable-crypt
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --enable-bdb
CONFIGURE_OPTIONS += --enable-hdb
CONFIGURE_OPTIONS += --enable-null
CONFIGURE_OPTIONS += --enable-ldap
CONFIGURE_OPTIONS += --enable-passwd	 
CONFIGURE_OPTIONS += --enable-shell
CONFIGURE_OPTIONS += --with-cyrus-sasl
CONFIGURE_OPTIONS += --with-threads
CONFIGURE_OPTIONS += --with-tls=openssl

PROTOULD = $(PROTOUSRLIBDIR)
COMPONENT_TEST_ENV += LD_LIBRARY_PATH="$(PROTOULD):$(PROTOULD)/$(MACH64):"
COMPONENT_TEST_ARGS += -e

$(INSTALL_32): COMPONENT_POST_INSTALL_ACTION = \
	for f in $(PROTOUSRBINDIR)/ldap* $(PROTOUSRLIBDIR)/slapd ; do \
		/usr/bin/elfedit -e "dyn:runpath ''" $$f; \
	done ; \

$(INSTALL_64): COMPONENT_POST_INSTALL_ACTION = \
	for f in $(PROTOUSRBINDIR64)/ldap* $(PROTOUSRLIBDIR64)/slapd ; do \
		/usr/bin/elfedit -e "dyn:runpath ''" $$f; \
	done ; \

# common targets
build:	$(BUILD_32_and_64)
	(cd $(BUILD_DIR_32)/doc/guide/admin; \
	$(PERL) -I$(SDFBLIB)/lib $(SDFBLIB)/script/sdf -2html guide.sdf; \
	$(PERL) -I$(SDFBLIB)/lib $(SDFBLIB)/script/sdf -2html index.sdf)

install:	$(INSTALL_32_and_64)

# build does this always
test:	$(TEST_32_and_64)

REQUIRED_PACKAGES += database/berkeleydb-5
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/libsasl
