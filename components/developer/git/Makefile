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
# Copyright (c) 2020, Michal Nowak
# Copyright (c) 2021, Nona Hansel
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		git
COMPONENT_VERSION=	2.42.0
COMPONENT_SUMMARY=	git - Fast Version Control System
COMPONENT_DESCRIPTION=	Git is a free & open source, distributed version control system designed to handle everything from small to very large projects with speed and efficiency.
COMPONENT_PROJECT_URL=	https://git-scm.com/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:3278210e9fd2994b8484dd7e3ddd9ea8b940ef52170cdb606daa94d887c93b0d
COMPONENT_ARCHIVE_URL=	https://www.kernel.org/pub/software/scm/git/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		developer/versioning/git
COMPONENT_CLASSIFICATION=	Development/Source Code Management
COMPONENT_LICENSE=	GPLv2

#
# man pages are a separate archive
#
COMPONENT_ARCHIVE_1=		$(COMPONENT_NAME)-manpages-$(COMPONENT_VERSION).tar.xz
COMPONENT_ARCHIVE_HASH_1=	sha256:03e0dc60a077ad31b10119e6619af8b50e652bd5c8a95c891523d73af1e573b9
COMPONENT_ARCHIVE_URL_1=	https://www.kernel.org/pub/software/scm/git/$(COMPONENT_ARCHIVE_1)

include $(WS_MAKE_RULES)/common.mk

# With PATH.gnu gmake test gives a slightly better success rate:
PATH= $(PATH.gnu)

LDFLAGS += -lnsl -lsocket

CONFIGURE_PREFIX= /usr
CONFIGURE_OPTIONS += --with-libpcre2
CONFIGURE_OPTIONS += --without-openssl
CONFIGURE_OPTIONS += --libexecdir=/usr/lib
CONFIGURE_OPTIONS += --with-perl=$(PERL)
CONFIGURE_OPTIONS += --with-python=$(PYTHON)
CONFIGURE_OPTIONS += CPPFLAGS="-I/usr/include/pcre"

COMPONENT_BUILD_ENV += NO_PERL_MAKEMAKER=1
COMPONENT_BUILD_ENV += V=1
COMPONENT_INSTALL_ENV += NO_PERL_MAKEMAKER=1

PKG_MACROS += PERLVER=$(PERL_VERSION)

