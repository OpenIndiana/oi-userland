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

PATH=/usr/bin:/usr/gnu/bin

COMPONENT_NAME=		vim
COMPONENT_VERSION=	7.3
IPS_COMPONENT_VERSION=	$(shell echo $(COMPONENT_HG_REV) | sed -e 's/-/./g' -e 's/v//')
COMPONENT_SRC=		vim-$(COMPONENT_HG_REV)
COMPONENT_PROJECT_URL=	http://www.vim.org/
COMPONENT_ARCHIVE=	vim-$(COMPONENT_HG_REV).tar.bz2
COMPONENT_ARCHIVE_URL=	$(EXTERNAL_ARCHIVE_MIRROR)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:33dbd364780a078708f62569b440128f13fb574095b2adcd0ef9f98f3168760c
COMPONENT_HG_URL=	https://vim.googlecode.com/hg
COMPONENT_HG_REV=	v7-3-584
COMPONENT_HG_REV_OLD=	v7-3-584

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

HGREPODIR=		$(COMPONENT_NAME).hg
TARBALLDIR=		$(COMPONENT_NAME)-$(COMPONENT_HG_REV)

$(HGREPODIR)/.hg:
	hg clone -U $(COMPONENT_HG_URL) $(@D)

hgball-pull: $(HGREPODIR)/.hg
	hg -R $(HGREPODIR) pull

hgball: COMPONENT_HG_REV = $(shell hg -R $(HGREPODIR) tags | awk '$$1 ~ /^v7-/ {print $$1; exit}')

# Create the tarball.  It should contain the working directory of the repo at
# the desired revision, but not the .hg directory.  Note that the digest will
# be different every time because .hg doesn't set the timestamps of the files
# in the working directory.
hgball: hgball-pull
	rm -rf $(TARBALLDIR)
	hg clone -u $(COMPONENT_HG_REV) $(HGREPODIR) $(TARBALLDIR)
	rm -rf $(TARBALLDIR)/.hg
	tar jcf $(COMPONENT_ARCHIVE) $(TARBALLDIR)
	hg --cwd $(HGREPODIR) stat -ar --rev $(COMPONENT_HG_REV_OLD):tip runtime src/po
	digest=$$(digest -a sha256 $(COMPONENT_ARCHIVE)); \
		/usr/gnu/bin/sed -i \
			-e "s/^COMPONENT_ARCHIVE_HASH=.*/COMPONENT_ARCHIVE_HASH=	sha256:$$digest/" \
			-e "s/^COMPONENT_HG_REV=.*/COMPONENT_HG_REV=	$(COMPONENT_HG_REV)/" \
			-e "s/^COMPONENT_HG_REV_OLD=.*/COMPONENT_HG_REV_OLD=	$(COMPONENT_HG_REV)/" \
			Makefile

PATCH_LEVEL =	0

PKG_MACROS +=	VIMVER=vim73

X_VARIANT =	$(BUILD_DIR)/$(MACH32)-gvim
NOX_VARIANT =	$(BUILD_DIR)/$(MACH32)-vim

VARIANTS =	$(X_VARIANT) $(NOX_VARIANT)

$(VARIANTS:%=%/.configured):	BITS=32

BUILD_32 = 	$(VARIANTS:%=%/.built)

# Only install the non-X variant.  We will cherry-pick gvim out of the build
# directory to avoid re-installing everything.
INSTALL_32 = 	$(NOX_VARIANT)/.installed

TEST_32 = 	$(NOX_VARIANT)/.tested

# Override a broken imake that's always providing a 64-bit library directory.
CONFIGURE_OPTIONS +=	--x-libraries=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS +=	--with-features=huge
CONFIGURE_OPTIONS +=	--with-compiledby="the Solaris Userland build environment"
CONFIGURE_OPTIONS +=	--with-modified-by="Solaris Userland <userland-discuss@opensolaris.org>"
CONFIGURE_OPTIONS +=	--enable-luainterp=dynamic
# XXX Perl compilation fails, for some reason.
# - Perl_croak_nocontext is redefined (embed.h, line 5157), having something to
#   do with PERL_IMPLICIT_CONTEXT, which is discussed in perlguts(1).  This is
#   just a warning, but looks like it might have nasty consequences.
# - The declaration of Perl_Gthr_key_ptr() has a problem with its argument of
#   type pTHX.  if_perl.xs defines that to void if it's not already defined,
#   but perl.h probably does something else to it, not sure what yet.  This
#   also appears to have something to do with PERL_IMPLICIT_CONTEXT.
# CONFIGURE_OPTIONS +=	--enable-perlinterp=dynamic
CONFIGURE_OPTIONS +=	--enable-pythoninterp=dynamic
CONFIGURE_OPTIONS +=	--enable-rubyinterp=dynamic

# We build two variants: with and without X support.
$(NOX_VARIANT)/.configured:	CONFIGURE_OPTIONS += --without-x
$(NOX_VARIANT)/.configured:	CONFIGURE_OPTIONS += --disable-gui
$(NOX_VARIANT)/.configured:	CONFIGURE_OPTIONS += --disable-gtktest
$(X_VARIANT)/.configured:	CONFIGURE_OPTIONS += --with-vim-name=gvim
$(X_VARIANT)/.configured:	CONFIGURE_OPTIONS += --with-x
$(X_VARIANT)/.configured:	CONFIGURE_OPTIONS += --enable-gui=gtk2
$(X_VARIANT)/.configured:	CONFIGURE_OPTIONS += --enable-gtk2-check

# Vim's build is too smart for itself and configure can't run outside of a
# complete source tree.
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_TEST_TARGETS = test

$(SOURCE_DIR)/runtime/doc/uganda.txt: prep

$(BUILD_DIR)/license: $(SOURCE_DIR)/runtime/doc/uganda.txt
	nawk '/begin of license/ {p=1; getline; next} /end of license/ {p=0} p == 1 {print}' $< > $@

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32) $(X_VARIANT)/.built $(BUILD_DIR)/license

test:		$(TEST_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
