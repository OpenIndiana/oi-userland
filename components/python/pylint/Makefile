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
# Copyright 2021 Gary Mills
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
#

BUILD_STYLE=	setup.py
BUILD_BITS=	NO_ARCH

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pylint
COMPONENT_VERSION=	2.9.3
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:9f0c8e6cd5c812fe4cc65b11dbce0573302171e385fcd9ebb48e0a5e99fd1dde
COMPONENT_ARCHIVE_URL= \
  https://github.com/PyCQA/$(COMPONENT_NAME)/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_PROJECT_URL=  https://github.com/PyCQA/$(COMPONENT_NAME)

# Set python version used by this product
PYTHON_VERSION=		3.9
PYTHON_VERSIONS=	3.9

include $(WS_MAKE_RULES)/common.mk

# There are several pylint documentation files that setup.py isn't installing
# but are present in the pylint package on other distributions. Copy them into
# the proto area "manually", so they can be included in the package.
PDOC =			$(PROTO_DIR)/usr/share/doc
PDOC_PYLINT =		$(PDOC)/pylint
PDOC_PYLINT_EXAMPLES =	$(PDOC_PYLINT)/examples

COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) $(PDOC_PYLINT) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(COMPONENT_SRC)/doc/tutorial.rst $(PDOC_PYLINT) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(COMPONENT_SRC)/doc/faq.rst $(PDOC_PYLINT) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(COMPONENT_SRC)/doc/index.rst $(PDOC_PYLINT) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(COMPONENT_SRC)/doc/intro.rst $(PDOC_PYLINT) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(COMPONENT_SRC)/doc/support.rst $(PDOC_PYLINT) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(COMPONENT_SRC)/README.rst $(PDOC_PYLINT) ;

COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) $(PDOC_PYLINT_EXAMPLES) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(COMPONENT_SRC)/examples/custom.py $(PDOC_PYLINT_EXAMPLES) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(COMPONENT_SRC)/examples/custom_raw.py $(PDOC_PYLINT_EXAMPLES) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(COMPONENT_SRC)/elisp/pylint.el $(PDOC_PYLINT_EXAMPLES) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(COMPONENT_SRC)/examples/pylintrc_camelcase $(PDOC_PYLINT_EXAMPLES) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(COMPONENT_SRC)/examples/pylintrc $(PDOC_PYLINT_EXAMPLES) ;
COMPONENT_POST_INSTALL_ACTION += \
	(cd $(PROTOUSRBINDIR); $(MV) epylint epylint-$(PYTHON_VERSION)) ;
COMPONENT_POST_INSTALL_ACTION += \
	(cd $(PROTOUSRBINDIR); $(MV) pylint pylint-$(PYTHON_VERSION)) ;
COMPONENT_POST_INSTALL_ACTION += \
	(cd $(PROTOUSRBINDIR); $(MV) pyreverse pyreverse-$(PYTHON_VERSION)) ;
COMPONENT_POST_INSTALL_ACTION += \
	(cd $(PROTOUSRBINDIR); $(MV) symilar symilar-$(PYTHON_VERSION)) ;

# The tests are run using python 3.9 only and require that
# the python-39 package is installed (does not have to be the default python).
# The astroid-39, isort-39, mccabe-39, and toml-39 packages must also
# be installed

# Use the python 3.9 libraries for testing.
test: PYTHON_VERSION=3.9

COMPONENT_TEST_ENV = PYTHONPATH=$(PROTO_DIR)$(PYTHON_VENDOR_PACKAGES)

# Run pytest-3.9
COMPONENT_TEST_DIR = $(COMPONENT_SRC)/tests
COMPONENT_TEST_CMD = /usr/bin/pytest-$(PYTHON_VERSION)
COMPONENT_TEST_ARGS =

# Typical failures for test target:
#=========================== short test summary info ============================
#FAILED test_import_graph.py::test_dependencies_graph[tests/regrtest_data/foo.dot]
#FAILED test_self.py::TestRunTC::test_pkginfo - AssertionError: expected outpu...
#FAILED test_self.py::TestRunTC::test_enable_all_works - assert "*************...
#...
#FAILED checkers/unittest_typecheck.py::TestTypeChecker::test_nomember_on_c_extension_error_msg
#FAILED checkers/unittest_typecheck.py::TestTypeChecker::test_nomember_on_c_extension_info_msg
#=== 14 failed, 1375 passed, 59 skipped, 200 deselected in 263.14s (0:04:23) ====

# Manually added test dependencies
REQUIRED_PACKAGES += library/python/flaky
REQUIRED_PACKAGES += library/python/hypothesis
REQUIRED_PACKAGES += library/python/isort
REQUIRED_PACKAGES += library/python/mccabe
REQUIRED_PACKAGES += library/python/pluggy
REQUIRED_PACKAGES += library/python/py
REQUIRED_PACKAGES += library/python/pytest
REQUIRED_PACKAGES += library/python/pytest-benchmark
REQUIRED_PACKAGES += library/python/pytest-reporter

REQUIRED_PACKAGES += runtime/python-39
