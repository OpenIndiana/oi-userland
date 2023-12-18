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
HUMAN_VERSION =			8.0.2
COMPONENT_SUMMARY =		diff_cover - Run coverage and linting reports on diffs
COMPONENT_PROJECT_URL =		https://github.com/Bachmann1234/diff-cover
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/d8/10/44951fe435a18444ed351419f7f189421c7eebee036587e5442bb6a01d98/diff_cover-8.0.2.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:b2fa9d551e33af3791ff0b8b913a9238d379a371185a1d4a7f64981c33fda8b3
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIRED_PACKAGES.python += library/python/pytest-datadir
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/chardet
PYTHON_REQUIRED_PACKAGES += library/python/jinja2
PYTHON_REQUIRED_PACKAGES += library/python/pluggy
PYTHON_REQUIRED_PACKAGES += library/python/poetry-core
PYTHON_REQUIRED_PACKAGES += library/python/pygments
PYTHON_REQUIRED_PACKAGES += runtime/python
