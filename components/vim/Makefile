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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

PATH=/usr/bin:/usr/gnu/bin

COMPONENT_NAME=		vim
COMPONENT_VERSION=	7.2
IPS_COMPONENT_VERSION=	$(shell find $(PATCH_DIR) -name $(PATCH_PATTERN) | \
				sort | tail -1 | cut -d/ -f2)
COMPONENT_SRC=		vim72
COMPONENT_PROJECT_URL=	http://www.vim.org/
COMPONENT_ARCHIVE=	vim-$(COMPONENT_VERSION).tar.bz2
COMPONENT_ARCHIVE_HASH=	sha1:a4b6641ca528fada71ea77c998a441495ed4984c
COMPONENT_ARCHIVE_URL=	ftp://ftp.vim.org/pub/vim/unix/$(COMPONENT_ARCHIVE)

PATCH_DIR =	$(COMPONENT_SRC)-patches
PATCH_PATTERN =	$(COMPONENT_VERSION).*
EXTRA_PATCHES =	$(PATCH_DIR)/runtime.patch $(PATCH_DIR)/vim-help.patch

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATCH_LEVEL =	0

PKG_MACROS +=	VIMVER=$(COMPONENT_SRC)

X_VARIANT =	$(BUILD_DIR)/$(MACH32)-gvim
NOX_VARIANT =	$(BUILD_DIR)/$(MACH32)-vim

VARIANTS =	$(X_VARIANT) $(NOX_VARIANT)

$(VARIANTS:%=%/.configured):	BITS=32

BUILD_32 = 	$(VARIANTS:%=%/.built)

# Only install the non-X variant.  We will cherry-pick gvim out of the build
# directory to avoid re-installing everything.
INSTALL_32 = 	$(NOX_VARIANT)/.installed

TEST_32 = 	$(NOX_VARIANT)/.tested

CONFIGURE_OPTIONS +=	--with-features=huge

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

$(SOURCE_DIR)/runtime/doc/uganda.txt: prep

$(BUILD_DIR)/license: $(SOURCE_DIR)/runtime/doc/uganda.txt
	nawk '/begin of license/ {p=1; getline; next} /end of license/ {p=0} p == 1 {print}' $< > $@

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32) $(X_VARIANT)/.built $(BUILD_DIR)/license

test:		$(TEST_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
