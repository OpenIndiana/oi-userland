
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
# Copyright (c) 2014, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		hiera
COMPONENT_VERSION=	1.3.4
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).gem
COMPONENT_ARCHIVE_HASH=	\
    sha256:a3c85385ddda64916d453efeeb965151dc2454428d88f04f40d539559af27020
COMPONENT_ARCHIVE_URL=	http://rubygems.org/gems/$(COMPONENT_SRC).gem
COMPONENT_PROJECT_URL=  https://github.com/puppetlabs/hiera	
COMPONENT_BUGDB=	utility/puppet

TPNO=                   18210

# No gemspec is shipped with the gem. Create one
COMPONENT_POST_UNPACK_ACTION= \
    $(GEM) spec $(USERLAND_ARCHIVES)/$(COMPONENT_ARCHIVE) > $(SOURCE_DIR)/$(GEMSPEC)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/ips.mk
include $(WS_TOP)/make-rules/gem.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
