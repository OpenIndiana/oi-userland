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
# Copyright (c) 2013, 2015, Oracle and/or its affiliates. All rights reserved.
# Copyright 2018 Till Wegmüller
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		openssh
COMPONENT_VERSION=	7.4p1
COMPONENT_REVISION=	3
HUMAN_VERSION=		$(COMPONENT_VERSION)
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)

# Version for IPS.  The encoding rules are:
#   OpenSSH <x>.<y>p<n>     => IPS <x>.<y>.0.<n>
#   OpenSSH <x>.<y>.<z>p<n> => IPS <x>.<y>.<z>.<n>
IPS_COMPONENT_VERSION=	7.4.0.1

COMPONENT_PROJECT_URL=	http://www.openssh.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:1b1fc4a14e2024293181924ed24872e6f2e06293f3e8926a376b8aec481f19d1
COMPONENT_ARCHIVE_URL=	http://mirror.yandex.ru/pub/OpenBSD/OpenSSH/portable/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=utility/openssh

TPNO_OPENSSH=		21980
TPNO_GSSKEX=		20377

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Enable ASLR for this component
# ASLR_MODE = $(ASLR_ENABLE)

COMPONENT_PREP_ACTION = (cd $(@D) ; autoreconf -f -i)

CFLAGS += -DSET_USE_PAM
CFLAGS += -DNO_UID_RESTORATION_TEST
CFLAGS += -DDEPRECATE_SUNSSH_OPT
CFLAGS += -DKRB5_BUILD_FIX
CFLAGS += -DDTRACE_SFTP
CFLAGS += -DDISABLE_BANNER
CFLAGS += -DPAM_ENHANCEMENT
CFLAGS += -DPAM_BUGFIX
CFLAGS += -DOPTION_DEFAULT_VALUE
CFLAGS += -DHAVE_EVP_SHA256
CFLAGS += -DPER_SESSION_XAUTHFILE
CFLAGS += -I/usr/include/kerberosv5/

# We need to disable lazyloading of dynamic dependent libraries. During the
# pre-authentication phase, sshd will chroot to /var/empty which doesn't
# contain any files. If we use lazyloading, sshd will fail to find any
# libraries that it needs.
LDFLAGS += -B direct -z nolazyload

CONFIGURE_OPTIONS += --with-audit=solaris
CONFIGURE_OPTIONS += --with-libedit
CONFIGURE_OPTIONS += --with-kerberos5
CONFIGURE_OPTIONS += --with-pam
CONFIGURE_OPTIONS += --with-sandbox=solaris
CONFIGURE_OPTIONS += --with-solaris-contracts
CONFIGURE_OPTIONS += --with-solaris-privs
CONFIGURE_OPTIONS += --with-tcp-wrappers
CONFIGURE_OPTIONS += --with-4in6
CONFIGURE_OPTIONS += --with-xauth=/usr/bin/xauth
CONFIGURE_OPTIONS += --enable-strip=no
CONFIGURE_OPTIONS += --without-rpath
CONFIGURE_OPTIONS += --libexecdir=/usr/lib/ssh
CONFIGURE_OPTIONS += --sbindir=/usr/lib/ssh
CONFIGURE_OPTIONS += --sysconfdir=/etc/ssh
CONFIGURE_OPTIONS += --bindir=/usr/bin
CONFIGURE_OPTIONS += --disable-lastlog

COMPONENT_POST_INSTALL_ACTION += $(INSTALL) -Dm755 $(SOURCE_DIR)/contrib/ssh-copy-id $(PROTOUSRBINDIR)/ssh-copy-id;
COMPONENT_POST_INSTALL_ACTION += $(INSTALL) -Dm644 $(SOURCE_DIR)/contrib/ssh-copy-id.1 $(PROTOUSRSHAREMAN1DIR)/ssh-copy-id.1;

# common targets
build:		$(BUILD_64)

install:	$(INSTALL_64)

# Because of certain set up requirement, the regress test suite is ported to
# the STC gate.
test:		$(NO_TESTS)

REQUIRED_PACKAGES += library/libedit
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += service/security/kerberos-5
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-6-runtime
REQUIRED_PACKAGES += system/library/security/gss
