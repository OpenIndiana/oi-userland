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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
#
OPENSSL_VERSION= 3.1
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		alpine
COMPONENT_VERSION=	2.26
COMPONENT_SUMMARY=	Alternatively Licensed Program for Internet News and Email
COMPONENT_PROJECT_URL=	https://alpineapp.email/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:c0779c2be6c47d30554854a3e14ef5e36539502b331068851329275898a9baba
COMPONENT_ARCHIVE_URL=	https://alpineapp.email/alpine/release/src/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		mail/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_LICENSE=	Apache-2.0
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

CFLAGS += -D_XPG6
LDFLAGS += -lsocket -lnsl -lldap_r

COMPONENT_PRE_CONFIGURE_ACTION += \
        ( $(CLONEY) $(SOURCE_DIR) $(@D) )

COMPONENT_POST_CONFIGURE_ACTION += ( cp $(@D)/include/config.h $(SOURCE_DIR)/include )

CONFIGURE_OPTIONS += LDFLAGS="$(LDFLAGS) -L$(OPENSSL_PREFIX)/lib/$(MACH64)"
CONFIGURE_OPTIONS += CPPFLAGS="-I$(OPENSSL_PREFIX)/include -I/usr/include/openldap"
CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS += --prefix=/usr
CONFIGURE_OPTIONS += --with-passfile=.pine-pass
CONFIGURE_OPTIONS += --with-ssl-dir=$(OPENSSL_PREFIX)
CONFIGURE_OPTIONS += --without-krb5
CONFIGURE_OPTIONS += --without-tcl

# Auto-generated dependencies
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/security/openssl-31
REQUIRED_PACKAGES += system/library
