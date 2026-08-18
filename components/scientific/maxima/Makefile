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
# Copyright 2024 Andreas Wacknitz
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	maxima
COMPONENT_VERSION= 	5.50.0
COMPONENT_REVISION=	1
COMPONENT_SUMMARY= 	Maxima is a descendant of Macsyma, the legendary computer algebra system
COMPONENT_PROJECT_URL=	https://maxima.sourceforge.io
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://sourceforge.net/projects/maxima/files/Maxima-source/$(COMPONENT_VERSION)-source/$(COMPONENT_ARCHIVE)/download
COMPONENT_ARCHIVE_HASH= sha256:0bc4b5e11fe153ef20b24a3a816b668ece5378cc738fa24ca426b62fd6d8fc37
COMPONENT_FMRI=			library/math/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Development/Other Languages
COMPONENT_LICENSE=		GPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_BUILD_ENV += LC_ALL=en_US.UTF-8
COMPONENT_BUILD_ENV += MAXIMA_VERSION=$(COMPONENT_VERSION)
COMPONENT_TEST_ENV += LC_ALL=en_US.UTF-8

COMPONENT_PREP_ACTION= ( cd $(@D) && aclocal && autoconf )

COMPONENT_PRE_CONFIGURE_ACTION= ( $(CLONEY) $(SOURCE_DIR) $(@D) )

CONFIGURE_OPTIONS += --enable-sbcl-exec
CONFIGURE_OPTIONS += --enable-quiet-build

# Remove info/dir
COMPONENT_POST_INSTALL_ACTION += $(RM) $(PROTOUSRSHAREDIR)/info/dir ;

# Note that the detailed test results are
# No unexpected errors found out of 20,589 tests.
COMPONENT_TEST_ENV += maxima_tempdir=/tmp

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += image/gnuplot
REQUIRED_PACKAGES += runtime/sbcl
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
