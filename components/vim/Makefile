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

COMPONENT_NAME=		vim
COMPONENT_VERSION=	7.4
IPS_COMPONENT_VERSION=	$(shell echo $(HG_REV) | sed -e 's/-/./g' -e 's/v//')
# COMPONENT_SRC* is autodefined by the prep-{SCM} Makefile fragment
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_PROJECT_URL=	http://www.vim.org/

HG_REPO=	https://vim.googlecode.com/hg
HG_REV=		v7-4
HG_HASH= sha256:0c823290aebf4ea341be2f8280cc5906cdbbf772c54fa675afb0845983f23b60


TPNO=			21780

INSTALL_TARGET=
include $(WS_MAKE_RULES)/common.mk

PATCH_LEVEL =	0

PKG_MACROS +=	VIMVER=vim74

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
install:	$(INSTALL_64) $(X_VARIANT)/.built $(BUILD_DIR)/license

REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcursor
REQUIRED_PACKAGES += x11/library/toolkit/libxt
