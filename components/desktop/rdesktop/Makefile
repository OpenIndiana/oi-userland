#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2018 Alexander Pyhalov
# Copyright 2019 Michal Nowak
#

PREFERRED_BITS=		64

include ../../../make-rules/shared-macros.mk

# Really, this is not the stated version as releases are based on the 1.8.x
# branch but require libgssglue, which we don't want to package as it's
# obsolete in the master branch anyway. For Kerberos we use native GSS-API.
# So, version 1.8.99 is to be read as development version before 1.9.0 is out.
COMPONENT_NAME=		rdesktop
COMPONENT_VERSION=	1.8.99
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	https://www.rdesktop.org/
COMPONENT_SUMMARY=	RDP, Microsoft Terminal Services client
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_COMMIT)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_HASH=	\
	sha256:318ef24770a6b9b4083cc75473d1722e6421804ff93e92031a80511e40b076fb
COMPONENT_COMMIT=	6028c999ba7852d560b7831853502e675c65709a
COMPONENT_ARCHIVE_URL=	https://github.com/rdesktop/rdesktop/archive/$(COMPONENT_COMMIT).zip
COMPONENT_FMRI=		desktop/remote-desktop/rdesktop
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	GPLv3

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Force use of gnutls-3 pkgconfig during 2.x->3.x transition
GNUTLS_PKG_CONFIG_PATH_32 = /usr/lib/pkgconfig/gnutls-3
GNUTLS_PKG_CONFIG_PATH_64 = /usr/lib/$(MACH64)/pkgconfig/gnutls-3
PKG_CONFIG_PATH = $(GNUTLS_PKG_CONFIG_PATH_$(BITS)):$(PKG_CONFIG_PATH.$(BITS))

LD_OPTIONS.32 += -L/usr/lib/gnutls-3 -R/usr/lib/gnutls-3
LD_OPTIONS.64 += -L/usr/lib/$(MACH64)/gnutls-3 -R/usr/lib/$(MACH64)/gnutls-3
LD_OPTIONS += $(LD_OPTIONS.$(BITS))

CFLAGS += -I/usr/include/gmp

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION = (cd $(@D) && autoreconf -if)

# Missing files in build dir without this.
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--enable-credssp
CONFIGURE_OPTIONS+=	--disable-smartcard

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/libsamplerate
REQUIRED_PACKAGES += library/libtasn1
REQUIRED_PACKAGES += library/nettle
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/gss
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcursor
REQUIRED_PACKAGES += x11/library/libxrandr
