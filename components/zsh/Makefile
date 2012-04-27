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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk
include ../../make-rules/shared-targets.mk

COMPONENT_NAME=		zsh
COMPONENT_VERSION=	4.3.12
COMPONENT_PROJECT_URL=	http://www.zsh.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:4a9fd2dac76fc08fd1dc400deba854fcefa12ad76226d93fb6c01a801324f106
COMPONENT_ARCHIVE_URL=	http://downloads.sourceforge.net/project/zsh/zsh-dev/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_OPTIONS += -n
CONFIGURE_OPTIONS += --enable-cppflags="$(CPP_LARGEFILES)"
CONFIGURE_OPTIONS += --enable-dynamic
CONFIGURE_OPTIONS += --enable-etcdir=/etc
CONFIGURE_OPTIONS += --enable-function-subdirs
CONFIGURE_OPTIONS += --enable-ldflags="-zignore"
CONFIGURE_OPTIONS += --enable-libs="-lnsl"
CONFIGURE_OPTIONS += --enable-maildir-support
CONFIGURE_OPTIONS += --enable-multibyte
CONFIGURE_OPTIONS += --enable-pcre
CONFIGURE_OPTIONS += --with-tcsetpgrp
CONFIGURE_OPTIONS += --disable-gdbm

# pcre-config --libs unnecessarily emits "-L/usr/lib -R/usr/lib"; we remove it
# so that it doesn't end up in the binaries.
COMPONENT_POST_CONFIGURE_ACTION = \
	(cd $(@D); \
	sed -e 's,-L/usr/lib -R/usr/lib,,' \
		config.status > config.status.new; \
	mv config.status.new config.status; \
	chmod 755 config.status; \
	./config.status)

COMPOVERRIDES = $(shell find Completion -type f -print)

$(PROTOETCDIR)/%: % $(PROTOETCDIR)
	$(INS.file)

$(PROTOETCDIR)/zprofile: $(PROTOETCDIR)
	$(RM) $@; $(SYMLINK) profile $@

# makepro.awk leaves turds behind when using gawk 3.1.5 and LANG=en_US.UTF-8.
# Upgrading gawk would fix the problem, but for now, all we can do is change
# the language.
COMPONENT_BUILD_ENV += LANG=C

$(COMPONENT_SRC)/Completion/%: Completion/%
	$(CP) $< $@

$(COMPONENT_SRC)/LICENCE: prep

license: $(COMPONENT_SRC)/LICENCE
	iconv -f 8859-1 -t utf-8 $< > $@

CLEAN_PATHS += license

# common targets
build:		$(BUILD_32) $(COMPOVERRIDES:%=$(COMPONENT_SRC)/%)

install:	build $(INSTALL_32) $(PROTOETCDIR)/zprofile $(PROTOETCDIR)/zshrc license

# build does this always
test:		$(TEST_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
