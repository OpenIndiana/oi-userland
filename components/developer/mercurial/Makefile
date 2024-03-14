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
# Copyright 2017, 2021 Gary Mills
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#

BUILD_STYLE= setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mercurial
COMPONENT_VERSION=	5.9.3
COMPONENT_REVISION=		2
COMPONENT_SUMMARY=		The Mercurial Source Control Management System
COMPONENT_PROJECT_URL=		https://mercurial-scm.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:3b43f68977ad0fa75aa7f1e5c8f0a83ba935621ab2396129abb498e56d1be08e
COMPONENT_ARCHIVE_URL=	https://www.mercurial-scm.org/release/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			developer/versioning/mercurial
COMPONENT_CLASSIFICATION=	Development/Source Code Management
COMPONENT_LICENSE=		GPL-2.0-or-later
COMPONENT_LICENSE_FILE=		COPYING

SINGLE_PYTHON_VERSION = yes

TEST_STYLE = custom

include $(WS_MAKE_RULES)/common.mk

PKG_PROTO_DIRS +=	$(COMPONENT_SRC)/contrib
PKG_PROTO_DIRS +=	$(COMPONENT_SRC)/doc

# Use bash in sh mode for the tests; using /bin/sh on Solaris hasn't always
# worked, and using /bin/bash doesn't always work, either.  Also skip the
# tests which try to check all the code in the userland gate.  And finally,
# test the bits from the proto area, rather than rebuilding.  Given the way the
# test suite works, the hg executable must be named "hg".
TEST_BLACKLIST = \
	test-check-code.t \
	test-check-config.t \
	test-devel-warnings.t \
	test-hghave.t \
	test-run-tests.t \
	test-merge1.t \
	test-removeemptydirs.t \
	test-stdio.py \
	test-update-names.t

# https://www.mercurial-scm.org/pipermail/mercurial-devel/2017-March/093876.html
TEST_BLACKLIST += \
	test-ssh-bundle1.t \
	test-bundle2-exchange.t

COMPONENT_PRE_TEST_ACTION += \
	(cd $(BUILD_DIR); rm -f sh; ln -s /bin/bash sh; \
	printf "%s\n" $(TEST_BLACKLIST) > blacklist);

COMPONENT_TEST_DIR =	$(COMPONENT_SRC)/tests
COMPONENT_TEST_ENV =	PYTHONPATH=$(PROTO_DIR)/$(PYTHON_LIB)
COMPONENT_TEST_ENV +=	TERM=dumb
COMPONENT_TEST_ENV +=	HGTEST_JOBS=$(or $(HGTEST_JOBS),1)
COMPONENT_TEST_ENV +=	PATH=/usr/gnu/bin:/usr/bin
COMPONENT_TEST_CMD =	$(PYTHON)
COMPONENT_TEST_ARGS =	./run-tests.py \
			--shell $(BUILD_DIR)/sh \
			--with-hg $(PROTOUSRBINDIR)/hg \
			--blacklist $(BUILD_DIR)/blacklist
COMPONENT_TEST_TARGETS =

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += system/library
