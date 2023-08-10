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
#   $WS_TOOLS/python-integrate-project sphinxcontrib_serializinghtml
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		sphinxcontrib_serializinghtml
HUMAN_VERSION =			1.1.7
COMPONENT_SUMMARY =		sphinxcontrib_serializinghtml - sphinxcontrib-serializinghtml is a sphinx extension which outputs \\\\\\\"serialized\\\\\\\" HTML files (json and pickle)
COMPONENT_PROJECT_URL =		https://www.sphinx-doc.org/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/0d/1b/96acc54abc747faa2c9a64b05f12e043eee30de7933181a752cb458d1134/sphinxcontrib_serializinghtml-1.1.7.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:ca31afee32e1508cff4034e258060ce2c81a3b1c49e77da60fdb61f0e7a73c22
COMPONENT_LICENSE =		BSD-2-Clause
COMPONENT_LICENSE_FILE =	LICENSE

# sphinxcontrib-serializinghtml needs sphinx to run tests, but sphinx needs
# sphinxcontrib-serializinghtml to build itself.  This is special case when we
# need to set PYTHON_TEST_BOOTSTRAP to make sure the
# sphinxcontrib-serializinghtml tests are not run when there is no sphinx
# available yet.
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Disable some plugins to get tests passed
PYTEST_ADDOPTS += -p no:black
PYTEST_ADDOPTS += -p no:mypy

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/flit-core
PYTHON_REQUIRED_PACKAGES += library/python/sphinx
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
