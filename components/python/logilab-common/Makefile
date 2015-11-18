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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		logilab-common
COMPONENT_VERSION=	0.63.2
COMPONENT_PROJECT_URL=	http://www.logilab.org/project/logilab-common/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:603ba00c9bb09219a3bd2906c214d9455481110dacc472f450b53d5ae90f28e7
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_BUGDB=	python-mod/logilab-common

TPNO=			22842

# Syntax issues: not Python 3 ready. pyorbit not 3.4 ready.
PYTHON_VERSIONS=	2.7

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk
include $(WS_MAKE_RULES)/setup.py.mk

# rename pytest to its versioned name; mediated links (depending on
# the python version) in the manifest will create the link from pytest
# to the correct pytest-${PYTHON_VERSION}
# compile all of the python .py files in the proto area since setup.py doesn't
# seem to be doing it for this component.
COMPONENT_POST_INSTALL_ACTION = \
	(cd $(PROTO_DIR)/usr/bin ; $(MV) -f pytest pytest-$(PYTHON_VERSION)) ; \
	($(PYTHON) -m compileall $(PROTO_DIR)$(PYTHON_VENDOR_PACKAGES))

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# common targets

build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)
	
# The tests are run using python 2.7 only and require that the
# python-27 package is installed (does not have to be the default python). 

# Use the python 2.7 libraries (via PYTHONPATH setting) for testing.
test: PYTHON_VERSION=2.7

# The test output contains details from each test, in whatever order they
# complete. Use nawk to extract just the sections that summarizes the test result.
COMPONENT_TEST_CMD = $(PROTOUSRBINDIR)/pytest-2.7
COMPONENT_TEST_ARGS =
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_TRANSFORMER =	$(NAWK)
COMPONENT_TEST_TRANSFORMS = "'/Ran (.+) test cases/{ sub(/in(.+)\)/, \"\"); print }/(.+) modules OK/'"

# This modutils test should expect the logilab module to be found under the
# standard /usr/lib/python* location when we test installed system bits,
# the opposite of what it expects when testing built bits in the proto area.
# Temporarily modify its expected result for system-test,
# and restore it afterwards.
COMPONENT_PRE_SYSTEM_TEST_ACTION += \
	($(MV) $(COMPONENT_SRC)/test/unittest_modutils.py $(COMPONENT_SRC)/test/unittest_modutils.py-orig; \
	$(GSED) -e "s/self.assertEqual(modutils.is_standard_module('logilab'), False)/self.assertEqual(modutils.is_standard_module('logilab'), True)/" $(COMPONENT_SRC)/test/unittest_modutils.py-orig > $(COMPONENT_SRC)/test/unittest_modutils.py)
COMPONENT_SYSTEM_TEST_CMD = /usr/bin/pytest-$(PYTHON_VERSION)
COMPONENT_SYSTEM_TEST_ARGS =
COMPONENT_POST_SYSTEM_TEST_ACTION += \
	$(MV) $(COMPONENT_SRC)/test/unittest_modutils.py-orig $(COMPONENT_SRC)/test/unittest_modutils.py

test:	$(TEST_NO_ARCH)

system-test:    $(SYSTEM_TEST_NO_ARCH)

REQUIRED_PACKAGES += library/python/pyorbit-27
REQUIRED_PACKAGES += library/python/six-27
