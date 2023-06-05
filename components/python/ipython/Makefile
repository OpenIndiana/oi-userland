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
HUMAN_VERSION =			8.14.0
COMPONENT_SUMMARY =		ipython - IPython: Productive Interactive Computing
COMPONENT_PROJECT_URL =		https://ipython.org
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/fa/cb/2b777f625cca49b4a747b0dfe9986c21f5b46e5b548176903a914cdbec55/ipython-8.14.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:1d197b907b6ba441b692c48cf2a3a2de280dc0ac91a3405b39349a50272ca0a1
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

# ipython >= 8.13.1 requires Python >= 3.9
PYTHON_VERSIONS := $(filter-out 3.7, $(PYTHON_VERSIONS))

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

# Testing fails with the checkdocs plugin installed
PYTEST_ADDOPTS += -p no:checkdocs
# Testing fails with the randomly plugin installed
PYTEST_ADDOPTS += -p no:randomly

# Random temporary file name
COMPONENT_TEST_TRANSFORMS += "-e 's|\(/tmp/tmp\).\{8\}\.py|\1XXXXXXXX.py|'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/backcall
PYTHON_REQUIRED_PACKAGES += library/python/decorator
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
