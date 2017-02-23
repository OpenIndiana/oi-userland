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
# Copyright (c) 2013, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
COMPILER= gcc
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		openssh
COMPONENT_VERSION=	7.4p1
HUMAN_VERSION=		$(COMPONENT_VERSION)
COMPONENT_ANITYA_ID=	2565

# Version for IPS.  The encoding rules are:
#   OpenSSH <x>.<y>p<n>     => IPS <x>.<y>.0.<n>
#   OpenSSH <x>.<y>.<z>p<n> => IPS <x>.<y>.<z>.<n>
IPS_COMPONENT_VERSION=	7.4.0.1

COMPONENT_PROJECT_URL=	http://www.openssh.org/
COMPONENT_ARCHIVE_HASH=	sha256:1b1fc4a14e2024293181924ed24872e6f2e06293f3e8926a376b8aec481f19d1
COMPONENT_ARCHIVE_URL=	http://mirrors.sonic.net/pub/OpenBSD/OpenSSH/portable/$(COMPONENT_ARCHIVE)

TPNO_OPENSSH=		33237
TPNO_GSSKEX=		20377

# Because of set up requirements, test suite is in stc gate.
TEST_TARGET= $(SKIP_TEST)

# 11.3 has conflicts with ON's SunSSH package, which had not yet added
# mediated links, thus cannot be updated to.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_64=
INSTALL_64=
PUBLISH_STAMP=
endif

include $(WS_MAKE_RULES)/common.mk

CFLAGS += -DSET_USE_PAM
CFLAGS += -DDEPRECATE_SUNSSH_OPT
CFLAGS += -DKRB5_BUILD_FIX
CFLAGS += -DDTRACE_SFTP
CFLAGS += -DDISABLE_BANNER
CFLAGS += -DPAM_ENHANCEMENT
CFLAGS += -DPAM_BUGFIX
CFLAGS += -DOPTION_DEFAULT_VALUE
CFLAGS += -DPER_SESSION_XAUTHFILE
CFLAGS += -DOPENSSL_NO_CAST
CFLAGS += -DENABLE_OPENSSL_FIPS
CFLAGS += -DOPENSSL_NO_RC4
CFLAGS += -DWITHOUT_HMAC_MD5
CFLAGS += -DDEFAULT_PKCS11_WHITELIST='\"/usr/lib/sparcv9/*,/lib/sparcv9/*,/usr/lib/amd64/*,/lib/amd64/*\"'


# We need to disable lazyloading of dynamic dependent libraries. During the
# pre-authentication phase, sshd will chroot to /var/empty which doesn't
# contain any files. If we use lazyloading, sshd will fail to find any
# libraries that it needs.
LDFLAGS += $(LD_B_DIRECT) -z nolazyload

# Enable adiheap and adistack security extensions
ADIHEAP_MODE =	$(ADIHEAP_ENABLE)
ADISTACK_MODE =	$(ADISTACK_ENABLE)

# Build PIE
CC_PIC_MODE =	$(CC_PIC_ENABLE)
LD_Z_PIE_MODE =	$(LD_Z_PIE_ENABLE)

# Fix 64-bit linking via compiler.
LDFLAGS += $(CC_BITS)

CONFIGURE_OPTIONS += --with-audit=solaris
CONFIGURE_OPTIONS += --with-libedit
CONFIGURE_OPTIONS += --with-kerberos5
CONFIGURE_OPTIONS += --with-pam
CONFIGURE_OPTIONS += --with-sandbox=no
CONFIGURE_OPTIONS += --with-solaris-contracts
CONFIGURE_OPTIONS += --with-4in6
CONFIGURE_OPTIONS += --with-xauth=$(USRBINDIR)/xauth
CONFIGURE_OPTIONS += --disable-strip
CONFIGURE_OPTIONS += --without-rpath
CONFIGURE_OPTIONS += --libexecdir=$(USRLIBDIR)/ssh
CONFIGURE_OPTIONS += --sbindir=$(USRLIBDIR)/ssh
CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)/ssh
CONFIGURE_OPTIONS += --disable-lastlog

# Copy the sftp dtrace provider file and the header file to source directory
COMPONENT_PRE_BUILD_ACTION = \
    ( echo "Copying dtrace sftp files..."; \
      $(LN) -fs $(COMPONENT_DIR)/dtrace_sftp/*.[dh] $(SOURCE_DIR); \
    )

# Copy Solaris specific source files and generate configuration script
COMPONENT_PREP_ACTION += \
    ( $(CP) sources/moduli sources/*.c $(@D)/; \
      cd $(@D); autoconf; \
    )

REQUIRED_PACKAGES += library/libedit
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += security/kerberos-5
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/network
REQUIRED_PACKAGES += text/groff/groff-core
