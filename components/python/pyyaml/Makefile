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
# Copyright (c) 2014, 2017, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		PyYAML
COMPONENT_VERSION=	3.11
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:c36c938a872e5ff494938b33b14aaa156cb439ec67548fcab3535bb78b0846e8
COMPONENT_ARCHIVE_URL=	http://pyyaml.org/download/pyyaml/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://pyyaml.org/wiki/PyYAML
COMPONENT_BUGDB=	python-mod/pyyaml
COMPONENT_ANITYA_ID=	4123

TPNO=			28704

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

COMPONENT_TEST_DIR =		$(SOURCE_DIR)
COMPONENT_TEST_ARGS.2.7 =	./tests/lib/test_all.py
COMPONENT_TEST_ARGS.3.4 =	./tests/lib3/test_all.py
COMPONENT_TEST_ARGS.3.5 =	./tests/lib3/test_all.py
COMPONENT_TEST_ARGS =		$(COMPONENT_TEST_ARGS.$(PYTHON_VERSION))

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:		$(TEST_NO_ARCH)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)

