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
#   $WS_TOOLS/python-integrate-project mutagen
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		mutagen
HUMAN_VERSION =			1.47.0
COMPONENT_SUMMARY =		mutagen - read and write audio tags for many formats
COMPONENT_PROJECT_URL =		https://github.com/quodlibet/mutagen
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/81/e6/64bc71b74eef4b68e61eb921dcf72dabd9e4ec4af1e11891bbd312ccbb77/mutagen-1.47.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:719fadef0a978c31b4cf3c956261b3c58b6948b32023078a2117b1de09f0fc99
COMPONENT_LICENSE =		GPL-2.0-only
COMPONENT_LICENSE_FILE =	COPYING

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

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
GENERATE_EXTRA_CMD += | \
	$(GSED) -e 's|\(usr/share/man/man.*-\)3\.[0-9]\{1,\}\(\.[0-9]\)|\1$$(PYVER)\2|' | uniq

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
