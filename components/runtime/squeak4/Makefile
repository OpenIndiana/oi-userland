#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2020 David Stes
#


#
# Package Makefile for the "Classic VM" Squeak Smalltalk V4 system
# See http://squeak.org and http://squeakvm.org
#
# The squeak4 vm can only run Squeak4 images; it will not work with 
# Squeak5 images; squeak5 uses  different technology called "Cog Spur"
#
# squeak4 uses cmake and a custom configure script (not GNU autoconf)
# in order to build this package, "cmake" must be installed
#

# squeak4 can be built both in 32-bit and 64-bit 
# but generally SqueakV4 images are 32bit
BUILD_BITS=32

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		squeak-4
COMPONENT_VERSION=	4.16.7
COMPONENT_SUMMARY=	The Squeak V4 Smalltalk Virtual Machine
COMPONENT_PROJECT_URL=	http://www.squeak.org
COMPONENT_ARCHIVE_URL=  http://squeakvm.org
COMPONENT_FMRI=		runtime/squeak-4
COMPONENT_CLASSIFICATION=	Development/Other Languages
SVN_REPO=		http://squeakvm.org/svn/squeak/trunk/
SVN_REV=		3775
SVN_HASH=  sha256:918f3576a148bc41ae10a929f3ac53dfa6984208604a9c28d4a712f58db55748

# See http://wiki.squeak.org/squeak/933
# See http://wiki.squeak.org/squeak/159
# there's 2 license lines in the manifest, the MIT squeak.license and this one
COMPONENT_LICENSE=      Squeak4
COMPONENT_LICENSE_FILE= squeak4.license

TEST_TARGET= $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

# squeak4 configure looks for .svn or svnversion file, but
# prep-svn.mk did a svn export and created an unversioned copy of the sources
COMPONENT_PRE_CONFIGURE_ACTION = \
( echo $(SVN_REV) > $(SOURCE_DIR)/platforms/unix/svnversion )

CONFIGURE_SCRIPT= $(SOURCE_DIR)/platforms/unix/cmake/configure
CONFIGURE_OPTIONS +=	--src=$(SOURCE_DIR)/src

# Makefile install/strip doesn't work
COMPONENT_POST_INSTALL_ACTION = \
( $(STRIP) $(PROTOUSRLIBDIR32)/squeak/$(COMPONENT_VERSION)-$(SVN_REV)/squeakvm )

REQUIRED_PACKAGES += x11/library/mesa
REQUIRED_PACKAGES += system/library/dbus

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/audio/gstreamer
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxrender
