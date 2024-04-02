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
# Copyright 2021 Andreas Grueninger, Grueninger GmbH, (grueni). All rights reserved.
# Copyright 2022 Niklas Poslovski
# Copyright 2024 Goetz Fischer, R-A-C. All rights reserved.
#

BUILD_BITS= 64
USE_PARALLEL_BUILD= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= ejabberd
COMPONENT_VERSION= 24.2
HUMAN_VERSION= 24.02
COMPONENT_SUMMARY= ejabberd - Jabber/XMPP instant messaging server
COMPONENT_PROJECT_URL= https://www.ejabberd.im/
COMPONENT_SRC= $(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:b6d48d3bf2bef368e9321e35436381c86d78444b9042649c6c4aab0089395c07
COMPONENT_ARCHIVE_URL= https://static.process-one.net/ejabberd/downloads/$(HUMAN_VERSION)/ejabberd-$(HUMAN_VERSION).tar.gz
COMPONENT_FMRI= web/server/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= Web Services/Communications
COMPONENT_LICENSE= GPLv2
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CXX      += $(CC_BITS)
CFLAGS   += -I$(USRINCDIR)/gd2
CXXFLAGS += -I$(USRINCDIR)/gd2
CPPFLAGS += -I$(OPENSSL_INCDIR) -I$(USRINCDIR)/gd2
LDFLAGS  += -L$(OPENSSL_LIBDIR) -lnsl -lsocket

# testing these with gcc 13. can safely be omitted in doubt.
CFLAGS   += -finline-functions -funroll-loops
CXXFLAGS += -finline-functions -funroll-loops -fno-exceptions -fno-rtti

CONFIGURE_ENV += "HOME=/tmp"
CONFIGURE_ENV += "CPP=$(CC) -E"
COMPONENT_BUILD_ENV += $(CONFIGURE_ENV)
COMPONENT_INSTALL_ENV += "HOME=/tmp"

COMPONENT_PRE_CONFIGURE_ACTION+= \
  cd $(SOURCE_DIR); ./autogen.sh

COMPONENT_PRE_BUILD_ACTION+= \
  $(CLONEY) $(SOURCE_DIR) $(@D)

CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --with-erlang=$(USRBINDIR)
CONFIGURE_OPTIONS += --localstatedir=$(VARDIR)
CONFIGURE_OPTIONS += --enable-odbc
CONFIGURE_OPTIONS += --enable-mysql
CONFIGURE_OPTIONS += --enable-pgsql
CONFIGURE_OPTIONS += --enable-sqlite
CONFIGURE_OPTIONS += --enable-pam
CONFIGURE_OPTIONS += --enable-redis
CONFIGURE_OPTIONS += --enable-new-sql-schema
CONFIGURE_OPTIONS += --enable-sip
CONFIGURE_OPTIONS += --enable-tools

CONFIGURE_SBINDIR.64 = $(CONFIGURE_PREFIX)/bin

COMPONENT_BUILD_TARGETS = all

# Manually added build dependencies
REQUIRED_PACKAGES += runtime/erlang

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/libyaml
REQUIRED_PACKAGES += library/security/openssl-31
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
