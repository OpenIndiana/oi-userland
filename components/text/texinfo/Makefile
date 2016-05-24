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
# Copyright (c) 2012, 2016, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		texinfo
COMPONENT_VERSION=	6.0
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/texinfo/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:11ba4358696e8be3b3c7cfc88b89cf69525791aeabf0ee0a59ca58ebbd3471e4
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/texinfo/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/texinfo

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

INFOPATH := /usr/share/info
INFOPATH := $(INFOPATH):/usr/sfw/share/info
INFOPATH := $(INFOPATH):/usr/gnu/share/info
INFOPATH := $(INFOPATH):/usr/local/share/info
INFOPATH := $(INFOPATH):.

CPPFLAGS += -DDEFAULT_INFOPATH=\\\"$(INFOPATH)\\\"

CONFIGURE_OPTIONS  +=		CPPFLAGS="$(CPPFLAGS)"

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += \
	'-e "s|^.*$(CC).*$$|XXX_CC_XXX|g" ' \
	'-e "s|^.*$(CXX).*$$|XXX_CC_XXX|g" ' \
	'-e "s|^DEPDIR.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^mv.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^make.*: Nothing to be.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^make.*: Leaving directory.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^make.*: Entering directory.*$$|XXX_CC_XXX|g" ' \
	'-e "/^XXX_CC_XXX$$/d" '

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk
