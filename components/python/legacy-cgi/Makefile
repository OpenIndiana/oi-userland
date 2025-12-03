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
#   $WS_TOOLS/python-integrate-project -d python/legacy-cgi legacy_cgi
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		legacy_cgi
HUMAN_VERSION =			2.6.4
COMPONENT_SUMMARY =		Fork of the standard library cgi and cgitb modules removed in Python 3.13
COMPONENT_ARCHIVE_HASH =	\
	sha256:abb9dfc7835772f7c9317977c63253fd22a7484b5c9bbcdca60a29dcce97c577
COMPONENT_LICENSE =		PSF-2.0
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

# legacy-cgi is needed for Python >= 3.13 only
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/hatchling
REQUIRED_PACKAGES.python += runtime/python
