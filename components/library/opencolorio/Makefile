#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2022 Daniel Chan
#

BUILD_STYLE= cmake
USE_PARALLEL_BUILD = yes
USE_DEFAULT_TEST_TRANSFORMS = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		OpenColorIO
COMPONENT_VERSION=	2.4.1
COMPONENT_SUMMARY=	A color management framework for visual effects and animation
COMPONENT_PROJECT_URL=	https://github.com/AcademySoftwareFoundation/$(COMPONENT_NAME)
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:d4eb15408b33dffd6ba0bba9a53328085b40bdd9319fa3d0d7348d06a8cbe842
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=		library/opencolorio
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=	BSD-3-Clause
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Make pkglint happy by avoiding default paths in rpath
CMAKE_OPTIONS += -DCMAKE_SKIP_RPATH=TRUE

# Make sure testing finds built libOpenColorIO
COMPONENT_TEST_ENV += LD_LIBRARY_PATH=$(BUILD_DIR_$(BITS))/src/OpenColorIO

# Manually added optional build dependencies
PYTHON_REQUIRED_PACKAGES += library/python/pybind11

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/imath
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += library/minizip-ng
REQUIRED_PACKAGES += library/openexr
REQUIRED_PACKAGES += library/pystring
REQUIRED_PACKAGES += library/yaml-cpp-8
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
