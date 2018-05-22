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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ruby-augeas
COMPONENT_VERSION=	0.5.0
COMPONENT_REVISION=	1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).gem
COMPONENT_ARCHIVE_HASH=	\
    sha256:42b0973c8ff88c5a903a1b126f1418a69eb3c8f4d45999055bfdce9b70e57101
COMPONENT_ARCHIVE_URL=	http://rubygems.org/gems/$(COMPONENT_SRC).gem
COMPONENT_PROJECT_URL=  https://github.com/hercules-team/ruby-augeas
COMPONENT_BUGDB=	utility/augeas
COMPONENT_ANITYA_ID=	7017
COMPONENT_CLASSIFICATION= System/Administration and Configuration
COMPONENT_FMRI=	library/ruby/augeas
COMPONENT_SUMMARY= Ruby bindings for Augeas configuration editor
COMPONENT_DESCRIPTION= The class Augeas provides bindings to augeas [http://augeas.net] library.
COMPONENT_LICENSE= LGPL-2.1	
COMPONENT_LICENSE_FILE=	augeas.license

TPNO=                   21871

# No gemspec is shipped with the gem. Create one
COMPONENT_POST_UNPACK_ACTION= \
    $(GEM) spec $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE) --ruby > $(SOURCE_DIR)/$(GEMSPEC)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk
include $(WS_MAKE_RULES)/gem.mk
include $(WS_MAKE_RULES)/ruby.mk

COMPONENT_TEST_CMD=	/usr/bin/rake
COMPONENT_TEST_DIR=	$(SOURCE_DIR)
COMPONENT_TEST_ARGS+=	test
COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
	'-e "/failures/p" '

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

REQUIRED_PACKAGES += library/augeas-libs
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += runtime/ruby-23
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
