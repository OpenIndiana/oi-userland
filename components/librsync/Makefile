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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		librsync
COMPONENT_VERSION=	0.9.7
COMPONENT_PROJECT_URL=	http://librsync.sourceforge.net/
COMPONENT_ARCHIVE_HASH=	\
    sha256:6633e4605662763a03bb6388529cbdfd3b11a9ec55b8845351c1bd9a92bc41d6
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/$(COMPONENT_NAME)/files/librsync/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_BUGDB=	library/librsync

# librsync documentation as originally found at:
# http://librsync.sourcefrog.net/doc/librsync.html
# http://librsync.sourcefrog.net/doc/librsync.pdf
# The files there are not in an easily downloadable format so a local
# archive has been created for them.
COMPONENT_NAME_1=	librsync-docs
COMPONENT_SRC_1=	$(COMPONENT_NAME_1)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_1=	$(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_HASH_1=	\
    sha256:e805819272f71b06823ee13f2dd7ddb92e75d75de18c33b7fd32133847c52afe
COMPONENT_ARCHIVE_URL_1=	$(EXTERNAL_ARCHIVE_MIRROR)/$(COMPONENT_ARCHIVE_1)
COMPONENT_POST_UNPACK_ACTION_1 = $(MV) $(COMPONENT_NAME_1) $(@D)

TPNO=			9087

CLEAN_PATHS += $(COMPONENT_NAME_1)

TEST_TARGET= install $(TEST_32_and_64)
SYSTEM_TEST_TARGET= build $(SYSTEM_TEST_32_and_64)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D)) ; \
	tar -xvf $(COMPONENT_ARCHIVE_1)

CFLAGS += -features=no%extinl

CONFIGURE_OPTIONS  +=	--enable-shared

PROTOUSRSHAREDOCDIR = $(PROTOUSRSHAREDIR)/doc/librsync-0.9.7

# Get correct librsync.so.1 from the proto area.
TEST_LIBPATH.32 =		$(PROTOUSRLIBDIR)
TEST_LIBPATH.64 =		$(PROTOUSRLIBDIR64)
COMPONENT_TEST_ENV +=		LD_LIBRARY_PATH=$(TEST_LIBPATH.$(BITS))

COMPONENT_TEST_DIR =		$(@D)/testsuite
COMPONENT_SYSTEM_TEST_DIR =	$(@D)/testsuite

# Master test results are the same for 32-bit and 64-bit, so override
# here, rather than create multiple identical master files.
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

# The additional librsync specific set of transforms to be applied to the
# test results to try to normalize them.
COMPONENT_TEST_TRANSFORMS += \
	'-e "/Entering directory/d"' \
	'-e "/Leaving directory/d"' \
	'-e "/check-TESTS/d"' \
	'-e "/depmode/d"' \
	'-e "/isprefix.driver/d"' \
	'-e "/^mkdir/d"' \
	'-e "/^make/d"' \
	'-e "s|^.*$(CC).*$$|XXX_CC_XXX|g" ' \
	'-e "s|^.*source=.*libtool=no.*$$|XXX_CC_XXX|g" ' \
	'-e "/^XXX_CC_XXX$$/d" '

COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) -p $(PROTOUSRSHAREDOCDIR) ; \
	$(CP) librsync-docs/librsync.pdf $(PROTOUSRSHAREDOCDIR) ; \
	$(CP) -r librsync-docs/html $(PROTOUSRSHAREDOCDIR)

REQUIRED_PACKAGES += library/popt
