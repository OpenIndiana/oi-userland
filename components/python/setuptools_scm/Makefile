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
#   $WS_TOOLS/python-integrate-project setuptools_scm
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		setuptools_scm
COMPONENT_VERSION =		7.0.5
COMPONENT_REVISION =		4
COMPONENT_SUMMARY =		setuptools_scm - the blessed package to manage your versions by scm tags
COMPONENT_PROJECT_URL =		https://github.com/pypa/setuptools_scm/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/d0/43/f038b5009f93bcd77b1b8da9e6d424b739ab17aec9726f3a99eba23d53ca/setuptools_scm-7.0.5.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:031e13af771d6f892b941adb6ea04545bbf91ebc5ce68c78aaf3fff6e1fb4844
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - filelock (test bootstrap)
# - flit_scm (test bootstrap)
# - importlib_metadata
# - iniconfig (test bootstrap)
# - pluggy (test bootstrap)
# - py (test bootstrap)
# - pytest (test bootstrap)
# - tox (test bootstrap)
# - virtualenv (test bootstrap)
# - zipp
PYTHON_BOOTSTRAP = yes

# Step 3: keep versioned importlib-metadata in REQUIRED_PACKAGES
REQUIRED_PACKAGES_TRANSFORM += -e '/library\/python\/importlib-metadata/p'

include $(WS_MAKE_RULES)/common.mk

# The importlib-metadata is needed for Python 3.7 only. The generalized
# (unversioned) dependency on it create dependency loop because
# importlib_metadata needs setuptools_scm for building so setuptools_scm cannot
# require unversioned importlib_metadata.  Since our automatic dependency
# detection does not support (yet) per-version dependencies (all dependencies
# are always generalized) we need to break the loop using a workaround.
#
# Please note that we do not care about the the dependency loop for Python 3.7
# because we do not need to bootstrap Python 3.7 from scratch and Python 3.7
# should be EOLed in June 2023 anyway.
#
# Step 1: remove automatically detected dependency on importlib-metadata.
COMPONENT_POST_INSTALL_ACTION += $(GSED) -i -e '/^importlib-metadata$$/d' $(@D)/.depend-runtime ;
# Step 2: make sure setuptools-scm-37 depends on importlib-metadata-37
# (see setuptools_scm-PYVER.p5m)
#
# Step 3: (see above)
#
# Step 4: drop importlib-metadata from PYTHON_REQUIRED_PACKAGES
REQUIRED_PACKAGES_TRANSFORM += -e '/^PYTHON_.*library\/python\/importlib-metadata/d'

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/tomli
PYTHON_REQUIRED_PACKAGES += library/python/typing-extensions
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += library/python/importlib-metadata-37
