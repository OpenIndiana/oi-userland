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
#   $WS_TOOLS/python-integrate-project validate-pyproject
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		validate-pyproject
HUMAN_VERSION =			0.10.1
COMPONENT_SUMMARY =		validate-pyproject - Validation library and CLI tool for checking on 'pyproject.toml' files using JSON Schema
COMPONENT_PROJECT_URL =		https://github.com/abravalheri/validate-pyproject/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/45/14/02314175f34f3f000691bc3f3cd41a34b9616dfbfa34cf5baa96cc643618/validate-pyproject-0.10.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:4621e7728bcfc42fcb54752dc3712c1f4d2e2eb99ee97c31e34f62cabea26254
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	NOTICE.txt

include $(WS_MAKE_RULES)/common.mk

# Testing fails with the checkdocs plugin installed
PYTEST_ADDOPTS += -p no:checkdocs

# There are two sets of test results (pytest is run twice by tox) so we need to
# sort the 2nd one too (the first one is sorted in setup.py.mk).
COMPONENT_TEST_TRANSFORMS += \
	"| ( \
		$(GSED) -u -e '/^=\{1,\} test session starts /q' ; \
		$(GSED) -u -e '/^=\{1,\} test session starts /q' ; \
		$(GSED) -u -e '/^$$/q' ; \
		$(GSED) -u -e 's/ *\[...%\]$$//' -e '/^$$/Q' | LC_ALL=C $(GSORT) | $(NAWK) '{print}END{if(NR>0)printf(\"\\\\n\")}' ; \
		$(CAT) \
	) | $(COMPONENT_TEST_TRANSFORMER) -e ''"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/packaging
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-randomly
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/tomli
TEST_REQUIRED_PACKAGES.python += library/python/trove-classifiers
