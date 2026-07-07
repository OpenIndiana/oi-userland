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
#   $WS_TOOLS/python-integrate-project -d python/mutagen-39 mutagen
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		mutagen
HUMAN_VERSION =			1.47.0
COMPONENT_REVISION =		2
COMPONENT_SUMMARY =		read and write audio tags for many formats
COMPONENT_PROJECT_URL =		https://mutagen.readthedocs.io
COMPONENT_ARCHIVE_HASH =	\
	sha256:719fadef0a978c31b4cf3c956261b3c58b6948b32023078a2117b1de09f0fc99
COMPONENT_LICENSE =		GPL-2.0-only
COMPONENT_LICENSE_FILE =	COPYING

TEST_STYLE = pytest

# mutagen >= 1.48.0 requires Python >= 3.10
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# This project uses poetry to manage test dependencies.
TEST_REQUIREMENTS_POETRY += dev

# Rename section 1 man page(s) to contain version number
COMPONENT_POST_INSTALL_ACTION += \
	for f in $(PROTOUSRSHAREMAN1DIR)/*.1 ; do \
		[[ -f $$f ]] || continue ; \
		for v in $(PYTHON_VERSIONS) ; do \
			[[ "$$f" == "$${f%%$$v.1}" ]] || continue 2 ; \
		done ; \
		$(MV) $$f $${f%%.1}-$(PYTHON_VERSION).1 ; \
	done ;

# Replace Python version in man page file paths
GENERATE_EXTRA_SED += -e 's|\(usr/share/man/man.*-\)3\.[0-9]\{1,\}\(\.[0-9]\)|\1$$(PYVER)\2|'

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/hypothesis
TEST_REQUIRED_PACKAGES.python += library/python/pytest
