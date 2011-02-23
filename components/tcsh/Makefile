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

COMPONENT_NAME=		tcsh
COMPONENT_VERSION=	6.17.00
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:9bf67d5ce1b406178e9ba535ecd34553fe0d4d36
COMPONENT_ARCHIVE_URL=	ftp://ftp.astron.com/pub/tcsh/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_PREP_ACTION = \
	(cd $(@D) ; autoconf )

COMPONENT_POST_BUILD_ACTION = \
	(cd $(@D)/nls ; $(MAKE) all)

CFLAGS +=	$(CPP_LARGEFILES)

LOCALEDIR=$(PROTO_DIR)/$(CONFIGURE_LOCALEDIR)

CONFIGURE_OPTIONS  +=		--localedir=$(CONFIGURE_LOCALEDIR)
CONFIGURE_OPTIONS  +=		CFLAGS="$(CFLAGS)"

MAN1FILES= tcsh.1

include ../../make-rules/shared-targets.mk

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32) install-locales $(PROTOMAN1FILES)

# we don't agree on locale names
install-locales:
	$(INSTALL) -D $(BUILD_DIR_32)/nls/et.cat $(LOCALEDIR)/et/LC_MESSAGES/tcsh.cat 
	$(INSTALL) -D $(BUILD_DIR_32)/nls/finnish.cat $(LOCALEDIR)/fi/LC_MESSAGES/tcsh.cat
	$(INSTALL) -D $(BUILD_DIR_32)/nls/french.cat $(LOCALEDIR)/fr/LC_MESSAGES/tcsh.cat
	$(INSTALL) -D $(BUILD_DIR_32)/nls/german.cat $(LOCALEDIR)/de/LC_MESSAGES/tcsh.cat
	$(INSTALL) -D $(BUILD_DIR_32)/nls/greek.cat $(LOCALEDIR)/el/LC_MESSAGES/tcsh.cat
	$(INSTALL) -D $(BUILD_DIR_32)/nls/italian.cat $(LOCALEDIR)/it/LC_MESSAGES/tcsh.cat
	$(INSTALL) -D $(BUILD_DIR_32)/nls/ja.cat $(LOCALEDIR)/ja/LC_MESSAGES/tcsh.cat
	$(INSTALL) -D $(BUILD_DIR_32)/nls/pl.cat $(LOCALEDIR)/pl/LC_MESSAGES/tcsh.cat
	$(INSTALL) -D $(BUILD_DIR_32)/nls/russian.cat $(LOCALEDIR)/ru/LC_MESSAGES/tcsh.cat
	$(INSTALL) -D $(BUILD_DIR_32)/nls/spanish.cat $(LOCALEDIR)/es/LC_MESSAGES/tcsh.cat
	$(INSTALL) -D $(BUILD_DIR_32)/nls/ukrainian.cat $(LOCALEDIR)/uk/LC_MESSAGES/tcsh.cat


BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

# they don't seem quite doable for us
test: 
	@echo "no tests available"

include ../../make-rules/depend.mk
