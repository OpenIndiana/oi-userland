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
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		openssh
COMPONENT_VERSION=	7.2p2
HUMAN_VERSION=		$(COMPONENT_VERSION)
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_REVISION=	2

# Version for IPS.  The encoding rules are:
#   OpenSSH <x>.<y>p<n>     => IPS <x>.<y>.0.<n>
#   OpenSSH <x>.<y>.<z>p<n> => IPS <x>.<y>.<z>.<n>
IPS_COMPONENT_VERSION=	7.2.0.2

COMPONENT_PROJECT_URL=	http://www.openssh.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:a72781d1a043876a224ff1b0032daa4094d87565a68528759c1c2cab5482548c
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

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

# Because of certain set up requirement, the regress test suite is ported to
# the STC gate.
test:		$(NO_TESTS)

REQUIRED_PACKAGES += library/libedit
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += service/security/kerberos-5
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-4-runtime
REQUIRED_PACKAGES += system/library/security/gss
