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
# Copyright (c) 2017 Ken Mays
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		vim
COMPONENT_VERSION=	8.1.0005
# Remove leading zeros in the patch-level part of $COMPONENT_VERSION (IPS does not like them)
IPS_COMPONENT_VERSION=  $(shell echo $(COMPONENT_VERSION) | sed -e 's/\.00*\([1-9]\)/.\1/')
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://www.vim.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/vim/vim/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=sha256:e8e2d11b0012f109c5158c76a06dac33871756fd862fce018c4ebb99bd985988

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_POST_UNPACK_ACTION += ( chmod +x $(@D)/configure  $(@D)/src/auto/configure $(@D)/src/configure $(@D)/src/mkinstalldirs ; \
				  find $(@D) -name \*.sh  -exec chmod +x '{}' ';' )

PKG_MACROS +=  VIMVER=vim81

X_VARIANT =	$(BUILD_DIR)/$(MACH32)-gvim
NOX_VARIANT =	$(BUILD_DIR)/$(MACH32)-vim

VARIANTS =	$(X_VARIANT) $(NOX_VARIANT)

BUILD_32 = 	$(VARIANTS:%=%/.built)

INSTALL_32 = 	$(VARIANTS:%=%/.installed)

TEST_32 = 	$(NOX_VARIANT)/.tested

# vim uses self-defined INFINITY/NAN, which don't work well on illumos
CFLAGS += -std=c99 -D_XOPEN_SOURCE=600

# Make sure we use a default perl
CONFIGURE_ENV +=	vi_cv_path_perl=$(PERL)
# zh_CN.cp936.po has invalid characters which GNU msgfmt seems to be able to ignore.
CONFIGURE_ENV +=	MSGFMT=gmsgfmt
CONFIGURE_ENV +=	SOURCE_DATE_EPOCH=$(SOURCE_DATE_EPOCH)

CONFIGURE_OPTIONS +=	--with-features=huge
CONFIGURE_OPTIONS +=	--with-compiledby="oi-userland build environment"
CONFIGURE_OPTIONS +=	--with-modified-by="OpenIndiana <oi-dev@openindiana.org>"
CONFIGURE_OPTIONS +=	--enable-luainterp=dynamic
CONFIGURE_OPTIONS +=	--enable-perlinterp=dynamic
CONFIGURE_OPTIONS +=	--enable-pythoninterp=dynamic
CONFIGURE_OPTIONS +=	--enable-rubyinterp=dynamic
CONFIGURE_OPTIONS +=	--enable-terminal

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

# For the GUI, install only the executable itself.
$(X_VARIANT)/.installed: COMPONENT_INSTALL_ARGS += -C src
$(X_VARIANT)/.installed: COMPONENT_INSTALL_TARGETS = installvimbin

COMPONENT_TEST_TARGETS = test

$(SOURCE_DIR)/runtime/doc/uganda.txt: prep

$(BUILD_DIR)/license: $(SOURCE_DIR)/runtime/doc/uganda.txt
	nawk '/begin of license/ {p=1; getline; next} /end of license/ {p=0} p == 1 {print}' $< > $@

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32) $(BUILD_DIR)/license

#  A lot of tests fail with 'Cannot create directory'
test:		$(TEST_32)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/toolkit/libxt
