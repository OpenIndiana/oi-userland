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
#   $WS_TOOLS/python-integrate-project Pillow
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Pillow
HUMAN_VERSION =			10.0.0
COMPONENT_SUMMARY =		Pillow - Python Imaging Library (Fork)
COMPONENT_PROJECT_URL =		https://python-pillow.org
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/0f/8b/2ebaf9adcf4260c00f842154865f8730cf745906aa5dd499141fb6063e26/Pillow-10.0.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:9c82b5b3e043c7af0d95792d0d20ccf68f61a1fec6b3530e718b688422727396
COMPONENT_LICENSE =		HPND
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# build with the distribution preferred libjpeg implementation
CFLAGS   += $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS += $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS  += $(JPEG_LDFLAGS)

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += image/library/openjpeg
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += library/libwebp
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += x11/library/libxcb
TEST_REQUIRED_PACKAGES.python += library/python/cffi
TEST_REQUIRED_PACKAGES.python += library/python/check-manifest
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/defusedxml
TEST_REQUIRED_PACKAGES.python += library/python/markdown2
TEST_REQUIRED_PACKAGES.python += library/python/numpy
TEST_REQUIRED_PACKAGES.python += library/python/olefile
TEST_REQUIRED_PACKAGES.python += library/python/packaging
TEST_REQUIRED_PACKAGES.python += library/python/pyroma
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-timeout
