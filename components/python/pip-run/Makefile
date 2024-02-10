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
#   $WS_TOOLS/python-integrate-project pip-run
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pip-run
HUMAN_VERSION =			12.6.0
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		pip-run - install packages and run Python with them
COMPONENT_PROJECT_URL =		https://github.com/jaraco/pip-run
COMPONENT_ARCHIVE_HASH =	\
	sha256:f734df9ea5c82bd38dc6dce0d8225a75a8099c1b7f7ae84879b45aaed347a377
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Remove misplaced docs and tests files
# https://github.com/jaraco/pip-run/issues/98
COMPONENT_POST_INSTALL_ACTION += \
	$(RM) -r $(PROTO_DIR)/$(PYTHON_LIB)/docs ; \
	$(RM) -r $(PROTO_DIR)/$(PYTHON_LIB)/tests ;

# Revert back unneeded PYV normalizations
COMPONENT_TEST_TRANSFORMS += "-e 's/py\$$(PYV)compat/py$(subst .,,$(PYTHON_VERSION))compat/'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/autocommand
PYTHON_REQUIRED_PACKAGES += library/python/jaraco-context
PYTHON_REQUIRED_PACKAGES += library/python/jaraco-env
PYTHON_REQUIRED_PACKAGES += library/python/jaraco-functools
PYTHON_REQUIRED_PACKAGES += library/python/jaraco-text
PYTHON_REQUIRED_PACKAGES += library/python/more-itertools
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/path
PYTHON_REQUIRED_PACKAGES += library/python/pip
PYTHON_REQUIRED_PACKAGES += library/python/platformdirs
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += library/python/tomli
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/flit-core
TEST_REQUIRED_PACKAGES.python += library/python/jaraco-path
TEST_REQUIRED_PACKAGES.python += library/python/jaraco-test
TEST_REQUIRED_PACKAGES.python += library/python/nbformat
TEST_REQUIRED_PACKAGES.python += library/python/pygments
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-checkdocs
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-enabler
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mypy
