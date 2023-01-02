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
#   $WS_TOOLS/python-integrate-project nbformat
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		nbformat
HUMAN_VERSION =			5.7.2
COMPONENT_SUMMARY =		nbformat - The Jupyter Notebook format
COMPONENT_PROJECT_URL =		https://jupyter.org
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/dc/55/a5f62c430f1187b739f897fac0eea1cef62d805cf2a325e3587719cf3de5/nbformat-5.7.2.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:796469290e50e1bf9c19a55ca4fbe66319d99349e47ab94780247edde4bd7618
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	COPYING.md

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# The line number of reported warning depends on python version
COMPONENT_TEST_TRANSFORMS +=	"-e 's/:[0-9]\{1,\}\(: UserWarning: nbformat\.current is deprecated\.\)$$/:LINE\1/'"
# Order of detailed test results could change with every run
COMPONENT_TEST_TRANSFORMS +=	"-e '/^  /,/^$$/d'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/fastjsonschema
PYTHON_REQUIRED_PACKAGES += library/python/hatch-nodejs-version
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/jsonschema
PYTHON_REQUIRED_PACKAGES += library/python/jupyter-core
PYTHON_REQUIRED_PACKAGES += library/python/traitlets
PYTHON_REQUIRED_PACKAGES += runtime/python
