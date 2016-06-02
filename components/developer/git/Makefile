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
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		git
COMPONENT_VERSION=	2.8.3
COMPONENT_PROJECT_URL=	http://git-scm.com/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:7d8e6c274a88b4a73b3c98c70d3438ec12871300ce8bb4ca179ea19fcf74aa91
COMPONENT_ARCHIVE_URL=	https://www.kernel.org/pub/software/scm/git/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/git
COMPONENT_FMRI=		developer/versioning/git
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	git.license
COMPONENT_SUMMARY=	git - Fast Version Control System
COMPONENT_DESCRIPTION=	Git is a free & open source, distributed version control system designed to handle everything from small to very large projects with speed and efficiency.
COMPONENT_CLASSIFICATION=	Development/Source Code Management

#
# man pages are a separate archive
#
COMPONENT_ARCHIVE_1 =	$(COMPONENT_NAME)-manpages-$(COMPONENT_VERSION).tar.xz
COMPONENT_ARCHIVE_HASH_1 = sha256:9d25e10c2bc327fdc59820bb00075799487095059d652fb32fea1cdb3a898bc6
COMPONENT_ARCHIVE_URL_1 = https://www.kernel.org/pub/software/scm/git/$(COMPONENT_ARCHIVE_1)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_PREFIX    =	/usr
CONFIGURE_OPTIONS  +=	--with-libpcre
CONFIGURE_OPTIONS  +=	--without-openssl
CONFIGURE_OPTIONS  +=	--libexecdir=/usr/lib
CONFIGURE_OPTIONS  +=	--with-perl=$(PERL)
CONFIGURE_OPTIONS  +=	--with-python=$(PYTHON)
CONFIGURE_OPTIONS  +=	CPPFLAGS="-I/usr/include/pcre"

COMPONENT_BUILD_ENV+=	NO_PERL_MAKEMAKER=1
COMPONENT_INSTALL_ENV+=	NO_PERL_MAKEMAKER=1
COMPONENT_INSTALL_ENV+=	PERL_LIB=$(shell $(PERL) -MConfig -e 'print "$$Config{installvendorarch}"')
COMPONENT_INSTALL_ARGS+=	INSTALL="$(INSTALL)"

COMPONENT_TEST_TARGETS = test
COMPONENT_TEST_ENV = PATH=/usr/gnu/bin:/usr/bin ENV='/usr/bin/env -i'

# This runs configure but configure doesn't generate a Makefile.
# Instead a Makefile comes with git.
# Anyways viewpathing doesn't work.
# Therefore we need cloney to copy a set of files to build.
# Overwrite symliked tests, because they relying on test assets being regular files.

COMPONENT_PRE_CONFIGURE_ACTION = \
	(chmod u+x $(COMPONENT_SRC)/t/*.sh  && $(CLONEY) $(SOURCE_DIR) $(@D) && \
	$(RM) -r $(@D)/t && $(CP) -rp $(COMPONENT_SRC)/t $(@D))


build:		$(BUILD_32)

install:	$(INSTALL_32) $(BUILD_DIR)/.manpages $(BUILD_DIR_32)/.bash-completion

# There are some known issues around I18N.
test:	$(TEST_32)

# These man pages come in a separate archive with no Makefile
# and Solaris likes some of them moved around hence we'll just
# do it manually here.

$(BUILD_DIR)/.manpages:
	cd $(BUILD_DIR) ; $(UNPACK) $(UNPACK_ARGS) $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_1)
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

$(BUILD_DIR_32)/.bash-completion:
	$(MKDIR) $(PROTOUSRSHAREDIR)/bash-completion/completions
	$(CP) -RLp $(BUILD_DIR_32)/contrib/completion/git-completion.bash $(PROTOUSRSHAREDIR)/bash-completion/completions/git
	(cd $(PROTOUSRSHAREDIR)/bash-completion/completions; $(LN) -s git gitk)
	$(TOUCH) $@

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/python-26
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += web/curl
