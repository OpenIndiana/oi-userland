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
# Copyright (c) 2014, 2016, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS= 64
COMPILER =	gcc

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		postfix
COMPONENT_VERSION=	3.1.0
COMPONENT_PROJECT_URL=	http://www.postfix.org
COMPONENT_ARCHIVE_HASH=	\
    sha256:88ac3e92755629077d9363319b1fa0db406efb10c2f22cdbb941bd8ab36fd733
COMPONENT_ARCHIVE_URL=	http://mirrors-usa.go-parts.com/$(COMPONENT_NAME)/source/official/$(COMPONENT_ARCHIVE)

TPNO=			27578

BUILD_STYLE= justmake
TEST_TARGET= $(NO_TESTS)
include ../../make-rules/common.mk

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
CCARGS +=	-DHAS_LDAP -I/usr/include/openldap
AUXLIBS +=	-lldap_r-2.4 -llber-2.4

# Enable adiheap and adistack security extensions
ADIHEAP_MODE =	$(ADIHEAP_ENABLE)
ADISTACK_MODE =	$(ADISTACK_ENABLE)

# pcre-config is run as part of the setup, so we need to find the 64-bit
# version so it will provide a 64-bit runpath, o/w pkglint gives warnings.
PATH =		$(USRBINDIR64):$(USRBINDIR):$(GNUBIN)

COMPONENT_BUILD_ENV += CCARGS="$(CCARGS)"
COMPONENT_BUILD_ENV += OPT="$(CFLAGS)"
COMPONENT_BUILD_ENV += DEBUG="$(CFLAGS)"
COMPONENT_BUILD_ENV += PATH="$(PATH)"
COMPONENT_BUILD_ENV += AUXLIBS="$(AUXLIBS)"

COMPONENT_INSTALL_TARGETS = non-interactive-package install_root="$(PROTO_DIR)"

REQUIRED_PACKAGES += database/berkeleydb-5
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/network
REQUIRED_PACKAGES += system/network/ldap/openldap
