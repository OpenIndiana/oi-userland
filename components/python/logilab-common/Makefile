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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		logilab-common
COMPONENT_VERSION=	1.2.2
COMPONENT_PROJECT_URL=	http://www.logilab.org/project/logilab-common/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:62b0d88d9276e86b48c7188cea8d91d8ff1744d046ea6323d40359aa53aef708
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_BUGDB=	python-mod/logilab-common
COMPONENT_ANITYA_ID=	13260

TPNO=			31342

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

build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

# The test output contains details from each test, in whatever order they
# complete. Use nawk to extract just the sections that summarizes the test
# result.
COMPONENT_TEST_CMD = $(PROTOUSRBINDIR)/pytest-$(PYTHON_VERSION)
COMPONENT_TEST_ARGS =
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
