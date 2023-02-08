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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright 2021 Gary Mills
# Copyright 2022 Andreas Wacknitz
#

BUILD_STYLE=	setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pylint
COMPONENT_VERSION=	2.12.2
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	Pylint is a Python static code analysis tool
COMPONENT_DESCRIPTION=	Pylint is a Python static code analysis tool which looks for programming errors, helps enforcing a coding standard, sniffs for code smells and offers simple refactoring suggestions.
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:411308682f3d4578bb769e7fa549c8f34edf1033871d2e8cd5c3ce16a5741c59
# The sources provided by pypi are missing tests and doc files, thus we are using the sources provided by Github:
#COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_ARCHIVE_URL=	https://github.com/PyCQA/pylint/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_PROJECT_URL=	https://www.pylint.org/
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_FMRI=			developer/python/$(COMPONENT_NAME)
COMPONENT_LICENSE=	GPLv2

SINGLE_PYTHON_VERSION = yes

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_ENV += PYTHON=$(PYTHON)

# There are several pylint documentation files that setup.py isn't installing
# but are present in the pylint package on other distributions. Copy them into
# the proto area "manually", so they can be included in the package.
PDOC =			$(PROTO_DIR)/usr/share/doc
PDOC_PYLINT =		$(PDOC)/pylint
PDOC_PYLINT_EXAMPLES =	$(PDOC_PYLINT)/examples

COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) $(PDOC_PYLINT) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(SOURCE_DIR)/doc/tutorial.rst $(PDOC_PYLINT) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(SOURCE_DIR)/doc/faq.rst $(PDOC_PYLINT) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(SOURCE_DIR)/doc/index.rst $(PDOC_PYLINT) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(SOURCE_DIR)/doc/intro.rst $(PDOC_PYLINT) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(SOURCE_DIR)/doc/support.rst $(PDOC_PYLINT) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(SOURCE_DIR)/README.rst $(PDOC_PYLINT) ;

COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) $(PDOC_PYLINT_EXAMPLES) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(SOURCE_DIR)/examples/custom.py $(PDOC_PYLINT_EXAMPLES) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(SOURCE_DIR)/examples/custom_raw.py $(PDOC_PYLINT_EXAMPLES) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(SOURCE_DIR)/elisp/pylint.el $(PDOC_PYLINT_EXAMPLES) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(SOURCE_DIR)/examples/pylintrc_camelcase $(PDOC_PYLINT_EXAMPLES) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(SOURCE_DIR)/examples/pylintrc $(PDOC_PYLINT_EXAMPLES) ;

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/astroid
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/isort
PYTHON_REQUIRED_PACKAGES += library/python/mccabe
PYTHON_REQUIRED_PACKAGES += library/python/platformdirs
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/toml
PYTHON_REQUIRED_PACKAGES += library/python/typing-extensions
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/astroid
TEST_REQUIRED_PACKAGES.python += library/python/black
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/coveralls
TEST_REQUIRED_PACKAGES.python += library/python/flake8
TEST_REQUIRED_PACKAGES.python += library/python/flake8-typing-imports
TEST_REQUIRED_PACKAGES.python += library/python/gitpython
TEST_REQUIRED_PACKAGES.python += library/python/isort
TEST_REQUIRED_PACKAGES.python += library/python/mypy
TEST_REQUIRED_PACKAGES.python += library/python/pip
TEST_REQUIRED_PACKAGES.python += library/python/pre-commit
TEST_REQUIRED_PACKAGES.python += library/python/pyenchant
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-benchmark
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-profiling
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
TEST_REQUIRED_PACKAGES.python += library/python/tbump
TEST_REQUIRED_PACKAGES.python += library/python/types-pkg-resources
TEST_REQUIRED_PACKAGES.python += library/python/types-toml
