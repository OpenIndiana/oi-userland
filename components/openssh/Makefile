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
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		openssh
COMPONENT_VERSION=	6.8p1
HUMAN_VERSION=		$(COMPONENT_VERSION)
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)

# Version for IPS.  The encoding rules are:
#   OpenSSH <x>.<y>p<n>     => IPS <x>.<y>.0.<n>
#   OpenSSH <x>.<y>.<z>p<n> => IPS <x>.<y>.<z>.<n>
IPS_COMPONENT_VERSION=	6.8.0.1

COMPONENT_PROJECT_URL=	http://www.openssh.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:3ff64ce73ee124480b5bf767b9830d7d3c03bbcb6abe716b78f0192c37ce160e
COMPONENT_ARCHIVE_URL=	http://mirror.team-cymru.org/pub/OpenBSD/OpenSSH/portable/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=utility/openssh

TPNO_OPENSSH=		21980
TPNO_GSSKEX=		20377

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

COMPILER=	gcc

CFLAGS += -DSET_USE_PAM
CFLAGS += -DDEPRECATE_SUNSSH_OPT
CFLAGS += -DKRB5_BUILD_FIX
CFLAGS += -DDTRACE_SFTP
CFLAGS += -DDISABLE_BANNER
CFLAGS += -DPAM_ENHANCEMENT
CFLAGS += -DPAM_BUGFIX
CFLAGS += -DOPTION_DEFAULT_VALUE
CFLAGS += -DWITHOUT_ED25519

CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)" 

# We need to disable lazyloading of dynamic dependent libraries. During the
# pre-authentication phase, sshd will chroot to /var/empty which doesn't
# contain any files. If we use lazyloading, sshd will fail to find any
# libraries that it needs.
LDFLAGS += -B direct -z nolazyload

# Just $(BUILD_64) option was not propogating the 64 bit flags to all the
# necessary places. Hence the -m64 option is added to LDFLAGS for
# CONFIGURE_OPTIONS.64.
CONFIGURE_OPTIONS.64 += LDFLAGS="$(LDFLAGS) -m64"

CONFIGURE_OPTIONS += --with-audit=solaris
CONFIGURE_OPTIONS += --with-libedit
CONFIGURE_OPTIONS += --with-kerberos5
CONFIGURE_OPTIONS += --with-pam
CONFIGURE_OPTIONS += --with-sandbox=no
CONFIGURE_OPTIONS += --with-solaris-contracts
CONFIGURE_OPTIONS += --with-solaris-projects
CONFIGURE_OPTIONS += --with-tcp-wrappers
CONFIGURE_OPTIONS += --with-4in6
CONFIGURE_OPTIONS += --enable-strip=no
CONFIGURE_OPTIONS += --without-rpath
CONFIGURE_OPTIONS += --libexecdir=/usr/lib/ssh
CONFIGURE_OPTIONS += --sbindir=/usr/lib/ssh
CONFIGURE_OPTIONS += --sysconfdir=/etc/ssh
CONFIGURE_OPTIONS += --bindir=/usr/bin
CONFIGURE_OPTIONS += --disable-lastlog

# Copy the sftp dtrace provider file and the header file to source directory
COMPONENT_PRE_BUILD_ACTION = \
    ( echo "Copying dtrace sftp files..."; \
      $(LN) -fs $(COMPONENT_DIR)/dtrace_sftp/*.[dh] $(SOURCE_DIR); \
    )

# Copy source files that are not yet part of a patch
COMPONENT_PREP_ACTION += ($(CP) sources/*.c $(@D)/)

# common targets
configure:	$(CONFIGURE_64)

build:		$(BUILD_64)

install:	$(INSTALL_64)

# Because of certain set up requirement, the regress test suite is ported to
# the STC gate.
test:		$(NO_TESTS)

system-test:    $(NO_TESTS)


REQUIRED_PACKAGES += library/libedit
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += service/security/kerberos-5
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/gcc-48-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/security/gss
REQUIRED_PACKAGES += system/linker
