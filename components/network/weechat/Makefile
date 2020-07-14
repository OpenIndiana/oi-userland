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
# Copyright (c) 2020 Evgeny Litvinenko
#

BUILD_BITS=32

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		weechat
COMPONENT_VERSION=	2.8
COMPONENT_PROJECT_URL=	https://weechat.org/
COMPONENT_SUMMARY=	WeeChat - portable, fast, light and extensible IRC client
COMPONENT_DESCRIPTION=	WeeChat (Wee Enhanced Environment for Chat) is a portable, fast, light and \
extensible chat client. Everything can be done with a keyboard. \
It is customizable and extensible with scripts.
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha512:3bebb42118fca6b601f1de8f4d52378619a10e5c490f5b46f86d27a9680f00a56d48a1ade729e78d965cae589e6c80647c22414393000c7d3cfcc94a1e41c4df
COMPONENT_ARCHIVE_URL=	https://weechat.org/files/src/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).asc
COMPONENT_FMRI=		network/chat/weechat
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license
COMPONENT_CLASSIFICATION=	Applications/Internet

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_PREP_ACTION = ( cd $(@D) && ./autogen.sh )

CONFIGURE_OPTIONS += --enable-doc
CONFIGURE_OPTIONS += --enable-man
CONFIGURE_OPTIONS += --enable-tests
CONFIGURE_ENV += CA_FILE="/etc/certs/ca-certificates.crt"

COMPONENT_TEST_CMD =    ctest -V
COMPONENT_TEST_TARGETS =

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/guile
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/pcre2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/lua-53
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/ruby-23
REQUIRED_PACKAGES += runtime/tcl-8
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/libgcrypt
REQUIRED_PACKAGES += web/curl
