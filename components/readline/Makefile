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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		readline
COMPONENT_VERSION=	5.2
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:18f3412c73068509d5f491b7b4535aeaf9522834
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/readline/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

# readline likes to use ld directly and this is the easiest
# way to get it to add -lc
LDFLAGS += -lc
CONFIGURE_OPTIONS  +=		--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  +=		--enable-shared
CONFIGURE_OPTIONS  +=		--disable-static
CONFIGURE_OPTIONS  +=		CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS  +=		LDFLAGS="$(LDFLAGS)"


include ../../make-rules/shared-targets.mk

# common targets
build:		$(BUILD_32) $(BUILD_64)

install:	$(INSTALL_32) $(INSTALL_64)
	$(MKDIR) $(PROTO_DIR)/usr/demo/readline
	$(INSTALL) -D \
	    $(SOURCE_DIR)/examples/Inputrc $(PROTO_DIR)/usr/demo/readline
	sed -f oracleman-stability $(COMPONENT_SRC)/doc/history.3 \
	    > $(PROTOUSRSHAREMAN3DIR)/history.3
	sed -f oracleman-stability $(COMPONENT_SRC)/doc/readline.3 \
	    > $(PROTOUSRSHAREMAN3DIR)/readline.3


BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

test: build
	@cd $(BUILD_DIR_32); $(MAKE) check

include ../../make-rules/depend.mk
