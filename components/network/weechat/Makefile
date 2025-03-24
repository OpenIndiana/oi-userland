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

BUILD_STYLE= cmake
SINGLE_PYTHON_VERSION= yes
SINGLE_PERL_VERSION= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		weechat
COMPONENT_VERSION=	4.6.0
COMPONENT_SUMMARY=	WeeChat - portable, fast, light and extensible IRC client
COMPONENT_DESCRIPTION=	WeeChat (Wee Enhanced Environment for Chat) is a portable, fast, light and \
extensible chat client. Everything can be done with a keyboard. \
It is customizable and extensible with scripts.
COMPONENT_PROJECT_URL=	https://weechat.org
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:2681fc662996fead9d66a26d81740088e4284cf4e6dfe6b834f3b98fc703597f
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/files/src/$(COMPONENT_ARCHIVE)
# The signature is invalid
#COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).asc
COMPONENT_FMRI=		network/chat/weechat
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

CFLAGS += $(XPG6MODE)

LD_OPTIONS += -lresolv -lsocket -lnsl

# default value of option weechat.network.gnutls_ca_file (default is "/etc/ssl/certs/ca-certificates.crt")
# Alas since version 3.2 this is not supported anymore.
CMAKE_OPTIONS += -DCA_FILE="/etc/certs/ca-certificates.crt"
# We don't have PHP libraries (PHP with --enable-embed)
CMAKE_OPTIONS += -DENABLE_PHP=OFF
# We don't have libcjson
CMAKE_OPTIONS += -DENABLE_CJSON=OFF

COMPONENT_POST_INSTALL_ACTION= \
	for file in `find $(PROTO_DIR)/usr/lib/weechat/plugins/ -name "ruby.so"`; do \
		$(ELFEDIT) -e 'dyn:value -s  RUNPATH "$(GCC_LIBDIR):$(RUBY_LIBDIR)"' $$file ; \
		$(ELFEDIT) -e 'dyn:value -s  RPATH   "$(GCC_LIBDIR):$(RUBY_LIBDIR)"' $$file ; \
	done ;

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += runtime/perl
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/guile
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += runtime/ruby-32
REQUIRED_PACKAGES += runtime/tcl-8
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/libgcrypt
REQUIRED_PACKAGES += text/aspell
REQUIRED_PACKAGES += web/curl
