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

COMPONENT_NAME=		libp11
COMPONENT_VERSION=	0.4.2
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=		library/security/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	System/Security
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://github.com/OpenSC/$(COMPONENT_NAME)/wiki
COMPONENT_ARCHIVE_URL=	https://github.com/OpenSC/$(COMPONENT_NAME)/releases/download/$(COMPONENT_NAME)-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	\
	sha256:e2c3614a314b452a9b57e2914252df3ffee59e262dfb75b4fc73a2247f8ddebe
COMPONENT_LICENSE=		LGPLv2.1+
COMPONENT_LICENSE_FILE= COPYING
COMPONENT_DESCRIPTION=	libp11 is a library implementing a thin layer on top of PKCS11 API to make using PKCS11 implementations easier
COMPONENT_SUMMARY=	libp11 is a library to make using PKCS11 implementations easier

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION = \
        (cd $(@D) &&\
        autoreconf -fiv &&\
        $(RM) config.h )

COMPONENT_PRE_CONFIGURE_ACTION = \
        ($(CLONEY) $(SOURCE_DIR) $(@D))

INDIR.32=/usr/bin
BINDIR.64=/usr/bin/$(MACH64)
LIBDIR.32=/usr/lib
LIBDIR.64=/usr/lib/$(MACH64)

# OpenSSL engine directories; default is for files, engines is for symlinks
ENGINESDIR_32 = /lib/openssl/engines
ENGINESDIR_64 = /lib/openssl/engines/$(MACH64)
DEFENGINESDIR_32 = /lib/openssl/default/engines
DEFENGINESDIR_64 = /lib/openssl/default/engines/$(MACH64)

# The project install recipe is somehow borked, that it does some actions
# just assuming the engine directory is present... in the proto area...
# So we must ensure these dirs for both bitnesses are available before install.
COMPONENT_PRE_INSTALL_ACTION = (\
	$(MKDIR) $(PROTO_DIR)$(DEFENGINESDIR_$(BITS)) $(PROTO_DIR)$(ENGINESDIR_$(BITS)) ; \
	)

CONFIGURE_OPTIONS +=	--with-enginesdir=$(DEFENGINESDIR_$(BITS))

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += library/security/openssl
