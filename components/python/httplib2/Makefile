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
# Copyright (c) 2012, 2017, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		httplib2
COMPONENT_VERSION=	0.9.2
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:c3aba1c9539711551f4d83e857b316b5134a1c4ddce98a875b7027be7dd6d988
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	http://code.google.com/p/httplib2/
COMPONENT_BUGDB=	python-mod/httplib2
COMPONENT_ANITYA_ID=	3887

TPNO=			29114

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# Set up the tests for running with multiple versions.  Many of the tests
# attempt to connect to URLs outside the firewall, some of which no longer
# exist.  Others could be set up on a local server with the tests directory
# from the git repo.  But for the most part, just expect the tests to fail.
COMPONENT_PRE_TEST_ACTION = \
	v=$$(echo $(PYTHON_VERSION) | cut -c1); \
	$(CP) -r $(COMPONENT_SRC)/python$$v/httplib2/test $(@D); \
	$(CP) $(COMPONENT_SRC)/python$$v/httplib2test.py $(@D); \

COMPONENT_TEST_DIR =	$(@D)
COMPONENT_TEST_ARGS =	httplib2test.py

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:		$(TEST_NO_ARCH)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)

