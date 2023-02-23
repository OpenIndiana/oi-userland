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
#   $WS_TOOLS/python-integrate-project docutils
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		docutils
HUMAN_VERSION =			0.19
COMPONENT_SUMMARY =		docutils - Docutils -- Python Documentation Utilities
COMPONENT_PROJECT_URL =		https://docutils.sourceforge.io/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/6b/5c/330ea8d383eb2ce973df34d1239b3b21e91cd8c865d21ff82902d952f91f/docutils-0.19.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:33995a6753c30b7f577febfc2c50411fec6aac7f7ffeb7c4cfe5991072dcf9e6
COMPONENT_LICENSE =		CC-PDDC AND BSD-3-Clause AND BSD-2-Clause
COMPONENT_LICENSE_FILE =	COPYING.txt

include $(WS_MAKE_RULES)/common.mk

# Filter out lines with timestamps
COMPONENT_TEST_TRANSFORMS += "-e '/^Testing Docutils/d'"
COMPONENT_TEST_TRANSFORMS += "-e '/^OS:/d'"
COMPONENT_TEST_TRANSFORMS += "-e '/^Elapsed time:/d'"

# Sort list of tests
COMPONENT_TEST_TRANSFORMS += \
	" | ( \
		$(GSED) -u -e '/^Docutils package:/q' ; \
		$(GSED) -u -e '/^$$/Q' | LC_ALL=C $(GSORT) | $(NAWK) '{print}END{if(NR>0)printf(\"\\\\n\")}' ; \
		$(CAT) \
	) | $(COMPONENT_TEST_TRANSFORMER) -e ''"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/lxml
PYTHON_REQUIRED_PACKAGES += library/python/pygments
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
