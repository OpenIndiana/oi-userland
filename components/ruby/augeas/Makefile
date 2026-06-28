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
# Copyright (c) 2015, 2017, Oracle and/or its affiliates. All rights reserved.
# Copyright 2017 Andreas Grueninger, Grueninger GmbH, (grueni). All rights reserved.
# Copyright 2026 Klaus Ziegler
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ruby-augeas
COMPONENT_VERSION=	0.6.0
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).gem
COMPONENT_ARCHIVE_HASH=	\
    sha256:002bd237d8dce4b918384cc3043254bf5264efe81f663d1c9ac7b41cbe4df8d2
COMPONENT_ARCHIVE_URL=	https://rubygems.org/gems/$(COMPONENT_SRC).gem
COMPONENT_PROJECT_URL=  https://github.com/hercules-team/ruby-augeas
COMPONENT_BUGDB=	utility/augeas
COMPONENT_ANITYA_ID=	7017
COMPONENT_CLASSIFICATION= System/Administration and Configuration
COMPONENT_FMRI=	library/ruby/augeas
COMPONENT_SUMMARY= Ruby bindings for Augeas configuration editor
COMPONENT_DESCRIPTION= The class Augeas provides bindings to augeas [http://augeas.net] library.
COMPONENT_LICENSE= LGPL-2.1	
COMPONENT_LICENSE_FILE=	augeas.license

# No gemspec is shipped with the gem. Create one
COMPONENT_POST_UNPACK_ACTION= \
    $(GEM) spec $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE) --ruby > $(SOURCE_DIR)/$(GEMSPEC)

include $(WS_MAKE_RULES)/common.mk
include $(WS_MAKE_RULES)/gem.mk
include $(WS_MAKE_RULES)/ruby.mk

# to get GNU make instead of make
PATH= $(PATH.gnu)

ifeq ($(MACH), i386)
RUBY_CPU=x86_64
else
RUBY_CPU=sparc
endif

# these macros are used in the package manifest
PKG_MACROS += RUBY_VER=$(RUBY_VER)
PKG_MACROS += RUBY_LIB_VER=$(RUBY_LIB_VER)
PKG_MACROS += RUBY_CPU=$(RUBY_CPU)

COMPONENT_TEST_CMD=	/usr/bin/rake32
COMPONENT_TEST_DIR=	$(SOURCE_DIR)
COMPONENT_TEST_ARGS+=	test
COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
	'-e "/failures/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += library/augeas-libs
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += runtime/ruby-32
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