# This runs configure but configure doesn't generate a Makefile.
# Instead a Makefile comes with git.
# Anyways viewpathing doesn't work.
# Therefore we need cloney to copy a set of files to build.
# Overwrite symlinked tests, because they are relying on test assets being regular files.
COMPONENT_PRE_CONFIGURE_ACTION= \
	(chmod u+x $(COMPONENT_SRC)/t/*.sh  && $(CLONEY) $(SOURCE_DIR) $(@D) && \
	$(RM) -r $(@D)/t && $(CP) -rp $(COMPONENT_SRC)/t $(@D))

PKG_HARDLINKS += usr/lib/git-core/git
PKG_HARDLINKS += usr/lib/git-core/git-cvsserver
PKG_HARDLINKS += usr/lib/git-core/git-gui
PKG_HARDLINKS += usr/lib/git-core/git-remote-ftps
PKG_HARDLINKS += usr/lib/git-core/git-shell
PKG_HARDLINKS += usr/lib/git-core/scalar

# We want the perl modules to install the vendor_perl directory, and their
# manpages to install in the normal perl manpage directory, but the default
# behavior is to put the modules in /usr/lib.  Setting these four variables
# massages the perl to get files to go where we want.
COMPONENT_INSTALL_ARGS += INSTALL="$(INSTALL)"
COMPONENT_INSTALL_ARGS += perllibdir=$(shell $(PERL) -MConfig -e 'print "$$Config{installvendorarch}"')
COMPONENT_INSTALL_ARGS += VENDORPREFIX=$(shell $(PERL) -MConfig -e 'print "$$Config{installvendorlib}"')
COMPONENT_INSTALL_ARGS += PERLPREFIX=$(shell $(PERL) -MConfig -e 'print "$$Config{installvendorarch}"')
COMPONENT_INSTALL_ARGS += INSTALLVENDORLIB=$(shell $(PERL) -MConfig -e 'print "$$Config{installvendorlib}"')

COMPONENT_TEST_ENV += LC_ALL=C.UTF-8

# many failures; keep going; later versions of git are much cleaner
COMPONENT_TEST_ARGS += -k -i
# If GITTEST_JOBS is set, then run the jobs in parallel (to that number)
COMPONENT_TEST_ARGS += $(if $(GITTEST_JOBS),-j$(GITTEST_JOBS),)
COMPONENT_TEST_TARGETS = test
# Put each test result in a file; necessary if jobs run in parallel
COMPONENT_TEST_TARGETS += GIT_TEST_OPTS=--tee
COMPONENT_TEST_TARGETS += DEFAULT_TEST_TARGET=test-noclean
# Compile the test results and put that into the test output file instead
COMPONENT_POST_TEST_ACTION= \
	(cd $(COMPONENT_TEST_DIR)/t/test-results; for i in *.out; do \
		echo "*** $${i%.out}.sh ***"; \
		cat $$i; \
	done; \
	cd ..; \
	$(GMAKE) -s aggregate-results) &> $(COMPONENT_TEST_OUTPUT)

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

$(BUILD_DIR_64)/.contrib: $(BUILD_DIR_64)/.contrib-subtree
	$(MKDIR) $(PROTOUSRSHAREDIR)/bash-completion/completions
	PATH="$(PATH)" $(GMAKE) -C $(BUILD_DIR_64)/contrib/diff-highlight
	$(CP) -RLp $(BUILD_DIR_64)/contrib/diff-highlight/diff-highlight $(PROTOUSRBINDIR)/diff-highlight
	$(CP) -RLp $(BUILD_DIR_64)/contrib/completion/git-completion.bash $(PROTOUSRSHAREDIR)/bash-completion/completions/git
	(cd $(PROTOUSRSHAREDIR)/bash-completion/completions; $(LN) -sf git gitk)
	$(TOUCH) $@

# Install steps taken from contrib/subtree/INSTALL
$(BUILD_DIR_64)/.contrib-subtree:
	PATH="$(PATH)" $(GMAKE) -C $(BUILD_DIR_64)/contrib/subtree DESTDIR=$(PROTO_DIR)
	PATH="$(PATH)" $(GMAKE) -C $(BUILD_DIR_64)/contrib/subtree DESTDIR=$(PROTO_DIR) install
	PATH="$(PATH)" $(GMAKE) -C $(BUILD_DIR_64)/contrib/subtree DESTDIR=$(PROTO_DIR) install-doc
	$(TOUCH) $@

install:	$(INSTALL_64) $(BUILD_DIR)/.manpages $(BUILD_DIR_64)/.contrib

# Test dependencies
TEST_REQUIRED_PACKAGES += developer/fakeroot
TEST_REQUIRED_PACKAGES += developer/versioning/cvs
TEST_REQUIRED_PACKAGES += system/library/iconv/extra
TEST_REQUIRED_PACKAGES += system/library/iconv/unicode
TEST_REQUIRED_PACKAGES += system/library/iconv/utf-8
TEST_REQUIRED_PACKAGES += library/perl-5/cgi
TEST_REQUIRED_PACKAGES += library/perl-5/dbi
TEST_REQUIRED_PACKAGES += library/perl-5/dbd-sqlite
TEST_REQUIRED_PACKAGES += library/perl-5/subversion
TEST_REQUIRED_PACKAGES += locale/is
TEST_REQUIRED_PACKAGES += locale/is-extra

# Needed to generate git-subtree documentation
REQUIRED_PACKAGES += text/asciidoc
REQUIRED_PACKAGES += text/xmlto

# As long as we disabled pkgdepend on git-p4 we need to add this manually:
PYTHON_REQUIRED_PACKAGES += runtime/python

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/pcre2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += web/curl
