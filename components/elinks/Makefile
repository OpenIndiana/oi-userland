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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		elinks
COMPONENT_VERSION=	0.11.7
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	sha1:d13edc1477d0ab32cafe7d3c1f3a23ae1c0a5c54
COMPONENT_ARCHIVE_URL=	http://elinks.or.cz/download/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_OPTIONS  +=		--enable-bittorrent
CONFIGURE_OPTIONS  +=		--enable-html-highlight
CONFIGURE_OPTIONS  +=		--enable-256-colors
CONFIGURE_OPTIONS  +=		CFLAGS="$(CFLAGS)"

# common targets
build:		$(BUILD_32)

DOCFILES= bittorrent.txt color-model.txt bookmarks.txt dev-intro.txt \
	ecmascript.txt elinks.1.txt elinks.conf.5.txt elinkskeys.5.txt \
	events.txt exmode.txt faq.txt feedback.txt hacking.txt \
	installation.txt introduction.txt lua-scripting.txt mailcap.txt \
	manual.txt marks.txt mime.txt remote.txt small.txt tabs.txt \
	terminals.txt urlshortcuts.txt

PROTODOCDIR = $(PROTO_DIR)/usr/share/doc/elinks
PROTODOCFILES=$(DOCFILES:%=$(PROTODOCDIR)/%)

$(PROTODOCDIR):	$(INSTALL_32)
	$(MKDIR) $@

$(PROTODOCFILES):	$(PROTODOCDIR)
	$(INSTALL) -m 444 $(COMPONENT_SRC)/doc/$(@F) $(@D)

install:	$(INSTALL_32) $(PROTODOCDIR) $(PROTODOCFILES)
	(sed -f oracleman-stability $(COMPONENT_SRC)/doc/man/man1/elinks.1.in > \
		$(PROTO_DIR)/$(USRSHAREMAN1DIR)/elinks.1 ; \
	 sed -f oracleman-stability $(COMPONENT_SRC)/doc/man/man5/elinks.conf.5 > \
		$(PROTO_DIR)/$(USRSHAREMAN5DIR)/elinks.conf.5 ; \
	 sed -f oracleman-stability $(COMPONENT_SRC)/doc/man/man5/elinkskeys.5 > \
		$(PROTO_DIR)/$(USRSHAREMAN5DIR)/elinkskeys.5)

test: build
	@cd $(BUILD_DIR_32); $(MAKE) check

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
