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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		vim
COMPONENT_VERSION=	8.0
COMPONENT_FULL_VERSION=	$(shell echo $(GIT_TAG) | sed -e 's/v//')
IPS_COMPONENT_VERSION=	$(shell echo $(GIT_TAG) | sed -e 's/v//' -e 's/\.0*\([1-9]\)/.\1/')
COMPONENT_LABEL=	$(COMPONENT_FULL_VERSION)
# COMPONENT_SRC* is autodefined by the prep-{SCM} Makefile fragment
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_PROJECT_URL=	http://www.vim.org/
COMPONENT_ANITYA_ID=	5092

GIT_REPO=		git://github.com/vim/vim
GIT_TAG=		v8.0.0095
GIT_COMMIT_ID=		182707a
GIT_HASH=		sha256:9a9c90d3c5576e7a3e092ec86469529a7386828086d3631eee1b8db4b4c80f37

TPNO=			32753

PKG_MACROS +=	VIMVER=vim$(subst .,,$(COMPONENT_VERSION))

X_VARIANT =	$(BUILD_DIR)/$(MACH64)-gvim
NOX_VARIANT =	$(BUILD_DIR)/$(MACH64)-vim

VARIANTS =	$(X_VARIANT) $(NOX_VARIANT)

$(VARIANTS:%=%/.configured):	BITS=64

BUILD_64 = 	$(VARIANTS:%=%/.built)
INSTALL_64 = 	$(VARIANTS:%=%/.installed)
# Test only the terminal variant.
TEST_64 = 	$(NOX_VARIANT)/.tested

include $(WS_MAKE_RULES)/common.mk

# Studio 12.3 and 12.4 allow unknown __attribute__s, but complain about them,
# making the build pretty loud about unknown "unused" attributes.  If we make
# it an error, configure will turn off its use.  See bug 20230791.
CFLAGS +=		-errwarn=E_ATTRIBUTE_UNKNOWN

# Make sure we use a 64-bit, multithreaded perl
CONFIGURE_ENV +=	vi_cv_path_perl=/usr/perl5/5.22/bin/perl
# Vim's configure script looks for a "python3" executable, per PEP 394
CONFIGURE_ENV +=	vi_cv_path_python3=/usr/bin/python3.5
# zh_CN.cp936.po has invalid characters which GNU msgfmt seems to be able to ignore.
CONFIGURE_ENV +=	MSGFMT=gmsgfmt
CONFIGURE_ENV +=	SOURCE_DATE_EPOCH=$(SOURCE_DATE_EPOCH)

CONFIGURE_OPTIONS +=	--with-features=huge
CONFIGURE_OPTIONS +=	--with-compiledby="the Solaris Userland build environment"
CONFIGURE_OPTIONS +=	--with-modified-by="Solaris Userland <discuss@solaris-userland.java.net>"
CONFIGURE_OPTIONS +=	--enable-luainterp=dynamic
CONFIGURE_OPTIONS +=	--enable-perlinterp=dynamic
CONFIGURE_OPTIONS +=	--enable-pythoninterp=dynamic
CONFIGURE_OPTIONS +=	--enable-python3interp=dynamic
CONFIGURE_OPTIONS +=	--enable-rubyinterp=dynamic

# We build two variants: with and without X support.
$(NOX_VARIANT)/.configured:	CONFIGURE_OPTIONS += --without-x
$(NOX_VARIANT)/.configured:	CONFIGURE_OPTIONS += --disable-gui
$(NOX_VARIANT)/.configured:	CONFIGURE_OPTIONS += --disable-gtktest
$(X_VARIANT)/.configured:	CONFIGURE_OPTIONS += --with-vim-name=gvim
$(X_VARIANT)/.configured:	CONFIGURE_OPTIONS += --with-x
$(X_VARIANT)/.configured:	CONFIGURE_OPTIONS += --enable-gui=gtk3

# Vim's build is too smart for itself and configure can't run outside of a
# complete source tree.
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

# For the GUI, install only the executable itself.
$(X_VARIANT)/.installed: COMPONENT_INSTALL_ARGS += -C src
$(X_VARIANT)/.installed: COMPONENT_INSTALL_TARGETS = installvimbin

COMPONENT_TEST_TARGETS = test

$(SOURCE_DIR)/runtime/doc/uganda.txt: prep

$(BUILD_DIR)/license: $(SOURCE_DIR)/runtime/doc/uganda.txt
	nawk '/begin of license/ {p=1; getline; next} /end of license/ {p=0} p == 1 {print}' $< > $@

# common targets
install:	$(INSTALL_64) $(BUILD_DIR)/license


REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += runtime/ruby-21
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += text/gnu-gettext
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcursor
REQUIRED_PACKAGES += x11/library/toolkit/libxt
