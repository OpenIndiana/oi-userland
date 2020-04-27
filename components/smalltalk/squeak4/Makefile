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
# Package Makefile for the "Classic VM" Squeak Smalltalk V4 system
# See http://squeak.org and http://squeakvm.org
#

# squeak4 uses cmake and a custom configure script (not GNU autoconf)
BUILD_STYLE=		configure

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		squeak4
COMPONENT_VERSION=	4.16.7
COMPONENT_SUMMARY=	The Squeak V4 Smalltalk System
COMPONENT_PROJECT_URL=	http://www.squeak.org
COMPONENT_FMRI=		runtime/squeak4
COMPONENT_CLASSIFICATION=	Development/Other Languages
SVN_REPO=		http://squeakvm.org/svn/squeak/trunk/
SVN_REV=		3775
SVN_HASH=  sha256:497a8cc645a75fc049f9467dab6fff2bd06726e09c39d1a4d1a42164f820a102
SQUEAK_REV = $(COMPONENT_VERSION)-$(SVN_REV)
SQUEAK_VERSION = squeak-$(SQUEAK_REV)
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	usr/share/doc/$(SQUEAK_VERSION)/LICENSE

include $(WS_MAKE_RULES)/common.mk

# for usr/lib/squeak we need the version and for usr/share/doc/squeak-version
PKG_OPTIONS += -D SQUEAK_REV="$(SQUEAK_REV)"
PKG_OPTIONS += -D SQUEAK_VERSION="$(SQUEAK_VERSION)"

PATH=$(PATH.gnu)

# squeak4 configure looks for .svn or svnversion file, but
# prep-svn.mk did a svn export and created an unversioned copy of the sources
COMPONENT_PRE_CONFIGURE_ACTION = ( echo $(SVN_REV) > $(SOURCE_DIR)/platforms/unix/svnversion)

CONFIGURE_SCRIPT= $(SOURCE_DIR)/platforms/unix/cmake/configure
CONFIGURE_OPTIONS +=	--src=$(SOURCE_DIR)/src

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += service/opengl/ogl-select
REQUIRED_PACKAGES += system/library/dbus
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/math 
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += x11/library/libx11 
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxrender
REQUIRED_PACKAGES += library/glib2 
REQUIRED_PACKAGES += library/libffi 
REQUIRED_PACKAGES += library/audio/gstreamer 
REQUIRED_PACKAGES += library/audio/pulseaudio 
REQUIRED_PACKAGES += library/desktop/pango 
REQUIRED_PACKAGES += library/desktop/cairo 

