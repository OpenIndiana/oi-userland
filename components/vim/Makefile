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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

PATH=/usr/bin:/usr/gnu/bin

COMPONENT_NAME=		vim
COMPONENT_VERSION=	7.4
IPS_COMPONENT_VERSION=	$(shell echo $(COMPONENT_HG_REV) | sed -e 's/-/./g' -e 's/v//')
COMPONENT_SRC=		vim-$(COMPONENT_HG_REV)
COMPONENT_PROJECT_URL=	http://www.vim.org/
COMPONENT_ARCHIVE=	vim-$(COMPONENT_HG_REV).tar.bz2
COMPONENT_ARCHIVE_URL=	$(EXTERNAL_ARCHIVE_MIRROR)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:e7f4f411d9ff4c9dbf0ec57cc5da2e9d5e586e69fe3d69f31cbce9118e443507
COMPONENT_HG_URL=	https://vim.googlecode.com/hg
COMPONENT_HG_REV=	v7-4

COMPONENT_BUGDB=	utility/vim

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

HGREPODIR=		$(COMPONENT_NAME).hg
TARBALLDIR=		$(COMPONENT_NAME)-$(COMPONENT_HG_REV)

$(HGREPODIR)/.hg:
	hg clone -U $(COMPONENT_HG_URL) $(@D)

# Create the tarball.
hgball: $(HGREPODIR)/.hg
	cd $(HGREPODIR); \
	hg pull; \
	if [[ -n "$(COMPONENT_HG_NEWREV)" ]]; then \
		newrev=$(COMPONENT_HG_NEWREV); \
	else \
		newrev=$$(hg tags | awk '$$1 ~ /^v7-/ {print $$1; exit}'); \
	fi; \
	hg archive -p vim-$$newrev -r $$newrev ../vim-$$newrev.tar.bz2; \
	hg stat -ar --rev $(COMPONENT_HG_REV):$$newrev runtime src/po; \
	digest=$$(digest -a sha256 ../vim-$$newrev.tar.bz2); \
	$(GSED) -i \
		-e "s/^COMPONENT_ARCHIVE_HASH=.*/COMPONENT_ARCHIVE_HASH=	sha256:$$digest/" \
		-e "s/^COMPONENT_HG_REV=.*/COMPONENT_HG_REV=	$$newrev/" \
		../Makefile

PATCH_LEVEL =	0

PKG_MACROS +=	VIMVER=vim74

ASLR_MODE =	$(ASLR_ENABLE)

X_VARIANT =	$(BUILD_DIR)/$(MACH64)-gvim
NOX_VARIANT =	$(BUILD_DIR)/$(MACH64)-vim

VARIANTS =	$(X_VARIANT) $(NOX_VARIANT)

$(VARIANTS:%=%/.configured):	BITS=64

BUILD_64 = 	$(VARIANTS:%=%/.built)

# Only install the non-X variant.  We will cherry-pick gvim out of the build
# directory to avoid re-installing everything.
INSTALL_64 = 	$(NOX_VARIANT)/.installed

TEST_64 = 	$(NOX_VARIANT)/.tested

# Necessary to pass 64-bit flags to the link stage.
CC +=			$(CC_BITS)

# Put all the binaries directly in /usr/bin, not in /usr/bin/64.
CONFIGURE_BINDIR.64 =	$(CONFIGURE_PREFIX)/bin

# Use the 64-bit versions of pkg-config files (or GTK+ will add -R/usr/lib)
CONFIGURE_ENV +=	PKG_CONFIG_PATH="$(PKG_CONFIG_PATH)"

# Necessary to pass 64-bit flags to the compilation stage.
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"
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
build:		$(BUILD_64)

install:	$(INSTALL_64) $(X_VARIANT)/.built $(BUILD_DIR)/license

test:		$(TEST_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
