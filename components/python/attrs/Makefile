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
#   $WS_TOOLS/python-integrate-project attrs
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		attrs
HUMAN_VERSION =			25.1.0
COMPONENT_SUMMARY =		Classes Without Boilerplate
COMPONENT_ARCHIVE_HASH =	\
	sha256:1c97078a80c814273a76b2a298a932eb681c87415c11dee0a6921de7f1b02c3e
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Filter out test loop dependency.  The loop is caused by complex project's
# test dependency hierarchy involving extras (see pyproject.toml).
REQUIRED_PACKAGES_TRANSFORM += \
	| $(GSED) -e '/^TEST_REQUIRED_PACKAGES\.python += library\/python\/attrs$$/d' \
	| $(COMPONENT_TEST_TRANSFORMER) -e ''

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/hatch-fancy-pypi-readme
PYTHON_REQUIRED_PACKAGES += library/python/hatch-vcs
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/cloudpickle
TEST_REQUIRED_PACKAGES.python += library/python/hypothesis
TEST_REQUIRED_PACKAGES.python += library/python/psutil
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
