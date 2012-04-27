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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

# The archive untars to directory without the '-2' suffix, so
# COMPONENT_SUBVERSION had to be introduced
#
COMPONENT_NAME=			ImageMagick
COMPONENT_VERSION=		6.3.4
COMPONENT_SUBVERSION=	2
HUMAN_VERSION=			$(COMPONENT_VERSION)-$(COMPONENT_SUBVERSION)
COMPONENT_PROJECT_URL=		http://www.imagemagick.org/
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC)-$(COMPONENT_SUBVERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:25fb373ac3889e81555e5b48c8a22a3deabeac8b6129387cec9dc7e13804914e
COMPONENT_ARCHIVE_URL=	http://image_magick.veidrodis.com/image_magick/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATH=$(SPRO_VROOT)/bin:/usr/bin:/usr/gnu/bin

# IPS_COMPONENT_VERSION is by default set to $(COMPONENT_VERSION) but in
# this case we need to replace the '-' by '.'.
#
IPS_COMPONENT_VERSION=	$(COMPONENT_VERSION).$(COMPONENT_SUBVERSION)

# The archive contains pre-generated magick-config.h header, which is later on
# being used and the build fails.  However, we want to use the header generated
# by configure from BUILD_DIR_32 / BUILD_DIR_64 directory, so the pre-generated
# header file needs to be deleted.
#
COMPONENT_PREP_ACTION= (cd $(@D) ; $(RM) magick/magick-config.h)

# To get the Perl modules built it is necessary to copy the PerlMagick directory
# to the build directory
#
COMPONENT_PRE_CONFIGURE_ACTION= ($(CP) -R $(SOURCE_DIR)/PerlMagick $(@D); cd $(SOURCE_DIR); $(AUTORECONF) -f)

# Show name of "error tag" as part of the warning
#
CFLAGS+= -errtags

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
CONFIGURE_OPTIONS+= --x-libraries=$(CONFIGURE_LIBDIR.$(BITS)) 
CONFIGURE_OPTIONS.32+= --with-perl=$(PERL)
CONFIGURE_OPTIONS.32+= --with-perl-options="INSTALLDIRS=vendor"
CONFIGURE_OPTIONS.64+= --without-perl

# common targets
#
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

# ImageMagick tests have hard-coded absolute paths inside, so essentially they
# can be run only after ImageMagick is actually installed and this is not 
# possible, so the tests are not invoked.
#
test:		$(NO_TESTS)
	@echo "Tests can be run only after ImageMagick is installed."

BUILD_PKG_DEPENDENCIES= $(BUILD_TOOLS)

include ../../make-rules/depend.mk
