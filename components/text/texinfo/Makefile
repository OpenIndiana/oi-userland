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
# Copyright (c) 2012, 2016, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2019, Michal Nowak
# Copyright (c) 2021, Nona Hansel
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		texinfo
COMPONENT_VERSION=	7.0.3
COMPONENT_SUMMARY=	Documentation system for on-line information and printed output
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/texinfo/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:74b420d09d7f528e84f97aa330f0dd69a98a6053e7a4e01767eed115038807bf
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/gnu/texinfo/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		text/texinfo
COMPONENT_CLASSIFICATION=	Development/GNU

include $(WS_MAKE_RULES)/common.mk

INFOPATH := /usr/share/info
INFOPATH := $(INFOPATH):/usr/sfw/share/info
INFOPATH := $(INFOPATH):/usr/gnu/share/info
INFOPATH := $(INFOPATH):/usr/local/share/info
INFOPATH := $(INFOPATH):.

CPPFLAGS += -DDEFAULT_INFOPATH=\\\"$(INFOPATH)\\\"

CONFIGURE_OPTIONS  +=		--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  +=		CPPFLAGS="$(CPPFLAGS)"

# Set PATH to make sure run_parser_all.sh is able to find GNU diff
COMPONENT_TEST_ENV +=		PATH=$(PATH.gnu)

COMPONENT_TEST_TRANSFORMS += \
	'-e "s|^.*$(CC).*$$|XXX_CC_XXX|g" ' \
	'-e "s|^.*$(CXX).*$$|XXX_CC_XXX|g" ' \
	'-e "s|^DEPDIR.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^mv.*$$|XXX_CC_XXX|g" ' \
	'-e "s|.*ginstall.*|XXX_CC_XXX|g" ' \
	'-e "s|^make.*: Nothing to be.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^make.*: Leaving directory.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^make.*: Entering directory.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^make.*: .*is up to date.*$$|XXX_CC_XXX|g" ' \
	'-e "/^XXX_CC_XXX$$/d" '

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
