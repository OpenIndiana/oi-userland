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
# Copyright (c) 2016 Sergey Avseyev
#

BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		qhull
COMPONENT_VERSION=	8.0.2
HUMAN_VERSION=		2020.2
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://www.qhull.org/
COMPONENT_SUMMARY=	General dimension convex hull programs
COMPONENT_DESCRIPTION=	Qhull is a general dimension convex hull program that reads a set of points from stdin, and outputs the smallest convex set that contains the points to stdout.  It also generates Delaunay triangulations, Voronoi diagrams, furthest-site Voronoi diagrams, and halfspace intersections about a point.
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-2020-src-$(COMPONENT_VERSION).tgz
COMPONENT_ARCHIVE_HASH=	sha256:b5c2d7eb833278881b952c8a52d20179eab87766b00b865000469a45c1838b7e
COMPONENT_ARCHIVE_URL=	http://www.qhull.org/download/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/qhull
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=	Qhull
COMPONENT_LICENSE_FILE=	COPYING.txt

include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS+=	-DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS+= -DINCLUDE_INSTALL_DIR:PATH=$(CMAKE_INCLUDEDIR)
CMAKE_OPTIONS+= -DBIN_INSTALL_DIR:PATH=$(CMAKE_BINDIR.$(BITS))
CMAKE_OPTIONS+= -DLIB_INSTALL_DIR:PATH=$(CMAKE_LIBDIR.$(BITS))
CMAKE_OPTIONS+= -DCMAKE_SKIP_RPATH=1

COMPONENT_TEST_TARGETS=	test
COMPONENT_TEST_ENV= LD_LIBRARY_PATH=$(PROTO_DIR)/usr/lib/$(MACH64) PATH=$(PATH):/usr/lib/$(MACH64)
COMPONENT_TEST_TRANSFORMS += '-e "s/[0-9]*\.[0-9]* sec//" '

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
