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
HUMAN_VERSION =			1.1.8
COMPONENT_SUMMARY =		sphinxcontrib_serializinghtml - sphinxcontrib-serializinghtml is a sphinx extension which outputs \\\\\\\"serialized\\\\\\\" HTML files (json and pickle)
COMPONENT_PROJECT_URL =		https://www.sphinx-doc.org/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/a0/a3/4bd9d8c5c97312bf46b059bcf76eab42ce6ffb12560b7ce9a247e2e524a3/sphinxcontrib_serializinghtml-1.1.8.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:aaf3026335146e688fd209b72320314b1b278320cf232e3cda198f873838511a
COMPONENT_LICENSE =		BSD-2-Clause
COMPONENT_LICENSE_FILE =	LICENSE

# sphinxcontrib-serializinghtml needs sphinx to run tests, but sphinx needs
# sphinxcontrib-serializinghtml to build itself.  This is special case when we
# need to set PYTHON_TEST_BOOTSTRAP to make sure the
# sphinxcontrib-serializinghtml tests are not run when there is no sphinx
# available yet.
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/flit-core
PYTHON_REQUIRED_PACKAGES += library/python/sphinx
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
