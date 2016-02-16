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
# Copyright (c) 2013, 2016, Oracle and/or its affiliates. All rights reserved.
#
include ../../../../make-rules/shared-macros.mk


GIT_REPO= https://github.com/oraclesolaris/puppet-solaris_providers
GIT_BRANCH= v1.0.2
GIT_COMMIT_ID= c4b6092
GIT_HASH=  sha256:12b9c1a169e95494dc2c8463fecafcdf4875642bc0970a2a59fdbc4cfa09df50

COMPONENT_NAME=		puppet-solaris_providers
COMPONENT_VERSION=	1.0.2
COMPONENT_PROJECT_URL=	https://github.com/oraclesolaris/puppet-solaris_providers
# github releases provide direct archive downloads
COMPONENT_ARCHIVE_URL= $(COMPONENT_PROJECT_URL)/archive/$(GIT_BRANCH).tar.gz
# Construct our own SRC instead of using the default with GIT_COMMIT_ID
# archive from github strips leading v from release for vN named release tags
COMPONENT_SRC=$(COMPONENT_NAME)-$(shell echo $(GIT_BRANCH) | sed -e 's/v//')
COMPONENT_BUGDB=	utility/puppet

TPNO=			18128

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/puppetmodule.mk
include $(WS_MAKE_RULES)/ips.mk


MODULE_NAME =	solaris_providers

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

PKG_OPTIONS +=	-I $(COMPONENT_DIR)

# generate manifest for files supplied from git repo on demand
oracle-solaris_providers-github.frag: install
	$(PKGSEND) generate $(PROTO_DIR)/etc/puppet/modules/ | \
		$(GSED) -e 's/\(file\|dir\).*path=/\1 path=/' | \
		$(PKGFMT) > oracle-solaris_providers-github.frag

# common targets
build: $(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:		$(NO_TESTS)

system-test:    $(NO_TESTS)

PKG_PROTO_DIRS += files
REQUIRED_PACKAGES += system/management/puppet
