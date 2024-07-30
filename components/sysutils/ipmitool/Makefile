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
# Copyright 2017 Gary Mills
# Copyright 2016 Alexander Pyhalov
# Copyright 2019 Michal Nowak
# Copyright 2022 Niklas Poslovski
#

OPENSSL_VERSION= 3.1
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ipmitool
COMPONENT_VERSION=	1.8.19
COMPONENT_REVISION=	2
COMPONENT_SUMMARY=	IPMI management tool
COMPONENT_SRC=		$(COMPONENT_NAME)-IPMITOOL_1_8_19
COMPONENT_ARCHIVE=	IPMITOOL_1_8_19.tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:48b010e7bcdf93e4e4b6e43c53c7f60aa6873d574cbd45a8d86fa7aaeebaff9c
COMPONENT_ARCHIVE_URL= \
	https://github.com/ipmitool/ipmitool/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://github.com/ipmitool/ipmitool
COMPONENT_CLASSIFICATION=	System/Hardware
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_FMRI=		system/management/ipmitool

include $(WS_MAKE_RULES)/common.mk

CPPFLAGS += -D__EXTENSIONS__

# Provide paths for OpenSSL 3.1
CFLAGS  += -I$(OPENSSL_INCDIR)
LDFLAGS += -L$(OPENSSL_LIBDIR)

COMPONENT_PREP_ACTION = (cd $(@D) && autoreconf -fi)

CONFIGURE_SBINDIR.64 = /usr/lib

CONFIGURE_OPTIONS += --enable-intf-free=yes
CONFIGURE_OPTIONS += --enable-intf-usb=no
CONFIGURE_OPTIONS += --enable-intf-lanplus
CONFIGURE_OPTIONS += --enable-solaris-opt

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

REQUIRED_PACKAGES += driver/ipmi
# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/extended-system-utilities
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/management/freeipmi
