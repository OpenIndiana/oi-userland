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
# Copyright (c) 2022, Andreas Wacknitz
#

#USE_OPENSSL11= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         wget2
COMPONENT_VERSION=      2.0.1
COMPONENT_SUMMARY=		GNU Wget2 is the successor of GNU Wget, a file and recursive website downloader
COMPONENT_PROJECT_URL=  https://www.gnu.org/software/wget/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.lz
COMPONENT_ARCHIVE_HASH= sha256:2c942fba6a547997aa7aae0053b7c46a5203e311e4e62d305d575b6d2f06411f
COMPONENT_ARCHIVE_URL=  https://ftp.gnu.org/gnu/wget/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			web/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_LICENSE=		GPLv3+, LGPLv3+

include $(WS_MAKE_RULES)/common.mk

# Our idn2 include file is in a separate folder:
CPPFLAGS +=	-I/usr/include/idn2

CONFIGURE_OPTIONS +=	--sysconfdir=/etc
# Our gnutls is more up-to-date than our openssl:
#CONFIGURE_OPTIONS +=	--with-ssl=openssl
CONFIGURE_OPTIONS +=	--with-bzip2
CONFIGURE_OPTIONS +=	--with-microhttpd
CONFIGURE_OPTIONS +=	--with-libnghttp2
CONFIGURE_OPTIONS +=	--with-libpcre2
CONFIGURE_OPTIONS +=	--with-lzip
CONFIGURE_OPTIONS +=	--with-lzma
CONFIGURE_OPTIONS +=	--with-zlib
CONFIGURE_OPTIONS +=	--with-zstd
CONFIGURE_OPTIONS +=	--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS +=	--disable-static

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

unexport SHELLOPTS

COMPONENT_TEST_TRANSFORMS += '-ne "/^TOTAL/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^PASS/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^XPASS/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^FAIL/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^XFAIL/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^SKIP/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^ERROR/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^===/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^\# /p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^Testsuite summary/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^See/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^Please/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += library/brotli
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/libidn2
REQUIRED_PACKAGES += library/lzlib
REQUIRED_PACKAGES += library/nghttp2
REQUIRED_PACKAGES += library/pcre2
REQUIRED_PACKAGES += library/security/gpgme
REQUIRED_PACKAGES += library/security/libassuan
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
