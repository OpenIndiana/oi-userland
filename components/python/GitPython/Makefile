#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# This file was automatically generated using the following command:
#   $WS_TOOLS/python-integrate-project GitPython
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		GitPython
HUMAN_VERSION =			3.1.44
COMPONENT_SUMMARY =		GitPython is a Python library used to interact with Git repositories
COMPONENT_PROJECT_URL =		https://github.com/gitpython-developers/GitPython
COMPONENT_ARCHIVE_URL =		\
	https://github.com/gitpython-developers/GitPython/archive/refs/tags/$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:30101221a869968d4fe2a010ee9ca1134c22272089d9e9fee2040a68541443c6
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# see README.md
COMPONENT_PRE_TEST_ACTION += ( \
	$(RM) -r $(COMPONENT_TEST_DIR)/.git-test-tree ; \
	git clone https://github.com/gitpython-developers/GitPython.git $(COMPONENT_TEST_DIR)/.git-test-tree ; \
	cd $(COMPONENT_TEST_DIR)/.git-test-tree ; \
	git tag __testing_point__ ; \
	git checkout master ; \
	git reset --hard HEAD~1 ; \
	git reset --hard HEAD~1 ; \
	git reset --hard HEAD~1 ; \
	git reset --hard __testing_point__ ; \
	git submodule update --init --recursive ; \
) ;
COMPONENT_TEST_ENV += GIT_PYTHON_TEST_GIT_REPO_BASE=$(COMPONENT_TEST_DIR)/.git-test-tree

# Testing is using /tmp/repos.  We need to make sure it does not exists to get
# consistent test results.
COMPONENT_PRE_TEST_ACTION += $(RM) -r /tmp/repos ;

# Force no colors to override defaults in tox.ini
TOX_POSARGS += --color=no

# Manually added test dependencies
TEST_REQUIRED_PACKAGES += developer/versioning/git

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/gitdb
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/ddt
TEST_REQUIRED_PACKAGES.python += library/python/mypy
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
TEST_REQUIRED_PACKAGES.python += library/python/tomli
TEST_REQUIRED_PACKAGES.python += library/python/typing-extensions
