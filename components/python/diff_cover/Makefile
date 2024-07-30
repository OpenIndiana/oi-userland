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
#   $WS_TOOLS/python-integrate-project diff_cover
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		diff_cover
HUMAN_VERSION =			9.1.1
COMPONENT_SUMMARY =		Run coverage and linting reports on diffs
COMPONENT_PROJECT_URL =		https://github.com/Bachmann1234/diff-cover
COMPONENT_ARCHIVE_HASH =	\
	sha256:b5ed20955b3ebdee94476e429cfd9f1324e1c19a04c4aae32a893b11c3673f1e
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# This project uses poetry to manage test dependencies.
TEST_REQUIREMENTS_POETRY += dev

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/chardet
PYTHON_REQUIRED_PACKAGES += library/python/jinja2
PYTHON_REQUIRED_PACKAGES += library/python/pluggy
PYTHON_REQUIRED_PACKAGES += library/python/poetry-core
PYTHON_REQUIRED_PACKAGES += library/python/pygments
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/black
TEST_REQUIRED_PACKAGES.python += library/python/flake8
TEST_REQUIRED_PACKAGES.python += library/python/isort
TEST_REQUIRED_PACKAGES.python += library/python/pycodestyle
TEST_REQUIRED_PACKAGES.python += library/python/pydocstyle
TEST_REQUIRED_PACKAGES.python += library/python/pyflakes
TEST_REQUIRED_PACKAGES.python += library/python/pylint
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-datadir
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
