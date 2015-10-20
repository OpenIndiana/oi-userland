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
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		git
COMPONENT_VERSION=	2.6.1
COMPONENT_PROJECT_URL=	http://git-scm.com/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:fc7c727745d5eb0d796a16dc7c4b999c184830110e0aeb592c788597cc8e9ccd
COMPONENT_ARCHIVE_URL=	https://www.kernel.org/pub/software/scm/git/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/git

TPNO=			24887

#
# man pages are a separate archive
#
COMPONENT_SRC_1=        $(COMPONENT_NAME)-manpages-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_1 =	$(COMPONENT_SRC_1).tar.xz
COMPONENT_ARCHIVE_HASH_1 = \
    sha256:e4cf64edcecd284d9ef4e6ca7fa0e8556d2414b5d9881a9abfe477f95b416391
COMPONENT_ARCHIVE_URL_1 = https://www.kernel.org/pub/software/scm/git/$(COMPONENT_ARCHIVE_1)
UNPACK_ARGS_1 =		-r $(COMPONENT_SRC_1)
PKG_PROTO_DIRS +=	$(COMPONENT_SRC_1)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PKG_HARDLINKS +=	usr/lib/git-core/git-cherry-pick
PKG_HARDLINKS +=	usr/lib/git-core/git-remote-ftps

PKG_MACROS +=		PYVER=$(PYTHON_VERSION)

CONFIGURE_BINDIR.64 =	$(CONFIGURE_PREFIX)/bin
CONFIGURE_LIBDIR.64 =	$(CONFIGURE_PREFIX)/lib

CONFIGURE_PREFIX    =	/usr
CONFIGURE_OPTIONS  +=	--with-libpcre
CONFIGURE_OPTIONS  +=	--libexecdir=/usr/lib
CONFIGURE_OPTIONS  +=	--with-perl=$(PERL)
CONFIGURE_OPTIONS  +=	--with-python=$(PYTHON.$(PYTHON_VERSION))
CONFIGURE_OPTIONS  +=	CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS  +=	CPPFLAGS="-I/usr/include/pcre"

# Build fails if environment variable PROFILE is set.
COMPONENT_BUILD_ENV+=	PROFILE=
COMPONENT_INSTALL_ENV+=	PROFILE=
COMPONENT_TEST_ENV+=	PROFILE=

# We set prefix_SQ empty to make sure that perl's MakeMaker module doesn't grab
# the value from $prefix (set by configure) and force VENDORPREFIX to $prefix,
# thereby putting the perl modules in /usr/lib/Git.
COMPONENT_BUILD_ARGS+=		prefix_SQ=
COMPONENT_INSTALL_ARGS+=	prefix_SQ=
COMPONENT_INSTALL_ARGS+=	INSTALL="$(INSTALL)"

# get rid of terminal escape codes in test output
COMPONENT_TEST_ENV = TERM=dumb
# many failures; keep going; later versions of git are much cleaner
COMPONENT_TEST_ARGS += -k -i
COMPONENT_TEST_TARGETS = test

# This runs configure but configure doesn't generate a Makefile.
# Instead a Makefile comes with git.
# Anyways viewpathing doesn't work.
# Therefore we need cloney to copy a set of files to build.

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

ASLR_MODE = $(ASLR_ENABLE)

configure:	$(CONFIGURE_64)

build:		$(BUILD_64)

install:	$(INSTALL_64)

# There are some known issues around I18N.
test:		$(TEST_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)

REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/perl-512
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += web/curl
