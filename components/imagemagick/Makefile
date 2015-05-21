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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=			ImageMagick
COMPONENT_VERSION=		6.8.3
COMPONENT_SUBVERSION=		5
HUMAN_VERSION=			$(COMPONENT_VERSION)-$(COMPONENT_SUBVERSION)
COMPONENT_PROJECT_URL=		http://www.imagemagick.org/
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC)-$(COMPONENT_SUBVERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:daead80170bc6d44cf6a54b4817446cbb7211b8ee445532b64033af190265fe3
COMPONENT_ARCHIVE_URL=	http://image_magick.veidrodis.com/image_magick/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/imagemagick

TPNO=			17708

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(SPRO_VROOT)/bin:/usr/bin:/usr/gnu/bin

# IPS_COMPONENT_VERSION is by default set to $(COMPONENT_VERSION) but in
# this case we need to replace the '-' by '.'.
IPS_COMPONENT_VERSION=	$(COMPONENT_VERSION).$(COMPONENT_SUBVERSION)

COMPONENT_POST_UNPACK_ACTION= ( $(MV) $(COMPONENT_SRC)-$(COMPONENT_SUBVERSION) \
    $(COMPONENT_SRC))

# To get the Perl modules built it is necessary to copy the PerlMagick directory
# to the build directory
COMPONENT_PRE_CONFIGURE_ACTION= ($(CP) -R $(SOURCE_DIR)/PerlMagick $(@D))

# Show name of "error tag" as part of the warning
CFLAGS += -errtags=yes
# To remove the compiler complaints about __restrict keyword,
# -D_magickcore_restrict should be used.
CFLAGS += -xc99=%all -D_magickcore_restrict=

# Needed to generate a decent RUNPATH for Magick.so
#
COMPONENT_BUILD_ARGS += LD="$(CC)"
COMPONENT_BUILD_ARGS += LD_RUN_PATH="$(CONFIGURE_LIBDIR.$(BITS))"

CONFIGURE_OPTIONS+= CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS+= CXXFLAGS="$(CXXFLAGS)"
CONFIGURE_OPTIONS+= --with-modules
CONFIGURE_OPTIONS+= --enable-shared=yes
CONFIGURE_OPTIONS+= --enable-static=no
CONFIGURE_OPTIONS+= --without-gvc
CONFIGURE_OPTIONS+= --disable-openmp
# Using option 'with-fontconfig=no' so that the fonts/fonts path specified in
# configuration file 'type-ghostscript.xml' is being used.
CONFIGURE_OPTIONS+= --with-fontconfig=no
# Configure option 'with-gs-font-dir' is required because some build systems
# might not have ghostscript fonts installed.
CONFIGURE_OPTIONS+= --with-gs-font-dir="/usr/share/ghostscript/fonts"
CONFIGURE_OPTIONS+= --x-libraries=$(CONFIGURE_LIBDIR.$(BITS)) 
CONFIGURE_OPTIONS.32+= --with-perl=$(PERL)
CONFIGURE_OPTIONS.32+= --with-perl-options="INSTALLDIRS=vendor"
CONFIGURE_OPTIONS.64+= --without-perl

# Needed for "gmake test" to work successfully.  If SHELLOPTS is exported (as
# it is by the Userland Makefiles), then all shell options get exported to
# child invocations of bash, which results in test failures due to nounset and
# xtrace being set unexpectedly, and errors such as "$1: unbound variable" and
# diffs failing due to script tracing in output files.
unexport SHELLOPTS

# Tests hang waiting for input unless stdin is redirected.
COMPONENT_TEST_TARGETS = check < /dev/null

ASLR_MODE = $(ASLR_ENABLE)

configure:	$(CONFIGURE_32_and_64)

build:		$(BUILD_32_and_64)

# Remove build machine runpath from libMagick++-6.Q16.so.1.0.0 and
# libMagickCore-6.Q16.so.1.0.0
install:	$(INSTALL_32_and_64)
	/usr/bin/elfedit -e 'dyn:delete RUNPATH' \
	    $(PROTO_DIR)/usr/lib/libMagick++-6.Q16.so.1.0.0; \
	/usr/bin/elfedit -e 'dyn:delete RUNPATH' \
	    $(PROTO_DIR)/usr/lib/$(MACH64)/libMagick++-6.Q16.so.1.0.0; \
	/usr/bin/elfedit -e 'dyn:delete RPATH' \
	    $(PROTO_DIR)/usr/lib/libMagick++-6.Q16.so.1.0.0; \
	/usr/bin/elfedit -e 'dyn:delete RPATH' \
	    $(PROTO_DIR)/usr/lib/$(MACH64)/libMagick++-6.Q16.so.1.0.0
	/usr/bin/elfedit -e 'dyn:delete RUNPATH' \
	    $(PROTO_DIR)/usr/lib/libMagickCore-6.Q16.so.1.0.0; \
	/usr/bin/elfedit -e 'dyn:delete RUNPATH' \
	    $(PROTO_DIR)/usr/lib/$(MACH64)/libMagickCore-6.Q16.so.1.0.0; \
	/usr/bin/elfedit -e 'dyn:delete RPATH' \
	    $(PROTO_DIR)/usr/lib/libMagickCore-6.Q16.so.1.0.0; \
	/usr/bin/elfedit -e 'dyn:delete RPATH' \
	    $(PROTO_DIR)/usr/lib/$(MACH64)/libMagickCore-6.Q16.so.1.0.0

test:		$(TEST_32_and_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)

REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += image/library/libjpeg
REQUIRED_PACKAGES += image/library/libpng
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/fftw-3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/lcms
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/c++-runtime
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/openmp
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
