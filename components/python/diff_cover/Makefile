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
HUMAN_VERSION =			9.7.1
COMPONENT_SUMMARY =		Run coverage and linting reports on diffs
COMPONENT_PROJECT_URL =		https://github.com/Bachmann1234/diff-cover
COMPONENT_ARCHIVE_HASH =	\
	sha256:a03b78bc64b7dc27dda7f11c46bc6d44f4e121c8fb9a5068d41f20a05d463548
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# This project uses poetry to manage test dependencies.
TEST_REQUIREMENTS_POETRY += dev

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/chardet
REQUIRED_PACKAGES.python += library/python/jinja2
REQUIRED_PACKAGES.python += library/python/pluggy
REQUIRED_PACKAGES.python += library/python/poetry-core
REQUIRED_PACKAGES.python += library/python/pygments
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/black
TEST_REQUIRED_PACKAGES.python += library/python/isort
TEST_REQUIRED_PACKAGES.python += library/python/pycodestyle
TEST_REQUIRED_PACKAGES.python += library/python/pyflakes
TEST_REQUIRED_PACKAGES.python += library/python/pylint
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-datadir
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
