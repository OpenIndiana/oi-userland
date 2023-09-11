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
#   $WS_TOOLS/python-integrate-project ipython
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		ipython
HUMAN_VERSION =			8.15.0
COMPONENT_SUMMARY =		ipython - IPython: Productive Interactive Computing
COMPONENT_PROJECT_URL =		https://ipython.org
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/15/d0/b84b1131d7b958b2e4564f784c9a88b63ce7c181af914f0c26ac07970dc1/ipython-8.15.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:2baeb5be6949eeebf532150f81746f8333e2ccce02de1c7eedde3f23ed5e9f1e
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Rename section 1 man page(s) to contain version number
COMPONENT_POST_INSTALL_ACTION += \
	for f in $(PROTOUSRSHAREMAN1DIR)/*.1 ; do \
		[[ -f $$f ]] || continue ; \
		for v in $(PYTHON_VERSIONS) ; do \
			[[ "$$f" == "$${f%%$$v.1}" ]] || continue 2 ; \
		done ; \
		$(MV) $$f $${f%%.1}-$(PYTHON_VERSION).1 ; \
	done ;

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS_EXTRAS += test

# Random temporary file name
COMPONENT_TEST_TRANSFORMS += "-e 's|\(/tmp/tmp\).\{8\}\.py|\1XXXXXXXX.py|'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/backcall
PYTHON_REQUIRED_PACKAGES += library/python/decorator
PYTHON_REQUIRED_PACKAGES += library/python/exceptiongroup
PYTHON_REQUIRED_PACKAGES += library/python/jedi
PYTHON_REQUIRED_PACKAGES += library/python/matplotlib-inline
PYTHON_REQUIRED_PACKAGES += library/python/pexpect
PYTHON_REQUIRED_PACKAGES += library/python/pickleshare
PYTHON_REQUIRED_PACKAGES += library/python/prompt-toolkit
PYTHON_REQUIRED_PACKAGES += library/python/pygments
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/stack-data
PYTHON_REQUIRED_PACKAGES += library/python/traitlets
PYTHON_REQUIRED_PACKAGES += library/python/typing-extensions
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-asyncio
TEST_REQUIRED_PACKAGES.python += library/python/testpath
