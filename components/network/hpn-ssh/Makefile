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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		hpn-ssh
COMPONENT_VERSION=	18.4.2
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	High performance SSH/SCP
COMPONENT_SRC=		$(COMPONENT_NAME)-hpn-$(HUMAN_VERSION)
COMPONENT_PROJECT_URL=	https://www.psc.edu/hpn-ssh-home/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:ff5653d26cd3846f5d366e6826589c66dca7607b3ce7ab6af83258510da521f8
COMPONENT_ARCHIVE_URL=	https://github.com/rapier1/hpn-ssh/archive/refs/tags/hpn-$(HUMAN_VERSION).tar.gz
COMPONENT_FMRI=		network/hpn-ssh
COMPONENT_LICENSE=	BSD, BSD-like
COMPONENT_LICENSE_FILE=	LICENCE

COMPONENT_SUMMARY.$(COMPONENT_NAME)=		$(COMPONENT_SUMMARY) - client and utilities

COMPONENT_FMRI.$(COMPONENT_NAME)-service=	service/$(COMPONENT_FMRI)
COMPONENT_SUMMARY.$(COMPONENT_NAME)-service=	$(COMPONENT_SUMMARY) - servers and services

TEST_TARGET= $(SKIP_TEST)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = ( cd $(@D) ; autoreconf -f -i )

# Enable various fixes and enhancements implemented by patches
CFLAGS += -DSET_USE_PAM
CFLAGS += -DPAM_ENHANCEMENT
CFLAGS += -DPAM_BUGFIX
CFLAGS += -DDTRACE_SFTP
CFLAGS += -DDISABLE_BANNER
CFLAGS += -DDEPRECATE_SUNSSH_OPT
CFLAGS += -DPER_SESSION_XAUTHFILE

# configure is unable to find OpenSSL headers without this workaround
CFLAGS += -I$(OPENSSL_INCDIR)

# We need to disable lazyloading of dynamic dependent libraries. During the
# pre-authentication phase, hpnsshd will chroot to /var/empty which doesn't
# contain any files. If we use lazyloading, hpnsshd will fail to find any
# libraries that it needs.
LDFLAGS += -B direct -z nolazyload

# configure is unable to find OpenSSL libraries by default so we need to pass
# OPENSSL_LIBDIR to --with-ssl-dir as a workaround
CONFIGURE_OPTIONS += --with-ssl-dir=$(OPENSSL_LIBDIR)
CONFIGURE_OPTIONS += --with-ssl-engine
CONFIGURE_OPTIONS += --with-audit=solaris
CONFIGURE_OPTIONS += --with-libedit
CONFIGURE_OPTIONS += --with-kerberos5
CONFIGURE_OPTIONS += --with-pam
CONFIGURE_OPTIONS += --with-sandbox=solaris
CONFIGURE_OPTIONS += --with-solaris-contracts
CONFIGURE_OPTIONS += --with-solaris-privs
CONFIGURE_OPTIONS += --with-solaris-projects
CONFIGURE_OPTIONS += --with-tcp-wrappers
CONFIGURE_OPTIONS += --with-4in6
CONFIGURE_OPTIONS += --with-xauth=/usr/bin/xauth
CONFIGURE_OPTIONS += --enable-strip=no
CONFIGURE_OPTIONS += --without-rpath
CONFIGURE_OPTIONS += --disable-lastlog
CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)

# Install hpnssh-copy-id and its man page
COMPONENT_POST_INSTALL_ACTION += $(INSTALL) -Dm755 $(SOURCE_DIR)/contrib/hpnssh-copy-id $(PROTOUSRBINDIR)/hpnssh-copy-id ;
COMPONENT_POST_INSTALL_ACTION += $(INSTALL) -Dm644 $(SOURCE_DIR)/contrib/hpnssh-copy-id.1 $(PROTOUSRSHAREMAN1DIR)/hpnssh-copy-id.1 ;

# Install the service related files
COMPONENT_POST_INSTALL_ACTION += $(INSTALL) -Dm0444 $(COMPONENT_DIR)/files/hpnssh.xml $(PROTO_DIR)/lib/svc/manifest/network/hpnssh.xml ;
COMPONENT_POST_INSTALL_ACTION += $(INSTALL) -Dm0555 $(COMPONENT_DIR)/files/hpnsshd $(PROTO_DIR)/lib/svc/method/hpnsshd ;

# Install configuration snippets
COMPONENT_POST_INSTALL_ACTION += $(INSTALL) -d $(PROTO_DIR)/etc/hpnssh/ssh_config.d ;
COMPONENT_POST_INSTALL_ACTION += $(INSTALL) $(COMPONENT_DIR)/files/ssh_config.d/* $(PROTO_DIR)/etc/hpnssh/ssh_config.d ;
COMPONENT_POST_INSTALL_ACTION += $(INSTALL) -d $(PROTO_DIR)/etc/hpnssh/sshd_config.d ;
COMPONENT_POST_INSTALL_ACTION += $(INSTALL) $(COMPONENT_DIR)/files/sshd_config.d/* $(PROTO_DIR)/etc/hpnssh/sshd_config.d ;

COMPONENT_TEST_TARGETS = tests

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/libedit
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += service/security/kerberos-5
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/gss
