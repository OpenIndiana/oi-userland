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
#   $WS_TOOLS/python-integrate-project PyGObject
#

BUILD_STYLE = pyproject
# Force setup.py build style to get the pkgconfig file installed
# see also: https://pygobject.readthedocs.io/en/latest/packagingguide.html
BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		PyGObject
HUMAN_VERSION =			3.46.0
COMPONENT_SUMMARY =		PyGObject - Python bindings for GObject Introspection
COMPONENT_PROJECT_URL =		https://pygobject.readthedocs.io
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/ac/4a/f24ddf1d20cc4b56affc7921e29928559a06c922eb60077448392792b914/PyGObject-3.46.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:481437b05af0a66b7c366ea052710eb3aacbb979d22d30b797f7ec29347ab1e6
COMPONENT_LICENSE =		LGPL-2.1-only
COMPONENT_LICENSE_FILE =	COPYING

# Manifest options for library/python/pygobject-3-39 package
COMPONENT_FMRI.PyGObject-3-39 =		library/python/pygobject-3-39

# Force setup.py test style because the automatically detected pytest test
# style does not work properly.
TEST_STYLE = setup.py

# We cannot obsolete pygobject-27 yet because it is needed by gimp and pygtk2-27.
PYTHON_VERSIONS_OBSOLETING := $(filter-out 2.7, $(PYTHON_VERSIONS_OBSOLETING))

include $(WS_MAKE_RULES)/common.mk

# Make sure the data files are installed at proper location
PYTHON_DATA = $(USRDIR)

# Rename some files to make way for symlinks
COMPONENT_POST_INSTALL_ACTION += \
	(cd $(PROTOUSRINCDIR)/pygobject-3.0; $(MV) pygobject.h pygobject.h-$(PYTHON_VERSION)) ;
COMPONENT_POST_INSTALL_ACTION += \
	(cd $(PROTOUSRLIBDIR)/pkgconfig; $(MKDIR) ../$(MACH64)/pkgconfig; $(MV) pygobject-3.0.pc ../$(MACH64)/pkgconfig/pygobject-3.0.pc-$(PYTHON_VERSION)) ;

# Replace Python version in header and pkgconfig file names
GENERATE_EXTRA_CMD += | \
	$(GSED) -E -e 's/(pygobject((\.h)|(-3\.0\.pc))-)3\.[0-9]*$$/\1$$(PYVER)/' | uniq

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/pycairo
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += system/library
