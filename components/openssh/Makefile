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
# Copyright (c) 2013, 2014, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		openssh
COMPONENT_VERSION=	6.5p1
HUMAN_VERSION=		$(COMPONENT_VERSION)
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)

# Version for IPS.  The encoding rules are:
#   OpenSSH <x>.<y>p<n>     => IPS <x>.<y>.0.<n>
#   OpenSSH <x>.<y>.<z>p<n> => IPS <x>.<y>.<z>.<n>
IPS_COMPONENT_VERSION=	6.5.0.1

COMPONENT_PROJECT_URL=	http://www.openssh.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:a1195ed55db945252d5a1730d4a2a2a5c1c9a6aa01ef2e5af750a962623d9027
COMPONENT_ARCHIVE_URL=	http://mirror.team-cymru.org/pub/OpenBSD/OpenSSH/portable/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=utility/openssh

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS) -DSET_USE_PAM -DDEPRECATE_SUNSSH_OPT -DLASTLOG_FIX -DKRB5_BUILD_FIX -DAUE_openssh=6172 -DDTRACE_SFTP -DDISABLE_BANNER"

# We need to disable lazyloading of dynamic dependent libraries. During the
# pre-authentication phase, sshd will chroot to /var/empty which doesn't
# contain any files. If we use lazyloading, sshd will fail to find any
# libraries that it needs.
CONFIGURE_OPTIONS += LDFLAGS="$(LDFLAGS) -B direct -z nolazyload"

# Build with BSM audit. Do not check if getaudit and getaudit_addr are in
# libbsm, because they are no longer in libbsm and not needed any way.
CONFIGURE_OPTIONS += --with-audit=bsm
CONFIGURE_OPTIONS += "ac_cv_lib_bsm_getaudit=yes"       
CONFIGURE_OPTIONS += "ac_cv_func_getaudit=yes"
CONFIGURE_OPTIONS += "ac_cv_func_getaudit_addr=yes"
     
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

# Copy the sftp dtrace provider file and the header file to source directory
COMPONENT_PRE_BUILD_ACTION = \
    ( echo "Copying dtrace sftp files..."; \
      $(LN) -fs $(COMPONENT_DIR)/dtrace_sftp/*.[dh] $(SOURCE_DIR); \
    )

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

# Because of certain set up requirement, the regress test suite is ported to
# the STC gate.
test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
