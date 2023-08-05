#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2023, Andreas Wacknitz
#

BUILD_BITS= 64
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			ImageMagick
COMPONENT_VERSION=		7.1.1
COMPONENT_SUBVERSION=		15
HUMAN_VERSION=			$(COMPONENT_VERSION)-$(COMPONENT_SUBVERSION)
IPS_COMPONENT_VERSION=	$(COMPONENT_VERSION).$(COMPONENT_SUBVERSION)
COMPONENT_SUMMARY=		ImageMagick - Image Manipulation Utilities and Libraries
COMPONENT_PROJECT_URL=	https://legacy.imagemagick.org
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)-$(COMPONENT_SUBVERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_NAME)-$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:2372192a76af9be43c0543dd7ae6dfbf34b11fc0203583453ce3f9f707c36bcc
COMPONENT_ARCHIVE_URL=	https://github.com/ImageMagick/ImageMagick/archive/$(HUMAN_VERSION).tar.gz
COMPONENT_FMRI=			image/imagemagick
COMPONENT_CLASSIFICATION=	System/Multimedia Libraries
COMPONENT_LICENSE= Apache 2.0 license
COMPONENT_LICENSE_FILE= LICENSE

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = ( cd $(@D) && libtoolize -f && autoreconf -fi )

# To get the Perl modules built it is necessary to copy the PerlMagick directory
# to the build directory
#
COMPONENT_PRE_CONFIGURE_ACTION= ( $(CP) -R $(SOURCE_DIR)/PerlMagick $(@D) )

# Don't use rpath, or relink!
COMPONENT_POST_CONFIGURE_ACTION = \
	(cd $(BUILD_DIR_$(BITS)) ; \
	$(GSED) -i \
	-e 's|^hardcode_libdir_flag_spec=.*|hardcode_libdir_flag_spec=""|g' \
	-e 's|need_relink=yes|need_relink=not_on_solaris|' \
	libtool)

LIBS += -lsocket -lnsl
CONFIGURE_ENV += LIBS="$(LIBS)"

# build with the distribution preferred libjpeg implementation
CFLAGS   += $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS += $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS  += $(JPEG_LDFLAGS)

CONFIGURE_OPTIONS += --with-modules
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static
# Using option 'with-fontconfig=no' so that the fonts/fonts path specified in
# configuration file 'type-ghostscript.xml' is being used.
#CONFIGURE_OPTIONS+= --with-fontconfig=no
# Configure option 'with-gs-font-dir' is required because some build systems might 
# not have ghostscript fonts installed.
CONFIGURE_OPTIONS += --with-gs-font-dir="/usr/share/ghostscript/fonts"
CONFIGURE_OPTIONS += --x-libraries=$(CONFIGURE_LIBDIR.$(BITS)) 
CONFIGURE_OPTIONS += --with-perl=$(PERL)
CONFIGURE_OPTIONS += --with-perl-options="INSTALLDIRS=vendor"
CONFIGURE_OPTIONS += --sysconfdir=/etc

# As of version 7.1.0-34, a "Linux-compatible sendfile()" is detected;
# override thiis.
CONFIGURE_OPTIONS += ac_cv_have_linux_sendfile=no

# Needed for "gmake test" to work successfully.  If SHELLOPTS is exported (as
# it is by the Userland Makefiles), then all shell options get exported to
# child invocations of bash, which results in test failures due to nounset and
# xtrace being set unexpectedly, and errors such as "$1: unbound variable" and
# diffs failing due to script tracing in output files.
unexport SHELLOPTS

# Tests hang waiting for input unless stdin is redirected.
COMPONENT_TEST_TARGETS = check < /dev/null

# PKGVERS is needed for manifest processing
PKG_MACROS += PERLVER=$(PERL_VERSION)

# Build dependencies
REQUIRED_PACKAGES += print/filter/ghostscript/fonts/gnu-gs-fonts-std

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += image/djvulibre
REQUIRED_PACKAGES += image/graphviz
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libraw
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += image/library/openjpeg
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/libwebp
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libzip
REQUIRED_PACKAGES += library/openexr
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
