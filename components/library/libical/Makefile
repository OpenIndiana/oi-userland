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
# Copyright 2016 Alexander Pyhalov
#

BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libical
COMPONENT_VERSION=	3.0.16
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	libical is an Open Source implementation of the IETF's iCalendar Calendaring and Scheduling protocols
COMPONENT_PROJECT_URL=	https://libical.github.io/libical
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/libical/libical/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:b44705dd71ca4538c86fb16248483ab4b48978524fb1da5097bd76aa2e0f0c33
COMPONENT_FMRI=		library/libical
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE=	LICENSE.LGPL21.txt

include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS += -DBUILD_SHARED_LIBS=On
CMAKE_OPTIONS += -DICAL_ERRORS_ARE_FATAL=false
CMAKE_OPTIONS += -DLIB_SUFFIX=/$(MACH64)
CMAKE_OPTIONS += -DGOBJECT_INTROSPECTION=true
# Always use our own timezone data.
CMAKE_OPTIONS += -DUSE_BUILTIN_TZDATA=false
CMAKE_OPTIONS += -DICAL_GLIB=true
CMAKE_OPTIONS += -DICAL_GLIB_VAPI=true

COMPONENT_TEST_CMD = ctest
COMPONENT_TEST_TARGETS =
COMPONENT_TEST_TRANSFORMS = \
	' -e "s/[0-9]*\.[0-9]* sec//" ' \
	' -n ' \
	' -e "/Passed/p" ' \
	' -e "/passed/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += database/berkeleydb-5
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
