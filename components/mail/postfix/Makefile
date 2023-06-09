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
# Copyright 2016 Adam Stevko
# Copyright 2017 Till Wegmueller
# Copyright 2018 Michal Nowak
#

BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		postfix
COMPONENT_VERSION=	3.3.2
COMPONENT_REVISION=	4
COMPONENT_SUMMARY=	Postfix is a free and open-source mail transfer agent (MTA) that routes and delivers electronic mail, intended as an alternative to Sendmail MTA.
COMPONENT_PROJECT_URL=	http://www.postfix.org/
COMPONENT_FMRI=		service/network/smtp/postfix
COMPONENT_CLASSIFICATION= System/Services
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	http://cdn.postfix.johnriley.me/mirrors/postfix-release/official/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:3c93f31eee49a58e592c31e62a058701cadde11e8e066ea441da19fddad7b35b
COMPONENT_LICENSE=	IBM PUBLIC LICENSE, Eclipse Public License 2.0
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CCARGS=		-DDEF_DAEMON_DIR=\\\"/usr/lib/postfix\\\"
CCARGS+=	-DDEF_MANPAGE_DIR=\\\"/usr/share/man\\\"
CCARGS+=	-DDEF_NEWALIAS_PATH=\\\"/usr/sbin/newaliases\\\"

CCARGS+=	-DUSE_TLS
CCARGS+=	-DHAS_DB
CCARGS+=	-DHAS_SQLITE
CCARGS+=	-DUSE_SASL_AUTH -DUSE_CYRUS_SASL -I/usr/include/sasl

AUXLIBS=	-lssl
AUXLIBS+=	-lcrypto
AUXLIBS+=	-ldb-5.3
AUXLIBS+=	-lsqlite3
AUXLIBS+=	-lsasl


COMPONENT_BUILD_ENV+= CC=$(CC)
COMPONENT_BUILD_ENV+= CCARGS="$(CCARGS)"
COMPONENT_BUILD_ENV+= OPT="$(CFLAGS) -fcommon"
COMPONENT_BUILD_ENV+= DEBUG="$(CFLAGS) -fcommon"
COMPONENT_BUILD_ENV+= AUXLIBS="$(AUXLIBS)"

COMPONENT_INSTALL_TARGETS = non-interactive-package install_root="$(PROTO_DIR)"

PKG_HARDLINKS += usr/lib/postfix/qmgr
PKG_HARDLINKS += usr/lib/postfix/lmtp

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += database/berkeleydb-5
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/libsasl
