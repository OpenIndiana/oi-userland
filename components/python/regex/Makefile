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
#   $WS_TOOLS/python-integrate-project regex
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		regex
HUMAN_VERSION =			2023.5.4
COMPONENT_SUMMARY =		regex - Alternative regular expression module, to replace re.
COMPONENT_PROJECT_URL =		https://github.com/mrabarnett/mrab-regex
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/e4/e6/eac6b94eaf4081ccbe08aaff2e729f4c24b7ddaaffd023c0d8d9693ca8fc/regex-2023.5.4.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:9e1b4b0b4baff934ef3c0ac56578a6b773f7f90ad1db3ff843ee40d83bdae09f
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE.txt

# We need to force unittest test style because the pytest test style
# (automatically detected) fails.
# https://github.com/mrabarnett/mrab-regex/issues/416
TEST_STYLE = unittest

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += system/library
