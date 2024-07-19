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
#   $WS_TOOLS/python-integrate-project sphinx
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		sphinx
HUMAN_VERSION =			7.4.6
COMPONENT_SUMMARY =		Python documentation generator
COMPONENT_PROJECT_URL =		https://www.sphinx-doc.org/
COMPONENT_ARCHIVE_HASH =	\
	sha256:116918d455c493fff3178edea12b4fe1c1e4894680fd81e7b7431ea21d47ca52
COMPONENT_LICENSE =		BSD-2-Clause AND BSD-3-Clause AND MIT
COMPONENT_LICENSE_FILE =	LICENSE.rst

include $(WS_MAKE_RULES)/common.mk

# varies between test runs
COMPONENT_TEST_TRANSFORMS += "-e '/^base tmp_path:/d'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/alabaster
PYTHON_REQUIRED_PACKAGES += library/python/babel
PYTHON_REQUIRED_PACKAGES += library/python/docutils
PYTHON_REQUIRED_PACKAGES += library/python/flit-core
PYTHON_REQUIRED_PACKAGES += library/python/imagesize
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/jinja2
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/pygments
PYTHON_REQUIRED_PACKAGES += library/python/requests
PYTHON_REQUIRED_PACKAGES += library/python/snowballstemmer
PYTHON_REQUIRED_PACKAGES += library/python/sphinxcontrib-applehelp
PYTHON_REQUIRED_PACKAGES += library/python/sphinxcontrib-devhelp
PYTHON_REQUIRED_PACKAGES += library/python/sphinxcontrib-htmlhelp
PYTHON_REQUIRED_PACKAGES += library/python/sphinxcontrib-jsmath
PYTHON_REQUIRED_PACKAGES += library/python/sphinxcontrib-qthelp
PYTHON_REQUIRED_PACKAGES += library/python/sphinxcontrib-serializinghtml
PYTHON_REQUIRED_PACKAGES += library/python/tomli
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/cython
TEST_REQUIRED_PACKAGES.python += library/python/defusedxml
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/typing-extensions
