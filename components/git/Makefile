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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		git
COMPONENT_VERSION=	1.7.9.2
COMPONENT_PROJECT_URL=	http://git-scm.com/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:7aff1048480a8637de94e8d82744d312c0b5e060
COMPONENT_ARCHIVE_URL=	http://git-core.googlecode.com/files/$(COMPONENT_ARCHIVE)
#
# man pages are a separate archive
#
COMPONENT_ARCHIVE_1 =	$(COMPONENT_NAME)-manpages-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH_1 = sha1:d6992d899fb70e40983f94a2f96ad24b8ee93557
COMPONENT_ARCHIVE_URL_1 = http://git-core.googlecode.com/files/$(COMPONENT_ARCHIVE_1)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_PREFIX    =	/usr
CONFIGURE_OPTIONS  +=	--without-openssl
CONFIGURE_OPTIONS  +=	--libexecdir=/usr/lib
CONFIGURE_OPTIONS  +=	--with-perl=$(PERL)
CONFIGURE_OPTIONS  +=	--with-python=$(PYTHON)
CONFIGURE_OPTIONS  +=	CFLAGS="$(CFLAGS)"

COMPONENT_BUILD_ENV+=	NO_PERL_MAKEMAKER=1
COMPONENT_INSTALL_ENV+=	PERL_LIB=$(shell $(PERL) -MConfig -e 'print "$$Config{installvendorarch}"')
COMPONENT_INSTALL_ARGS+=	INSTALL="$(INSTALL)"

COMPONENT_TEST_TARGETS = test

# This runs configure but configure doesn't generate a Makefile.
# Instead a Makefile comes with git.
# Anyways viewpathing doesn't work.
# Therefore we need cloney to copy a set of files to build.

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

build:		$(BUILD_32)

install:	$(INSTALL_32) $(BUILD_DIR)/.manpages

# There are some known issues around I18N.
test:	$(TEST_32)

# These man pages come in a separate archive with no Makefile
# and Solaris likes some of them moved around hence we'll just
# do it manually here.

$(BUILD_DIR)/.manpages:
	cd $(BUILD_DIR) ; $(UNPACK) $(UNPACK_ARGS) ../$(COMPONENT_ARCHIVE_1)
	$(MKDIR) $(PROTOUSRSHAREMAN1DIR)
	$(MKDIR) $(PROTOUSRSHAREMAN4DIR)
	$(MKDIR) $(PROTOUSRSHAREMAN5DIR)
	cd $(BUILD_DIR) ; for manfile in man*/* ; \
	do \
		filename=`basename $$manfile`; \
		fname=$${filename%.*}; \
		ext=$${filename##*.}; \
		newext=1; \
		if [ $$ext = 5 ]; then newext=4; fi; \
		if [ $$ext = 7 ]; then newext=5; fi; \
		$(GSED) -e 's/\\m\[blue\]//g' -e 's/\\m\[\]//g' \
		        -e 's/"5"/"4"/' -e 's/(5)/(4)/g' \
			-e 's/"7"/"5"/' -e 's/(7)/(5)/g' $$manfile > \
		   $(PROTOUSRSHAREMANDIR)/man$$newext/$$fname.$$newext; \
	done
	$(TOUCH) $@


BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
