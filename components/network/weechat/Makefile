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

SINGLE_PYTHON_VERSION= yes
SINGLE_PERL_VERSION= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		weechat
COMPONENT_VERSION=	3.8
COMPONENT_SUMMARY=	WeeChat - portable, fast, light and extensible IRC client
COMPONENT_DESCRIPTION=	WeeChat (Wee Enhanced Environment for Chat) is a portable, fast, light and \
extensible chat client. Everything can be done with a keyboard. \
It is customizable and extensible with scripts.
COMPONENT_PROJECT_URL=	https://weechat.org
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:f7cb65c200f8c090c56f2cf98c0b184051e516e5f7099a4308cacf86f174bf28
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/files/src/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).asc
COMPONENT_FMRI=		network/chat/weechat
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_LICENSE=	GPLv3

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_PREP_ACTION= ( cd $(@D) && ./autogen.sh )

CONFIGURE_OPTIONS += --enable-doc
CONFIGURE_OPTIONS += --disable-ruby
CONFIGURE_OPTIONS += --enable-man
CONFIGURE_OPTIONS += --enable-tests
CONFIGURE_ENV += CA_FILE="/etc/certs/ca-certificates.crt"
CONFIGURE_ENV += PERL=$(PERL)

COMPONENT_TEST_CMD=    ctest -V
COMPONENT_TEST_TARGETS=

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += runtime/perl
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/guile
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/lua-53
REQUIRED_PACKAGES += runtime/tcl-8
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/libgcrypt
REQUIRED_PACKAGES += text/aspell
REQUIRED_PACKAGES += web/curl
