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

#
# Copyright (c) 2014, 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		postfix
COMPONENT_VERSION=	2.11.3
COMPONENT_PROJECT_URL=	http://www.postfix.org
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:04e5146e6e56261baae9f63c590348a4b12ce22d3d46260e26e97233f40802c3
COMPONENT_BUGDB=	utility/postfix
COMPONENT_ARCHIVE_URL=	http://mirrors-usa.go-parts.com/$(COMPONENT_NAME)/source/official/$(COMPONENT_ARCHIVE)

TPNO=			7492

include ../../make-rules/prep.mk
include ../../make-rules/justmake.mk
include ../../make-rules/ips.mk

# general
CCARGS =	-DDEF_DAEMON_DIR=\\\"/usr/lib/postfix\\\"
CCARGS +=	-DDEF_MANPAGE_DIR=\\\"/usr/share/man\\\"
CCARGS +=	-DDEF_NEWALIAS_PATH=\\\"/usr/sbin/newaliases\\\"
# TLS
CCARGS +=	-DUSE_TLS
AUXLIBS =	-lssl -lcrypto
# Berkeley DB
CCARGS +=	-DHAS_DB
AUXLIBS +=	-ldb-5.3
# SQLite
CCARGS +=	-DHAS_SQLITE
AUXLIBS +=	-lsqlite3
# LDAP
CCARGS +=	-DHAS_LDAP
AUXLIBS +=	-lldap

# pcre-config is run as part of the setup, so we need to find the 64-bit
# version so it will provide a 64-bit runpath, o/w pkglint gives warnings.
PATH =		/usr/bin/$(MACH64):/usr/bin:/usr/gnu/bin

COMPONENT_BUILD_ENV += CC="$(CC) -m64"
COMPONENT_BUILD_ENV += CCARGS="$(CCARGS)"
COMPONENT_BUILD_ENV += PATH="$(PATH)"
COMPONENT_BUILD_ENV += AUXLIBS="$(AUXLIBS)"

COMPONENT_INSTALL_TARGETS = non-interactive-package install_root="$(PROTO_DIR)"

ASLR_MODE = $(ASLR_ENABLE)

build:          $(BUILD_64)

install:        $(INSTALL_64)

test:           $(NO_TESTS)

system-test:    $(NO_TESTS)

PKG_PROTO_DIRS +=	$(COMPONENT_DIR)/files

REQUIRED_PACKAGES += database/berkeleydb-5
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/network
