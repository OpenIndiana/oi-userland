
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
# Copyright (c) 2016, 2017, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk
include ../../../make-rules/ruby.mk

#
# Override the inherited RUBY values in shared-macros.mk to be
# a later release.
# 
RUBY_VERSION=       2.1
RUBY_LIB_VERSION=   2.1.0
RUBY_VERSIONS=      2.1.0

COMPONENT_NAME=		stomp
COMPONENT_VERSION=	1.3.4
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).gem
COMPONENT_ARCHIVE_HASH=	\
    sha256:adc77e8760236bd6d751991e0a4fc2bfd5443fc45dd5cfedb0d8c99273bc5897
COMPONENT_ARCHIVE_URL=	http://rubygems.org/gems/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  https://rubygems.org/gems/stomp/
COMPONENT_BUGDB=	utility/ruby-stomp
COMPONENT_ANITYA_ID=	4499

TPNO=                   23495

# No gemspec is shipped with the gem. Create one
COMPONENT_POST_UNPACK_ACTION= \
    $(GEM) spec --ruby $(COMPONENT_ARCHIVE) > $(SOURCE_DIR)/$(GEMSPEC)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk
include $(WS_MAKE_RULES)/gem.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:		$(NO_TESTS)

system-test:    $(NO_TESTS)


REQUIRED_PACKAGES += network/amqp/rabbitmq
REQUIRED_PACKAGES += runtime/ruby-21
REQUIRED_PACKAGES += system/core-os
