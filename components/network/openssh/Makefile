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
# Copyright 2019 Michal Nowak
#

BUILD_BITS= 64
OPENSSL_VERSION= 3.1
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		openssh
#   OpenSSH <x>.<y>p<n>     => IPS <x>.<y>.0.<n>
#   OpenSSH <x>.<y>.<z>p<n> => IPS <x>.<y>.<z>.<n>
COMPONENT_VERSION=	9.3.0.2
HUMAN_VERSION=		9.3p2
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	OpenSSH client and associated utilities
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_PROJECT_URL=	https://www.openssh.org
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:200ebe147f6cb3f101fd0cdf9e02442af7ddca298dffd9f456878e7ccac676e8
COMPONENT_ARCHIVE_URL=	https://ftp.openbsd.org/pub/OpenBSD/OpenSSH/portable/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	network/ssh
COMPONENT_LICENSE=	BSD, BSD-like
COMPONENT_LICENSE_FILE=	LICENCE

#TEST_TARGET= $(SKIP_TEST)
include $(WS_MAKE_RULES)/common.mk

PATH = $(PATH.gnu)

COMPONENT_PREP_ACTION = ( cd $(@D) ; autoreconf -f -i )

CFLAGS += -DSET_USE_PAM
CFLAGS += -DPAM_ENHANCEMENT
CFLAGS += -DPAM_BUGFIX
CFLAGS += -DDTRACE_SFTP
CFLAGS += -I/usr/include/kerberosv5/
CFLAGS += -DKRB5_BUILD_FIX
CFLAGS += -DDISABLE_BANNER
CFLAGS += -DDEPRECATE_SUNSSH_OPT
CFLAGS += -DOPTION_DEFAULT_VALUE
CFLAGS += -DSANDBOX_SOLARIS
CFLAGS += -DPER_SESSION_XAUTHFILE
CFLAGS += -I$(OPENSSL_INCDIR)

# We need to disable lazyloading of dynamic dependent libraries. During the
# pre-authentication phase, sshd will chroot to /var/empty which doesn't
# contain any files. If we use lazyloading, sshd will fail to find any
# libraries that it needs.
LDFLAGS += -B direct -z nolazyload

CONFIGURE_OPTIONS += --with-ssl-dir=$(OPENSSL_LIBDIR)
CONFIGURE_OPTIONS += --with-ssl-engine
CONFIGURE_OPTIONS += --with-audit=solaris
CONFIGURE_OPTIONS += --with-libedit
CONFIGURE_OPTIONS += --with-kerberos5
CONFIGURE_OPTIONS += --with-pam
CONFIGURE_OPTIONS += --with-sandbox=solaris
CONFIGURE_OPTIONS += --with-solaris-contracts
CONFIGURE_OPTIONS += --with-solaris-privs
CONFIGURE_OPTIONS += --with-privsep-user=daemon
CONFIGURE_OPTIONS += --with-solaris-projects
CONFIGURE_OPTIONS += --with-tcp-wrappers
CONFIGURE_OPTIONS += --with-4in6
CONFIGURE_OPTIONS += --with-xauth=/usr/bin/xauth
CONFIGURE_OPTIONS += --enable-strip=no
CONFIGURE_OPTIONS += --without-rpath
CONFIGURE_OPTIONS += --disable-lastlog
CONFIGURE_OPTIONS += --libexecdir=/usr/lib/ssh
CONFIGURE_OPTIONS += --sbindir=/usr/lib/ssh
CONFIGURE_OPTIONS += --sysconfdir=/etc/ssh
CONFIGURE_OPTIONS += --bindir=/usr/bin

COMPONENT_POST_INSTALL_ACTION += $(INSTALL) -Dm755 $(SOURCE_DIR)/contrib/ssh-copy-id $(PROTOUSRBINDIR)/ssh-copy-id;
COMPONENT_POST_INSTALL_ACTION += $(INSTALL) -Dm644 $(SOURCE_DIR)/contrib/ssh-copy-id.1 $(PROTOUSRSHAREMAN1DIR)/ssh-copy-id.1;

COMPONENT_TEST_TARGETS = tests

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/libedit
REQUIRED_PACKAGES += library/security/openssl-31
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += network/ssh-askpass
REQUIRED_PACKAGES += service/security/kerberos-5
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/gss
REQUIRED_PACKAGES += x11/session/xauth
