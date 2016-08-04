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
# For this component, prefer 32-bit over 64-bit for now until sufficient
# testing has been performed.
BUILD_BITS= 32_and_64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		pam_pkcs11
COMPONENT_VERSION=	0.6.8
COMPONENT_PROJECT_URL=	https://sourceforge.net/projects/opensc/
COMPONENT_ARCHIVE_HASH=	\
    sha256:9d942e542ef35d0e1f990d9ff5bf9df0af84c828ed081add2eb1b4d84f0efbda
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)files/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/pam-pkcs11

TPNO=			28155

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Force regeneration of ancient autoconf scripts to fix 64-bit build detection
# and due to patches to autoconf and automake files.
COMPONENT_PREP_ACTION += (cd $(@D); autoreconf -fiv)

OPENSSL_LIBS= -lssl -lcrypto
ifeq ($(OS_VERSION),5.11)
OPENSSL_LIBS +=	-lsocket -lnsl
endif

CONFIGURE_BINDIR.32= $(USRLIB.32)/pam_pkcs11
CONFIGURE_BINDIR.64= $(USRLIB.64)/pam_pkcs11
CPPFLAGS += -I$(USRINCDIR)/openldap
CONFIGURE_OPTIONS += --datarootdir=$(ETCDIR)/security
CONFIGURE_OPTIONS += --localedir=$(USRSHARELOCALEDIR)
CONFIGURE_OPTIONS += --localstatedir=$(VARDIR)
CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --with-confdir=/etc/security/pam_pkcs11
CONFIGURE_OPTIONS += --docdir=/etc/security/pam_pkcs11
CONFIGURE_OPTIONS += OPENSSL_LIBS="$(OPENSSL_LIBS)"
CONFIGURE_OPTIONS += PCSC_CFLAGS="-I /usr/include/PCSC"
CONFIGURE_OPTIONS.32 += --with-pcsclite=no
CONFIGURE_OPTIONS.64 += --with-pcsclite=yes

REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/security/pcsc/pcsclite
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/network/ldap/openldap 
