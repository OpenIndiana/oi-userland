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
# Copyright (c) 2013, 2017, Oracle and/or its affiliates. All rights reserved.
#
include ../../../../make-rules/shared-macros.mk


GIT_REPO= https://github.com/oracle/puppet-solaris_providers
GIT_BRANCH= v2.0.1
GIT_COMMIT_ID= 932309
GIT_HASH=  sha256:b858d0615642a6eff3215ecdee32dace3988bb296c6b02894b89eabbb907f4fc

COMPONENT_NAME=		puppet-solaris_providers
COMPONENT_VERSION=	2.0.1
COMPONENT_PROJECT_URL=	https://github.com/oracle/puppet-solaris_providers
# Construct our own SRC instead of using the default with GIT_COMMIT_ID
# archive from github strips leading v from release for vN named release tags
COMPONENT_SRC=$(COMPONENT_NAME)-$(shell echo $(GIT_BRANCH) | sed -e 's/v//')
COMPONENT_BUGDB=	utility/puppet

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/puppetmodule.mk
include $(WS_MAKE_RULES)/ips.mk

MODULE_NAME =	solaris_providers

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

PKG_OPTIONS +=	-I $(COMPONENT_DIR)

# Dump a list of files installed in the proto dir but not in the manifest
# this is a convenience target for the package maintainer
new-files: install
	$(PKGSEND) generate $(PROTO_DIR)/usr/puppetlabs/puppet/modules/ | $(GNU_GREP) -v '/docs/' | \
	    $(GSED)  -e 's/\(file\).*path=/\1 path=/' | \
	    $(CAT) oracle-solaris_providers.p5m - | $(GNU_GREP) -h '^file' | sort | uniq -c | \
	    $(GSED) -e '/ 2 /d' -e 's/   1 //'

# common targets
build: $(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:		$(NO_TESTS)

system-test:    $(NO_TESTS)

REQUIRED_PACKAGES += system/management/puppet
