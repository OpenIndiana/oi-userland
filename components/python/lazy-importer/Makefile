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
#   $WS_TOOLS/python-integrate-project -d python/lazy-importer lazy_importer
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		lazy_importer
HUMAN_VERSION =			0.1.0
COMPONENT_SUMMARY =		A context manager for portable, opt-in lazy imports
COMPONENT_ARCHIVE_HASH =	\
	sha256:b2e296716ce015c0cd80e57b940e52727c5b934b34b8656d5ce06bdd0ee5fbdd
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

# lazy-importer needs Python >= 3.11
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/flit-core
REQUIRED_PACKAGES.python += runtime/python
