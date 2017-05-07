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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		postfix
COMPONENT_VERSION=	3.1.1
COMPONENT_SUMMARY=	Postfix is a free and open-source mail transfer agent (MTA) that routes and delivers electronic mail, intended as an alternative to Sendmail MTA.
COMPONENT_PROJECT_URL=	http://www.postfix.org/
COMPONENT_FMRI=		service/network/smtp/postfix
COMPONENT_CLASSIFICATION= System/Services
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	http://cdn.postfix.johnriley.me/mirrors/postfix-release/official/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:3deda4c34631970490b1b5fbb559905f93531bf1c7eb00e38b0d0deb1dba9982
COMPONENT_LICENSE=	IBM PUBLIC LICENSE
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

CCARGS=		-DDEF_DAEMON_DIR=\\\"/usr/lib/postfix\\\"
CCARGS+=	-DDEF_MANPAGE_DIR=\\\"/usr/share/man\\\"
CCARGS+=	-DDEF_NEWALIAS_PATH=\\\"/usr/sbin/newaliases\\\"

CCARGS+=	-DUSE_TLS
CCARGS+=	-DHAS_DB
CCARGS+=	-DHAS_SQLITE

AUXLIBS=	-lssl
AUXLIBS+=	-lcrypto
AUXLIBS+=	-ldb-5.3
AUXLIBS+=	-lsqlite3


COMPONENT_BUILD_ENV+= CC=$(CC)
COMPONENT_BUILD_ENV+= CCARGS="$(CCARGS)"
COMPONENT_BUILD_ENV+= OPT="$(CFLAGS)"
COMPONENT_BUILD_ENV+= DEBUG="$(CFLAGS)"
COMPONENT_BUILD_ENV+= AUXLIBS="$(AUXLIBS)"

COMPONENT_INSTALL_TARGETS = non-interactive-package install_root="$(PROTO_DIR)"

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

REQUIRED_PACKAGES += developer/icu
REQUIRED_PACKAGES += database/berkeleydb-5
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += system/library
