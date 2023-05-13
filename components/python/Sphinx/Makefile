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
#   $WS_TOOLS/python-integrate-project Sphinx
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Sphinx
HUMAN_VERSION =			7.0.1
COMPONENT_SUMMARY =		Sphinx - Python documentation generator
COMPONENT_PROJECT_URL =		https://www.sphinx-doc.org/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/61/b6/b2ca621fba7f1d938d75891fe175ba8054b47e803d11727d3e9f4433d86c/Sphinx-7.0.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:61e025f788c5977d9412587e733733a289e2b9fdc2fef8868ddfbfc4ccfe881d
COMPONENT_LICENSE =		BSD-2-Clause AND BSD-3-Clause AND MIT
COMPONENT_LICENSE_FILE =	LICENSE

# Sphinx >= 6.0.0 requires Python >= 3.8
PYTHON_VERSIONS := $(filter-out 3.7, $(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

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
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/cython
TEST_REQUIRED_PACKAGES.python += library/python/filelock
TEST_REQUIRED_PACKAGES.python += library/python/html5lib
TEST_REQUIRED_PACKAGES.python += library/python/pytest
