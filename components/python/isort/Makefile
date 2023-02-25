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
#   $WS_TOOLS/python-integrate-project isort
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		isort
HUMAN_VERSION =			5.12.0
COMPONENT_SUMMARY =		isort - A Python utility / library to sort Python imports.
COMPONENT_PROJECT_URL =		https://pycqa.github.io/isort/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/a9/c4/dc00e42c158fc4dda2afebe57d2e948805c06d5169007f1724f0683010a9/isort-5.12.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:8bef7dde241278824a6d83f44a544709b065191b95b6e50894bdc722fcba0504
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

# isort >= 5.12.0 requires Python >= 3.8
PYTHON_VERSIONS := $(filter-out 3.7, $(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/poetry-core
PYTHON_REQUIRED_PACKAGES += runtime/python
