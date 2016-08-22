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
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME =        lcms2
COMPONENT_VERSION=      2.7
COMPONENT_PROJECT_URL=  http://www.littlecms.com/
COMPONENT_ARCHIVE_HASH= \
    sha256:4524234ae7de185e6b6da5d31d6875085b2198bc63b1211f7dde6e2d197d6a53
COMPONENT_ARCHIVE_URL=  http://sourceforge.net/projects/lcms/files/lcms/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/lcms

TPNO=			25712

include $(WS_MAKE_RULES)/common.mk

# In order to run the tests, we need to use cloney
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

# Seems that we have no other way to designate that we want large file support.
CFLAGS += $(CPP_LARGEFILES)

# Need to ensure lcms custom chunk memory allocator aligns properly for all
# of our platforms - see _cmsALIGNMEM macro in src/lcms2_internal.h and
# _MAX_ALIGNMENT definition in per-platform sections of <sys/isa_defs.h>
CPPFLAGS += -DCMS_PTR_ALIGNMENT=_MAX_ALIGNMENT

CONFIGURE_OPTIONS +=	--includedir=$(USRINCDIR)/lcms
CONFIGURE_OPTIONS +=	--enable-shared
CONFIGURE_OPTIONS +=	--disable-static
CONFIGURE_OPTIONS +=	--with-jpeg
CONFIGURE_OPTIONS +=	--with-tiff
CONFIGURE_OPTIONS +=	--with-zlib
CONFIGURE_OPTIONS +=	--with-pic

COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(SOURCE_DIR)/utils/linkicc/linkicc.1 $(PROTOUSRSHAREMAN1DIR) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(SOURCE_DIR)/utils/psicc/psicc.1 $(PROTOUSRSHAREMAN1DIR) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP) $(SOURCE_DIR)/utils/transicc/transicc.1 $(PROTOUSRSHAREMAN1DIR) ;

# Needed to get past trying to copy identical files because the top_srcdir
# is not the same as the top_builddir.
COMPONENT_TEST_ARGS =	-k -i
COMPONENT_TEST_DIR =	$(@D)/testbed
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += \
	'-e "s|^.*test bed.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^.*MPixel.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^.*Single block hit.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^.*$(CC).*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^.*source=.*libtool=no.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^.*DEPDIR=.deps.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^make.*: Leaving directory.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^make.*: Entering directory.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "/^XXX_REMOVE_XXX$$/d" '

REQUIRED_PACKAGES += image/library/libjpeg
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += system/library/math
