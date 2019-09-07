#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2019 Michal Nowak
#

BUILD_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		wget2
COMPONENT_VERSION=	1.99.2
COMPONENT_SUMMARY=	GNU Wget2 - a file and recursive website downloader
COMPONENT_PROJECT_URL=	https://gitlab.com/gnuwget/wget2
COMPONENT_FMRI=		web/wget2
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.lz
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/gnu/wget/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:ec5dd1c5a89ec749fd772c56ac3ea23bd8570d2f6a60c1f41d5ec6b692043c4c
COMPONENT_LICENSE=	GPLv3, LGPLv3

include $(WS_MAKE_RULES)/common.mk

# Force use of gnutls-3 pkgconfig during 2.x->3.x transition
GNUTLS_PKG_CONFIG_PATH_32 = /usr/lib/pkgconfig/gnutls-3
GNUTLS_PKG_CONFIG_PATH_64 = /usr/lib/$(MACH64)/pkgconfig/gnutls-3
PKG_CONFIG_PATH = $(GNUTLS_PKG_CONFIG_PATH_$(BITS)):$(PKG_CONFIG_PATH.$(BITS))

LD_OPTIONS.32 += -L/usr/lib/gnutls-3 -R/usr/lib/gnutls-3
LD_OPTIONS.64 += -L/usr/lib/$(MACH64)/gnutls-3 -R/usr/lib/$(MACH64)/gnutls-3
LD_OPTIONS += $(LD_OPTIONS.$(BITS))

# Inherited from the wget component:
#   Enforce openssl (--with-ssl=openssl) instead of default gnutls
#   (--with-ssl) as wget doesn't work for secure connections with gnutls. 
# But: Wget2 requires OpenSSL 1.1 which we don't provide
#CONFIGURE_OPTIONS +=	--with-ssl=openssl
CONFIGURE_OPTIONS +=	--disable-static

unexport SHELLOPTS

COMPONENT_TEST_ENV = $(COMPONENT_BUILD_ENV)

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += library/brotli
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/libidn2
REQUIRED_PACKAGES += library/nghttp2
REQUIRED_PACKAGES += library/pcre2
REQUIRED_PACKAGES += library/security/gpgme
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
