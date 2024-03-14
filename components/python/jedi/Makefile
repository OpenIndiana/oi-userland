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
#   $WS_TOOLS/python-integrate-project jedi
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		jedi
HUMAN_VERSION =			0.19.1
COMPONENT_SUMMARY =		jedi - An autocompletion tool for Python that can be used for text editors.
COMPONENT_PROJECT_URL =		https://github.com/davidhalter/jedi
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/d6/99/99b493cec4bf43176b678de30f81ed003fd6a647a301b9c927280c600f0a/jedi-0.19.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:cf0496f3651bc65d7174ac1b7d043eff454892c708a87d1b683e57b569927ffd
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS_EXTRAS += testing

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/parso
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/attrs
TEST_REQUIRED_PACKAGES.python += library/python/colorama
TEST_REQUIRED_PACKAGES.python += library/python/django
TEST_REQUIRED_PACKAGES.python += library/python/docopt
TEST_REQUIRED_PACKAGES.python += library/python/pytest
