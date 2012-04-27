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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#

#
# This build is modeled after the one in SFW.
# Attempts to use the native build methods fail because we
# don't have the scm (scheme) interpreter.
# So just install this and get on with it.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		slib
COMPONENT_VERSION=	3b1
COMPONENT_PROJECT_URL=	http://people.csail.mit.edu/jaffer/SLIB/
COMPONENT_SRC=		$(COMPONENT_NAME)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-$(COMPONENT_VERSION).zip
COMPONENT_ARCHIVE_HASH=	\
    sha256:8e3ec24d51be03ebb7357ad9a2f3554056b86dafbc9e48d1d491aeda1efa566f
COMPONENT_ARCHIVE_URL=	http://groups.csail.mit.edu/mac/ftpdir/scm/OLD/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/ips.mk

# Lie to IPS packaging about the version because it doesn't like
# COMPONENT_VERSION's with letters.
# So if COMPONENT_VERSION changes above this needs to change as well.
IPS_COMPONENT_VERSION=  3.1.1

# nothing to really build
build: $(SOURCE_DIR)/.prep

install: build
	cd $(SOURCE_DIR) ; \
		$(MAKE) prefix=$(PROTO_DIR)/usr/ INSTALL=ginstall \
			man1dir=$(PROTOUSRSHAREMAN1DIR) install

test:	$(NO_TESTS)

clean::
	$(RM) -r $(BUILD_DIR)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include ../../make-rules/depend.mk
