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
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		saz-memcached
COMPONENT_VERSION=	2.7.1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:d89cb474eef11f1b8762df5322efa5a1bfb99ee40895e96c40c27f9477b21f66
COMPONENT_ARCHIVE_URL=	http://forgeapi.puppetlabs.com/v3/files/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://www.openstack.org/
COMPONENT_BUGDB=	utility/puppet

TPNO=			24167

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/puppetmodule.mk
include $(WS_MAKE_RULES)/ips.mk

MODULE_NAME =	memcached

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# common targets
build:		$(BUILD_NO_ARCH)

install: $(INSTALL_NO_ARCH)

REQUIRED_PACKAGES += system/management/puppet/puppetlabs-stdlib

test:		$(NO_TESTS)
