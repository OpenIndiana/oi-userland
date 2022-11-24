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
#   $WS_TOOLS/python-integrate-project sphinxcontrib-serializinghtml
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		sphinxcontrib-serializinghtml
COMPONENT_VERSION =		1.1.5
COMPONENT_SUMMARY =		sphinxcontrib-serializinghtml - sphinxcontrib-serializinghtml is a sphinx extension which outputs \\\\\\\"serialized\\\\\\\" HTML files (json and pickle).
COMPONENT_PROJECT_URL =		http://sphinx-doc.org/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/b5/72/835d6fadb9e5d02304cf39b18f93d227cd93abd3c41ebf58e6853eeb1455/sphinxcontrib-serializinghtml-1.1.5.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:aa5f6de5dfdf809ef505c4895e51ef5c9eac17d0f287933eb49ec495280b6952
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
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
