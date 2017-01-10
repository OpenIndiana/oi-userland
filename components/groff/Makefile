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
# Copyright (c) 2013, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		groff
COMPONENT_VERSION=	1.22.3
COMPONENT_ARCHIVE_HASH= \
    sha256:3a48a9d6c97750bfbd535feeb5be0111db6406ddb7bb79fc680809cda6d828a5

TPNO=			28205

TEST_TARGET= $(NO_TESTS)

# Complex dependencies on ON only available in S12.
ifeq ($(BUILD_TYPE), evaluation)
PUBLISH_STAMP=
endif

include $(WS_MAKE_RULES)/gnu-component.mk

# Deliver scripts from 64-bit build to the 32-bit location.
CONFIGURE_LIBDIR.64 =	$(CONFIGURE_LIBDIR.32)

CONFIGURE_OPTIONS += \
    --with-appresdir=$(CONFIGURE_PREFIX)/X11/lib/X11/app-defaults

CXXFLAGS += -std=c++11

# Don't generate tmac wrappers for the Solaris troff macro packages.
# Some man pages (such as groff.1) use long macro name definitions
# which fail in compatibility mode. See:
# http://osdir.com/ml/printing.groff.general/2003-07/msg00088.html
# for more details.
COMPONENT_INSTALL_ARGS += tmac_wrap=""

COMPONENT_INSTALL_ARGS += legacyfontdir=$(PROTOUSRLIBDIR)/font
COMPONENT_INSTALL_ARGS += sys_tmac_prefix=$(PROTOUSRSHARELIBDIR)/tmac/

COMPONENT_PRE_INSTALL_ACTION = \
	($(MKDIR) $(PROTOUSRBINDIR) )

# Adjust '#!/usr/bin/perl'
PERL_SCRIPTS= \
	$(PROTOUSRSHAREDIR)/groff/$(COMPONENT_VERSION)/font/devpdf/util/BuildFoundries \
	$(PROTOUSRLIBDIR)/groff/grog/subs.pl \
	$(PROTOUSRLIBDIR)/groff/gpinyin/subs.pl \
	$(PROTOUSRLIBDIR)/groff/groffer/main_subs.pl \
	$(PROTOUSRLIBDIR)/groff/groffer/subs.pl \
	$(PROTOUSRLIBDIR)/groff/groffer/man.pl \
	$(PROTOUSRBINDIR)/chem \
	$(PROTOUSRBINDIR)/roff2pdf \
	$(PROTOUSRBINDIR)/roff2dvi \
	$(PROTOUSRBINDIR)/roff2text \
	$(PROTOUSRBINDIR)/roff2html \
	$(PROTOUSRBINDIR)/groffer \
	$(PROTOUSRBINDIR)/glilypond \
	$(PROTOUSRBINDIR)/gperl \
	$(PROTOUSRBINDIR)/roff2ps \
	$(PROTOUSRBINDIR)/gpinyin \
	$(PROTOUSRBINDIR)/roff2x \
	$(PROTOUSRBINDIR)/gropdf \
	$(PROTOUSRBINDIR)/grog \
	$(PROTOUSRBINDIR)/mmroff \
	$(PROTOUSRBINDIR)/afmtodit \
	$(PROTOUSRBINDIR)/pdfmom

REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library/c++-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += text/doctools
REQUIRED_PACKAGES += text/gawk
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxmu
REQUIRED_PACKAGES += x11/library/toolkit/libxaw7
REQUIRED_PACKAGES += x11/library/toolkit/libxt
