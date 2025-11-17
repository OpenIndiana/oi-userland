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
#   $WS_TOOLS/python-integrate-project natsort
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		natsort
HUMAN_VERSION =			8.4.0
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Simple yet flexible natural sorting in Python.
COMPONENT_PROJECT_URL =		https://github.com/SethMMorton/natsort
COMPONENT_ARCHIVE_HASH =	\
	sha256:45312c4a0e5507593da193dedd04abb1469253b601ecaf63445ad80f0a1ea581
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# There are three sets of test results (pytest is run three times by tox) so we
# need to sort the 2nd one and the 3rd one too (the first one is sorted in
# setup.py.mk).
COMPONENT_TEST_TRANSFORMS += \
	"| ( \
		$(GSED) -u -e '/^=\{1,\} test session starts /q' ; \
		$(GSED) -u -e '/^=\{1,\} test session starts /q' ; \
		$(GSED) -u -e '/^$$/q' ; \
		$(GSED) -u -e 's/ *\[...%\]$$//' -e '/^$$/Q' | $(SORT) | $(GSED) -e '\$$a\'\$$'\\\n\\\n' ; \
		$(GSED) -u -e '/^=\{1,\} test session starts /q' ; \
		$(GSED) -u -e '/^$$/q' ; \
		$(GSED) -u -e 's/ *\[...%\]$$//' -e '/^$$/Q' | $(SORT) | $(GSED) -e '\$$a\'\$$'\\\n\\\n' ; \
		$(CAT) \
	) | $(COMPONENT_TEST_TRANSFORMER) -e ''"

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/hypothesis
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
