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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/shared-targets.mk

COMPONENT_NAME=		zsh
COMPONENT_VERSION=	5.2
COMPONENT_PROJECT_URL=	http://www.zsh.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:f17916320ffaa844bbd7ce48ceeb5945fc5f3eff64b149b4229bbfbdf3795a9d
COMPONENT_ARCHIVE_URL=	http://downloads.sourceforge.net/project/zsh/zsh/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

TPNO=			26447

BUILD_TARGET=
INSTALL_TARGET=
include $(WS_MAKE_RULES)/common.mk

CONFIGURE_LIBDIR.64= $(CONFIGURE_LIBDIR.32)

CONFIGURE_OPTIONS += -n
CONFIGURE_OPTIONS += --enable-cppflags="$(CPP_LARGEFILES)"
CONFIGURE_OPTIONS += --enable-dynamic
CONFIGURE_OPTIONS += --enable-etcdir=$(ETCDIR)
CONFIGURE_OPTIONS += --enable-function-subdirs
# Zsh uses the compiler to link, so we need to pass CC_BITS, not LD_BITS.
CONFIGURE_OPTIONS += --enable-ldflags="$(CC_BITS) -zignore"
ifeq ($(OS_VERSION),5.11)
CONFIGURE_OPTIONS += --enable-libs="-lnsl"
endif
CONFIGURE_OPTIONS += --enable-maildir-support
CONFIGURE_OPTIONS += --enable-multibyte
CONFIGURE_OPTIONS += --enable-pcre
CONFIGURE_OPTIONS += --with-tcsetpgrp
CONFIGURE_OPTIONS += --disable-gdbm

# pcre-config --libs unnecessarily emits "-R$(USRLIBDIR64)"; we remove it so that it
# doesn't end up in the binaries.
COMPONENT_POST_CONFIGURE_ACTION = \
	(cd $(@D); \
	sed -e "s,-R$(USRLIBDIR64),," \
		config.status > config.status.new; \
	mv config.status.new config.status; \
	chmod 755 config.status; \
	./config.status)

COMPOVERRIDES = $(shell test -d find && find Completion -type f -print)

$(PROTOETCDIR)/%: % $(PROTOETCDIR)
	$(INS.file)

$(PROTOETCDIR)/zprofile: $(PROTOETCDIR)
	$(RM) $@; $(SYMLINK) profile $@

# makepro.awk leaves turds behind when using gawk 3.1.5 and a UTF-8 locale.
# Upgrading gawk would fix the problem, but for now, all we can do is change
# the language.
COMPONENT_BUILD_ENV += LC_ALL=C

# The configure test for NIS tests to make sure that NIS is working, not whether
# it's available to compile against.  We actually want to go through the switch
# in all cases, so we force it off, regardless of whether the build environment
# has it enabled.
CONFIGURE_ENV += zsh_cv_sys_nis=no

$(COMPONENT_SRC)/Completion/%: Completion/%
	$(CP) $< $@

$(COMPONENT_SRC)/LICENCE: prep

license: $(COMPONENT_SRC)/LICENCE
	tail +13 $< > $@

CLEAN_PATHS += license

# common targets
build:		$(BUILD_64) $(COMPOVERRIDES:%=$(COMPONENT_SRC)/%)

install:	build $(INSTALL_64) $(PROTOETCDIR)/zprofile $(PROTOETCDIR)/zshrc license

REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += system/library/math
