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
#   $WS_TOOLS/python-integrate-project typing_extensions
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		typing_extensions
HUMAN_VERSION =			4.8.0
COMPONENT_SUMMARY =		typing_extensions - Backported and Experimental Type Hints for Python 3.8+
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/1f/7a/8b94bb016069caa12fc9f587b28080ac33b4fbb8ca369b98bc0a4828543e/typing_extensions-4.8.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:df8e4339e9cb77357558cbdbceca33c303714cf861d1eef15e1070055ae8b7ef
COMPONENT_LICENSE =		PSF-2.0
COMPONENT_LICENSE_FILE =	LICENSE

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - importlib_metadata
# - platformdirs (test bootstrap)
# - setuptools_scm
# - tox (test bootstrap)
PYTHON_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/flit-core
PYTHON_REQUIRED_PACKAGES += runtime/python
