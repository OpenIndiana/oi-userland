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
#   $WS_TOOLS/python-integrate-project wheel
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		wheel
COMPONENT_VERSION =		0.38.3
COMPONENT_SUMMARY =		wheel - A built-package format for Python
COMPONENT_PROJECT_URL =		https://github.com/pypa/wheel
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/2e/c6/af5def6796940a8bd602d815f7f495f32d833c81b38d055ca0b23ab3b804/wheel-0.38.3.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:4066646ef77d0e56cc44004c100381ee1957955cfc3151345dda96886f9896a5
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - packaging
PYTHON_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
