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

COMPONENT_NAME=		git
COMPONENT_VERSION=	1.7.3.2
PERL_VERSION=		5.10.0
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	sha1:cd8d806752aa6f5716cf193585024a002e098bf4
COMPONENT_ARCHIVE_URL=	http://kernel.org/pub/software/scm/git/$(COMPONENT_ARCHIVE)
#
# man pages are a separate archive
#
COMPONENT_ARCHIVE_1 =	$(COMPONENT_NAME)-manpages-$(COMPONENT_VERSION).tar.bz2
COMPONENT_ARCHIVE_HASH_1 = sha1:0be6fabbca523085e185711f2b80c99330f1e4ac
COMPONENT_ARCHIVE_URL_1 = http://kernel.org/pub/software/scm/git/$(COMPONENT_ARCHIVE_1)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_PREFIX    =	/usr
CONFIGURE_OPTIONS  +=	--without-openssl
CONFIGURE_OPTIONS  +=	--libexecdir=/usr/lib
CONFIGURE_OPTIONS  +=	--with-perl=/usr/perl5/$(PERL_VERSION)/bin/perl
CONFIGURE_OPTIONS  +=	--with-python=$(PYTHON.32)
CONFIGURE_OPTIONS  +=	CFLAGS="$(CFLAGS)"

COMPONENT_BUILD_ENV+=	NO_PERL_MAKEMAKER=1
COMPONENT_INSTALL_ENV+=	PERL_LIB=$(shell /usr/perl5/$(PERL_VERSION)/bin/perl -MConfig -e 'print "$$Config{installvendorarch}"')

COMPONENT_TEST_TARGETS = test

#
# This runs configure but configure doesn't generate a Makefile.
# Instead a Makefile comes with git ...
# Anyways viewpathing doesn't work.
# Therefore we need cloney to copy a set of files to build.
#
COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

#
# Processed man pages go here.
#
DOC=$(BUILD_DIR)/Documentation

PKG_MACROS	+=	PERL_ARCH=$(shell arch)
PKG_MACROS	+=	PERL_VERSION=$(PERL_VERSION)

build:		$(BUILD_32) $(DOC)/.manpages

install:	$(INSTALL_32)

#
# tests fully pass when done in the archive directory.
# fail here; probably due to the use of cloney.
#
test:	$(TEST_32)

#
# I know.  It's ugly.
# But these man pages come in a separate archive with no Makefile
# and Solaris likes some of them moved around hence we'll just
# do it manually here.
#
$(DOC)/.manpages:
	cd $(BUILD_DIR) ; $(UNPACK) $(UNPACK_ARGS) ../$(COMPONENT_ARCHIVE_1)
	$(MKDIR) $(@D)
	cd $(BUILD_DIR)/man1 ; for manfile in *.1; \
	do \
		name=`basename $$manfile .1`; \
		cat $$manfile > $(DOC)/$$name.1; \
	done
	cd $(BUILD_DIR)/man5 ; for manfile in *.5; \
	do \
		name=`basename $$manfile .5`; \
		sed 's/"5"/"4"/' $$manfile > $(DOC)/$$name.4; \
	done
	cd $(BUILD_DIR)/man7 ; for manfile in *.7; \
        do \
		name=`basename $$manfile .7`; \
		sed 's/"7"/"5"/' $$manfile > $(DOC)/$$name.5; \
	done
	$(TOUCH) $@


BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
