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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		logilab-astng
COMPONENT_VERSION=	0.19.0
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:87fe682ec98599c0088f228ba94cb50a7ed99466
COMPONENT_ARCHIVE_URL=	http://ftp.logilab.org/pub/astng/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/ips.mk
include ../../make-rules/setup.py.mk

# common targets

build:		$(BUILD_32)

install:	$(INSTALL_32)

# No runnable tests; the existing tests are missing a runtests.py
# file, which isn't fixed until logilab-ast version 0.20.1.
# When logilab-astng is updated, we can change this test target to do:
#        (cd $(COMPONENT_SRC)/test; $(ENV) - \
#        PYTHONPATH=$(PROTO_DIR)/usr/lib/python2.6/vendor-packages \
#        ./fulltest.sh)
test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
