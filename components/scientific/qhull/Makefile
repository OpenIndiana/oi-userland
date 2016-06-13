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
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		qhull
COMPONENT_VERSION=	7.2.0
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://www.qhull.org/
COMPONENT_SUMMARY=	General dimension convex hull programs
COMPONENT_DESCRIPTION=	Qhull is a general dimension convex hull program that reads a set of points from stdin, and outputs the smallest convex set that contains the points to stdout.  It also generates Delaunay triangulations, Voronoi diagrams, furthest-site Voronoi diagrams, and halfspace intersections about a point.
COMPONENT_FMRI=         library/qhull
COMPONENT_CLASSIFICATION=       System/Libraries
COMPONENT_SRC=		$(COMPONENT_NAME)-2015.2
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-2015-src-$(COMPONENT_VERSION).tgz
COMPONENT_ARCHIVE_HASH=	sha256:78b010925c3b577adc3d58278787d7df08f7c8fb02c3490e375eab91bb58a436
COMPONENT_ARCHIVE_URL=	http://www.qhull.org/download/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	Qhull
COMPONENT_LICENSE_FILE=	COPYING.txt

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk

CMAKE_OPTIONS+=	-DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS+= -DINCLUDE_INSTALL_DIR:PATH=$(CMAKE_INCLUDEDIR)
CMAKE_OPTIONS+= -DBIN_INSTALL_DIR:PATH=$(CMAKE_BINDIR.$(BITS))
CMAKE_OPTIONS+= -DLIB_INSTALL_DIR:PATH=$(CMAKE_LIBDIR.$(BITS))
CMAKE_OPTIONS+= -DCMAKE_SKIP_RPATH=1

COMPONENT_TEST_TARGETS=	test

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
