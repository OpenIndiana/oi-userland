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
# Copyright (c) 2012, 2016, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2020, Andreas Wacknitz
#

BUILD_BITS=					32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=				popt
COMPONENT_VERSION=			1.19
COMPONENT_SUMMARY=			Command line parsing library
COMPONENT_PROJECT_URL=		https://github.com/rpm-software-management/popt
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=		sha256:c25a4838fc8e4c1c8aacb8bd620edb3084a3d63bf8987fdad3ca2758c63240f9
COMPONENT_ARCHIVE_URL=		https://fossies.org/linux/misc/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=				library/popt
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=			X Consortium

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

# Add /usr/gnu/bin at the front of $PATH for GNU gettext.
CONFIGURE_ENV +=	PATH=$(PATH.gnu)

CONFIGURE_OPTIONS +=	--disable-nls
CONFIGURE_OPTIONS +=	--enable-static=no

# Get correct libpopt.so.0 from the proto area.
TEST_LIBPATH.32 =       $(PROTOUSRLIBDIR)
TEST_LIBPATH.64 =       $(PROTOUSRLIBDIR64)
COMPONENT_TEST_ENV +=   LD_LIBRARY_PATH=$(TEST_LIBPATH.$(BITS))

COMPONENT_TEST_TRANSFORMS += \
    '-e "/Entering directory/d"' \
    '-e "/Leaving directory/d"' \
    '-e "/recursive/d"' \
    '-e "/check-local/d"' \
    '-e "/check-TESTS/d"' \
    '-e "/^Making/d"' \
    '-e "/^make/d"'

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
