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
#   $WS_TOOLS/python-integrate-project -d python/gi-docgen gi_docgen
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		gi_docgen
HUMAN_VERSION =			2026.1
COMPONENT_SUMMARY =		Documentation tool for GObject-based libraries
COMPONENT_PROJECT_URL =		https://gitlab.gnome.org/GNOME/gi-docgen
COMPONENT_ARCHIVE_HASH =	\
	sha256:65ac3c4f2b4255d1c616fb8eae55139b6ca10071545ca2272759ffd2ccf2c7b5
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSES/Apache-2.0.txt

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

# Rename pkg-config file(s) to contain version number
COMPONENT_POST_INSTALL_ACTION += \
	for f in $(PROTOPKGCONFIGSHAREDIR)/*.pc ; do \
		[[ -f $$f ]] || continue ; \
		for v in $(PYTHON_VERSIONS) ; do \
			[[ "$$f" == "$${f%%$$v.pc}" ]] || continue 2 ; \
		done ; \
		$(MV) $$f $${f%%.pc}-$(PYTHON_VERSION).pc ; \
	done ;

# Replace Python version in man page file paths
GENERATE_EXTRA_SED += -e 's|\(usr/share/man/man.*-\)3\.[0-9]\{1,\}\(\.[0-9]\)|\1$$(PYVER)\2|'

# Replace Python version in pkg-config file paths
GENERATE_EXTRA_SED += -e 's|\(usr/share/pkgconfig/.*-\)3\.[0-9]\{1,\}\.pc|\1$$(PYVER).pc|'

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/jinja2
REQUIRED_PACKAGES.python += library/python/markdown
REQUIRED_PACKAGES.python += library/python/markupsafe
REQUIRED_PACKAGES.python += library/python/packaging
REQUIRED_PACKAGES.python += library/python/pygments
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/tomli
REQUIRED_PACKAGES.python += library/python/typogrify
REQUIRED_PACKAGES.python += runtime/python
