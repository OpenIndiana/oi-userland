#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016 Jim Klimov
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		vpnc
COMPONENT_VERSION=	0.5.3
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=		network/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://www.unix-ag.uni-kl.de/~massar/vpnc/
COMPONENT_ARCHIVE_URL=	https://www.unix-ag.uni-kl.de/~massar/vpnc/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	\
	sha256:46cea3bd02f207c62c7c6f2f22133382602baeda1dc320747809e94881414884
COMPONENT_LICENSE=		GPLv2,BSD-2clause
COMPONENT_LICENSE_FILE= COPYING
COMPONENT_SUMMARY=	An IPSec-like VPN client compatible with Cisco EasyVPN
COMPONENT_DESCRIPTION=	An IPSec-like (over TUN/TAP) VPN client compatible with Cisco 3000 VPN Concentrators and EasyVPN

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION = \
        (cd $(@D) &&\
        $(MV) vpnc.8.template vpnc.1m.template)

COMPONENT_PRE_CONFIGURE_ACTION = \
        ($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_INSTALL_ARGS += PREFIX=$(USRDIR)
COMPONENT_INSTALL_ARGS += BINDIR=$(USRBINDIR.$(BITS))
COMPONENT_INSTALL_ARGS += SBINDIR=$(USRSBINDIR.$(BITS))
COMPONENT_BUILD_ARGS += PREFIX=$(USRDIR)
COMPONENT_BUILD_ARGS += BINDIR=$(USRBINDIR.$(BITS))
COMPONENT_BUILD_ARGS += SBINDIR=$(USRSBINDIR.$(BITS))

CFLAGS += -DHAVE_GETLINE=1
CFLAGS += -DHAVE_INET_NTOP=1

# This also covers linking, even though "-m32"/"-m64" harmlessly
# appears twice in command-line for compilation
COMPONENT_BUILD_ARGS += CC="$(CC) -m$(BITS)"
COMPONENT_BUILD_ARGS += CFLAGS="$(CFLAGS)"

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += network/vpnc-scripts
REQUIRED_PACKAGES += system/library/security/libgcrypt
REQUIRED_PACKAGES += library/security/libgpg-error
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += system/library/security/gss
REQUIRED_PACKAGES += driver/network/header-tun
REQUIRED_PACKAGES += driver/network/header-tap
