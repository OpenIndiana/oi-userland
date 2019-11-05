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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
# Copyright 2017 Andreas Grueninger, Grueninger GmbH, (grueni). All rights reserved. 
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= ejabberd
COMPONENT_FMRI= web/server/$(COMPONENT_NAME)
COMPONENT_VERSION= 17.11
COMPONENT_REVISION= 1
COMPONENT_PROJECT_URL=	http://www.ejabberd.im/
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH= sha256:bd16b33a2f1345e5847fd05b70a5fa992181bac756cd6d5d621de9c18cb76801
COMPONENT_ARCHIVE_URL= https://www.process-one.net/downloads/ejabberd/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB= service/ejabberd
COMPONENT_SUMMARY= ejabberd - Jabber/XMPP instant messaging server
COMPONENT_DESCRIPTION= the ejabberd Jabber/XMPP instant messaging server
COMPONENT_CLASSIFICATION= Web Services/Communications
COMPONENT_LICENSE= GPL-2.0
COMPONENT_LICENSE_FILE= $(COMPONENT_NAME).license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CXX      += $(CC_BITS)
CFLAGS   += $(JPEG_CPPFLAGS) $(JPEG_CFLAGS) -I$(USRINCDIR)/gd2
CXXFLAGS += $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS) -I$(USRINCDIR)/gd2
CPPFLAGS += $(JPEG_CPPFLAGS) -I$(USRINCDIR)/gd2
LDFLAGS  += $(JPEG_LDFLAGS) -lnsl -lsocket

CONFIGURE_ENV += "HOME=/tmp"
CONFIGURE_ENV += "CPP=$(CC) -E"
COMPONENT_BUILD_ENV += $(CONFIGURE_ENV)
COMPONENT_INSTALL_ENV += "HOME=/tmp"

COMPONENT_PRE_BUILD_ACTION+= \
  $(CLONEY) $(SOURCE_DIR) $(@D)

CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS +=	--with-erlang=$(USRBINDIR)
CONFIGURE_OPTIONS +=	--localstatedir=/var
CONFIGURE_OPTIONS +=	--enable-odbc
CONFIGURE_OPTIONS +=	--enable-mysql
CONFIGURE_OPTIONS +=	--enable-pgsql
CONFIGURE_OPTIONS +=	--enable-sqlite
CONFIGURE_OPTIONS +=	--enable-pam
CONFIGURE_OPTIONS +=	--enable-riak
CONFIGURE_OPTIONS +=	--enable-redis

CONFIGURE_SBINDIR.64 = $(CONFIGURE_PREFIX)/bin

COMPONENT_BUILD_TARGETS = all

COMPONENT_TEST_ARGS = "CT_BACKENDS=mnesia"
COMPONENT_TEST_TARGETS = test

build:    $(BUILD_64)

install:  $(INSTALL_64)

test:     $(TEST_64)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += image/library/libjpeg8-turbo
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/gd
REQUIRED_PACKAGES += library/libwebp
REQUIRED_PACKAGES += library/libyaml
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
