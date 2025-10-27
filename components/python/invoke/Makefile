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
#   $WS_TOOLS/python-integrate-project invoke
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		invoke
HUMAN_VERSION =			2.2.1
COMPONENT_SUMMARY =		Pythonic task execution
COMPONENT_PROJECT_URL =		https://pyinvoke.org
COMPONENT_ARCHIVE_HASH =	\
	sha256:515bf49b4a48932b79b024590348da22f39c4942dff991ad1fb8b8baea1be707
COMPONENT_LICENSE =		BSD-2-Clause
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# invoke --> invocations ==> invoke
#
# To break loops we need to allow this project to integrate without testing in
# a case the required projects are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS += dev-requirements.txt

# https://github.com/pyinvoke/invoke/issues/933#issuecomment-1541046545
PYTEST_ADDOPTS += -s

# https://github.com/pyinvoke/invoke/issues/933#issuecomment-1638389449
PYTEST_ADDOPTS += --deselect tests/runners.py::Local_::pty::when_pty_True_we_use_pty_fork_and_os_exec
PYTEST_ADDOPTS += --deselect tests/runners.py::Local_::pty::pty_uses_WEXITSTATUS_if_WIFEXITED
PYTEST_ADDOPTS += --deselect tests/runners.py::Local_::pty::pty_uses_WTERMSIG_if_WIFSIGNALED
PYTEST_ADDOPTS += --deselect tests/runners.py::Local_::pty::WTERMSIG_result_turned_negative_to_match_subprocess
PYTEST_ADDOPTS += --deselect tests/runners.py::Local_::pty::pty_is_set_to_controlling_terminal_size
PYTEST_ADDOPTS += --deselect tests/runners.py::Local_::pty::spurious_OSErrors_handled_gracefully
PYTEST_ADDOPTS += --deselect tests/runners.py::Local_::pty::other_spurious_OSErrors_handled_gracefully
PYTEST_ADDOPTS += --deselect tests/runners.py::Local_::pty::non_spurious_OSErrors_bubble_up
PYTEST_ADDOPTS += --deselect tests/runners.py::Local_::pty::stop_mutes_errors_on_pty_close
PYTEST_ADDOPTS += --deselect tests/runners.py::Local_::pty::fallback::can_be_overridden_by_kwarg
PYTEST_ADDOPTS += --deselect tests/runners.py::Local_::pty::fallback::can_be_overridden_by_config
PYTEST_ADDOPTS += --deselect tests/runners.py::Local_::pty::fallback::overridden_fallback_affects_result_pty_value
PYTEST_ADDOPTS += --deselect tests/runners.py::Local_::shell::defaults_to_bash_or_cmdexe_when_pty_True
PYTEST_ADDOPTS += --deselect tests/runners.py::Local_::shell::may_be_overridden_when_pty_True
PYTEST_ADDOPTS += --deselect tests/runners.py::Local_::env::uses_execve_for_pty_True

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/alabaster
TEST_REQUIRED_PACKAGES.python += library/python/black
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/flake8
TEST_REQUIRED_PACKAGES.python += library/python/icecream
TEST_REQUIRED_PACKAGES.python += library/python/invocations
TEST_REQUIRED_PACKAGES.python += library/python/mypy
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-relaxed
TEST_REQUIRED_PACKAGES.python += library/python/releases
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/types-pyyaml
