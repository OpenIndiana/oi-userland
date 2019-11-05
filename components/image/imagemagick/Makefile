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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			ImageMagick
COMPONENT_VERSION=		6.9.9
COMPONENT_REVISION=		3
COMPONENT_MAJOR_VERSIOR=	$(shell echo $(COMPONENT_VERSION) | $(GSED) -e 's/\([0-9]\+\)\.[0-9]\+\.[0-9]\+/\1/')
COMPONENT_SUBVERSION=		21
HUMAN_VERSION=			$(COMPONENT_VERSION)-$(COMPONENT_SUBVERSION)
COMPONENT_FMRI=			image/imagemagick
COMPONENT_CLASSIFICATION=	System/Multimedia Libraries
COMPONENT_SUMMARY=		ImageMagick - Image Manipulation Utilities and Libraries
COMPONENT_PROJECT_URL=		http://www.imagemagick.org/
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC)-$(COMPONENT_SUBVERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:e8fdd8329c103b1f16654738ba517d46866b6c54ead43e001c04e83531faaab7						
COMPONENT_ARCHIVE_URL=		https://github.com/ImageMagick/ImageMagick/archive/$(COMPONENT_VERSION)-$(COMPONENT_SUBVERSION).tar.gz
COMPONENT_LICENSE = Apache 2.0 license
COMPONENT_LICENSE_FILE = LICENSE

CONFIGURE_FIX_LIBTOOL_RPATH=no

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION = (cd $(@D) && libtoolize -f && autoreconf -fi)

# IPS_COMPONENT_VERSION is by default set to $(COMPONENT_VERSION) but in
# this case we need to replace the '-' by '.'.
#
IPS_COMPONENT_VERSION=	$(COMPONENT_VERSION).$(COMPONENT_SUBVERSION)

COMPONENT_POST_UNPACK_ACTION= ( $(MV) $(COMPONENT_SRC)-$(COMPONENT_SUBVERSION) \
    $(COMPONENT_SRC))

# To get the Perl modules built it is necessary to copy the PerlMagick directory
# to the build directory
#
COMPONENT_PRE_CONFIGURE_ACTION= ($(CP) -R $(SOURCE_DIR)/PerlMagick $(@D))

# Don't use rpath, or relink!
COMPONENT_POST_CONFIGURE_ACTION = \
	(cd $(BUILD_DIR_$(BITS)) ; \
	$(GSED) -i \
	-e 's|^hardcode_libdir_flag_spec=.*|hardcode_libdir_flag_spec=""|g' \
	-e 's|need_relink=yes|need_relink=not_on_solaris|' \
	libtool)

LIBS += -lsocket -lnsl
CONFIGURE_ENV += LIBS="$(LIBS)"

# Prevent older versions of libMagick{Core,Wand}-6.Q16.so from the build
# machine from being found ahead of new versions from the proto area.
LD_OPTIONS_SO=		-L. -L../../magick/.libs
COMPONENT_BUILD_ENV +=	LD_OPTIONS_SO="$(LD_OPTIONS_SO)"

# build with the distribution preferred libjpeg implementation
CFLAGS   += $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS += $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS  += $(JPEG_LDFLAGS)

CONFIGURE_OPTIONS+= --with-modules
CONFIGURE_OPTIONS+= --enable-shared
CONFIGURE_OPTIONS+= --disable-static
CONFIGURE_OPTIONS+= --without-gvc
CONFIGURE_OPTIONS+= --disable-openmp
# Using option 'with-fontconfig=no' so that the fonts/fonts path specified in
# configuration file 'type-ghostscript.xml' is being used.
CONFIGURE_OPTIONS+= --with-fontconfig=no
# Configure option 'with-gs-font-dir' is required because some build systems might 
# not have ghostscript fonts installed.
CONFIGURE_OPTIONS+= --with-gs-font-dir="/usr/share/ghostscript/fonts"
CONFIGURE_OPTIONS+= --x-libraries=$(CONFIGURE_LIBDIR.$(BITS)) 
CONFIGURE_OPTIONS.32+= --with-perl=$(PERL)
CONFIGURE_OPTIONS.32+= --with-perl-options="INSTALLDIRS=vendor"
CONFIGURE_OPTIONS.64+= --without-perl
CONFIGURE_OPTIONS+= --sysconfdir=/etc

# common targets
#
build:		$(BUILD_32_and_64)

# Doing it twice because /usr/lib is deep...
# Remove build machine runpath from libMagick++-6.Q16.so.1.0.0
install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

PKG_MACROS += COMPONENT_MAJOR_VERSION=$(COMPONENT_MAJOR_VERSION)
PKG_MACROS += COMPONENT_SUBVERSION=$(COMPONENT_SUBVERSION)
PKG_MACROS += PERL_PKG=$(PERL_PKG)


# Needed for "gmake test" to work successfully.  If SHELLOPTS is exported (as
# it is by the Userland Makefiles), then all shell options get exported to
# child invocations of bash, which results in test failures due to nounset and
# xtrace being set unexpectedly, and errors such as "$1: unbound variable" and
# diffs failing due to script tracing in output files.
unexport SHELLOPTS

# Tests hang waiting for input unless stdin is redirected.
COMPONENT_TEST_TARGETS = check < /dev/null

# Master test transforms
COMPONENT_TEST_TRANSFORMS += \
       '-n '\
       '-e "/TOTAL/p" ' \
       '-e "/SKIP/p" ' \
       '-e "/PASS/p" ' \
       '-e "/FAIL/p" ' \
       '-e "/ERROR/p" ' 

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

# Build dependencies
REQUIRED_PACKAGES += print/filter/ghostscript/fonts/gnu-gs-fonts-std

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += image/djvulibre
REQUIRED_PACKAGES += image/library/libjpeg8-turbo
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libraw
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += image/library/openjpeg
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/fftw-3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/libwebp
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/openexr
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
