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
# Copyright 2019 Michal Nowak
#

BUILD_BITS= 32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         cairo
COMPONENT_VERSION=      1.16.0
COMPONENT_REVISION=     4
COMPONENT_SUMMARY=      Vector graphics library
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:5e7b29b3f113ef870d1e3ecf8adf21f923396401604bda16d44be45e66052331
COMPONENT_ARCHIVE_URL=  https://cairographics.org/releases/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  https://cairographics.org/
COMPONENT_FMRI=         library/desktop/cairo
COMPONENT_CLASSIFICATION=Desktop (GNOME)/Libraries
COMPONENT_LICENSE=      LGPLv2.1
COMPONENT_LICENSE_FILE= COPYING-LGPL-2.1

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION =	( cd $(@D) && PATH=$(PATH) libtoolize --force --copy && \
                                      aclocal  -I build && \
                                      gtkdocize &&\
                                      autoheader &&\
                                      automake -a -f -c --gnu &&\
                                      autoconf )

COMPONENT_PRE_CONFIGURE_ACTION = ( cp -a $(SOURCE_DIR)/* $(@D))

CONFIGURE_SCRIPT = $(@D)/configure

CFLAGS += -D_POSIX_PTHREAD_SEMANTICS

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-xcb-shm=no
CONFIGURE_OPTIONS += --enable-gl=yes
CONFIGURE_OPTIONS += --enable-xlib-xcb
CONFIGURE_OPTIONS += --enable-xml
CONFIGURE_OPTIONS += --enable-test-surfaces

# Needed for "gmake test" to work successfully.
# If SHELLOPTS is exported (as it is by the userland makefiles),
# then all shell options get exported to child invocations of bash,
# which results in test failures due to nounset and xtrace being
# set unexpectedly, and errors such as "$1: unbound variable" and
# diffs failing due to script tracing in output files.
unexport SHELLOPTS

# Auto-generated dependencies
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/graphics/pixman
REQUIRED_PACKAGES += library/lzo
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcb
