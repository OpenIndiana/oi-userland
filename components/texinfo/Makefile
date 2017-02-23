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
# Copyright (c) 2012, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
# using gcc makes parfait happy.
COMPILER= gcc
include ../../make-rules/shared-macros.mk
COMPONENT_NAME=		texinfo
COMPONENT_VERSION=	6.1
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/texinfo/ 
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:02582b6d9b0552f1cb1312be6bd7023e9799603c3b2320fa68a36029e4cbafbb
COMPONENT_ARCHIVE_URL=  http://ftp.gnu.org/gnu/texinfo/$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	4958

TPNO_TEXINFO=		27244
TPNO_TEXI2HTML=		9089

include $(WS_MAKE_RULES)/gnu-component.mk

INFOPATH := /usr/share/info
INFOPATH := $(INFOPATH):/usr/sfw/share/info
INFOPATH := $(INFOPATH):/usr/gnu/share/info
INFOPATH := $(INFOPATH):/usr/local/share/info
INFOPATH := $(INFOPATH):.

CPPFLAGS += -DDEFAULT_INFOPATH=\\\"$(INFOPATH)\\\"

CONFIGURE_OPTIONS  +=		--infodir=$(CONFIGURE_INFODIR)

# PERL_SCRIPTS_PROCESS needs to be the last COMPONENT_POST_INSTALL_ACTION
COMPONENT_POST_INSTALL_ACTION = 

COMPONENT_POST_INSTALL_ACTION += \
	$(INSTALL) -m 0755 texi2html.pl $(PROTOUSRBINDIR)/texi2html;

# Adjust '#!/usr/bin/perl'
PERL_SCRIPTS= \
	$(PROTOUSRBINDIR)/makeinfo \
	$(PROTOUSRBINDIR)/pod2texi \
	$(PROTOUSRBINDIR)/texi2any \
	$(PROTOUSRBINDIR)/texi2html

COMPONENT_POST_INSTALL_ACTION += $(PERL_SCRIPTS_PROCESS)

COMPONENT_TEST_TRANSFORMS += \
	'-e "s|^.*$(CC).*$$|XXX_CC_XXX|g" ' \
	'-e "s|^.*$(CXX).*$$|XXX_CC_XXX|g" ' \
	'-e "s|^DEPDIR.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^mv.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^make.*: Nothing to be.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^make.*: Leaving directory.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^make.*: Entering directory.*$$|XXX_CC_XXX|g" ' \
	'-e "s|.*ginstall.*$$|XXX_CC_XXX|g" ' \
	'-e "/^XXX_CC_XXX$$/d" '

REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library
