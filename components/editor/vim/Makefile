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
# Copyright (c) 2011, 2019, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2017, Ken Mays
# Copyright (c) 2019, Michal Nowak
# Copyright (c) 2020, Nona Hansel
# Copyright (c) 2022-2023 Niklas Poslovski
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		vim
COMPONENT_VERSION=	9.0.1677
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_PROJECT_URL=	https://www.vim.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/vim/vim/archive/v$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:c5750a1d47b514d60d59d9956e2953fb1673d1dd797bfec09c1bff721743e55c

include $(WS_MAKE_RULES)/common.mk

COMPONENT_POST_UNPACK_ACTION += ( chmod +x $(@D)/configure  $(@D)/src/auto/configure $(@D)/src/configure $(@D)/src/mkinstalldirs ; \
				  find $(@D) -name \*.sh  -exec chmod +x '{}' ';' ; rm $(@D)/src/po/{ko.po,zh_CN.po} ; )

NOX_VARIANT = $(BUILD_DIR)/$(MACH64)-vim
X_VARIANT =	$(BUILD_DIR)/$(MACH64)-gvim

VARIANTS = $(X_VARIANT) $(NOX_VARIANT)

$(VARIANTS:%=%/.configured): BITS=64

BUILD_64 = $(VARIANTS:%=%/.built)
INSTALL_64 = $(VARIANTS:%=%/.installed)
# Test only the terminal variant.
TEST_64 = $(NOX_VARIANT)/.tested

# vim uses self-defined INFINITY/NAN, which don't work well on illumos
CFLAGS += -std=c99 -D_XOPEN_SOURCE=600 -D__EXTENSIONS__

CONFIGURE_ENV += PATH=$(PATH.gnu)
# Make sure we use a 64-bit, multithreaded perl
CONFIGURE_ENV += vi_cv_path_perl=/usr/perl5/5.36/bin/perl
# Vim's configure script looks for a "python3" executable, per PEP 394
CONFIGURE_ENV += vi_cv_path_python3=/usr/bin/python$(PYTHON_VERSION)
# zh_CN.cp936.po has invalid characters which GNU msgfmt seems to be able to ignore.
CONFIGURE_ENV += MSGFMT=gmsgfmt

CONFIGURE_OPTIONS += --with-features=huge
CONFIGURE_OPTIONS += --with-compiledby="oi-userland build environment"
CONFIGURE_OPTIONS += --with-modified-by="OpenIndiana <oi-dev@openindiana.org>"
CONFIGURE_OPTIONS += --enable-luainterp=dynamic
CONFIGURE_OPTIONS += --enable-perlinterp=dynamic
CONFIGURE_OPTIONS += --enable-rubyinterp=dynamic
CONFIGURE_OPTIONS += --with-ruby-command=/usr/bin/ruby26
CONFIGURE_OPTIONS += --enable-pythoninterp=dynamic
CONFIGURE_OPTIONS += --enable-python3interp=dynamic
CONFIGURE_OPTIONS += --enable-terminal

# We build two variants: with and without X support.
$(NOX_VARIANT)/.configured:	CONFIGURE_OPTIONS += --without-x
$(NOX_VARIANT)/.configured:	CONFIGURE_OPTIONS += --disable-gui
$(NOX_VARIANT)/.configured:	CONFIGURE_OPTIONS += --disable-gtktest
$(NOX_VARIANT)/.configured:	CONFIGURE_OPTIONS += --disable-canberra
$(X_VARIANT)/.configured:	CONFIGURE_OPTIONS += --with-vim-name=gvim
$(X_VARIANT)/.configured:	CONFIGURE_OPTIONS += --with-x
$(X_VARIANT)/.configured:	CONFIGURE_OPTIONS += --enable-gui=gtk3
$(X_VARIANT)/.configured:	CONFIGURE_OPTIONS += --enable-gtk3-check
$(X_VARIANT)/.configured:	CONFIGURE_OPTIONS += --enable-canberra

# Vim's build is too smart for itself and configure can't run outside of a
# complete source tree.
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D) ; cd $(@D)/src ; aclocal ; autoconf ; )

# For the GUI, install only the executable itself.
$(X_VARIANT)/.installed: COMPONENT_INSTALL_ARGS += -C src
$(X_VARIANT)/.installed: COMPONENT_INSTALL_TARGETS = installvimbin

COMPONENT_TEST_TARGETS = test

$(SOURCE_DIR)/runtime/doc/uganda.txt: prep

$(BUILD_DIR)/license: $(SOURCE_DIR)/runtime/doc/uganda.txt
	nawk '/begin of license/ {p=1; getline; next} /end of license/ {p=0} p == 1 {print}' $< > $@

install:	$(INSTALL_64) $(BUILD_DIR)/license

# Manually added build dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
# libssp is in $(GCC_RUNTIME_PKG) since gcc-10
# Manually added dependency on python runtime
PYTHON_REQUIRED_PACKAGES += runtime/python

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/xdg/libcanberra
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/security/libsodium
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/toolkit/libxt
