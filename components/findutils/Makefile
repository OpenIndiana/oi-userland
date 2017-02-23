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
# Copyright (c) 2012, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		findutils
COMPONENT_VERSION=	4.6.0
COMPONENT_ARCHIVE_HASH= \
    sha256:ded4c9f73731cd48fec3b6bdaccce896473b6d8e337e9612e16cf1431bb1169d
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/gnu-findutils
COMPONENT_ANITYA_ID=	812

TPNO=			27155

include $(WS_MAKE_RULES)/gnu-component.mk

CONFIGURE_PREFIX =	$(USRGNUDIR)

# Fixes coredump in the tests/test-localename test.
CONFIGURE_OPTIONS  +=	ac_cv_func_newlocale=no

# Disable the leaf optimisation feature, because the st_nlinks directory
# field is incorrect on ZFS file systems.
CONFIGURE_OPTIONS +=	--disable-leaf-optimisation

COMPONENT_TEST_ENV +=	PATH="$(GNUBIN):$(PATH)"

COMPONENT_TEST_TRANSFORMS += \
	'-e "s|^.*$(CC).*$$|XXX_CC_XXX|g" ' \
	'-e "s|^.*source=.*libtool=no.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^.*DEPDIR=.deps.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^.*(core dumped).*$$|XXX_CC_XXX|g" ' \
	'-e "/^XXX_CC_XXX$$/d" ' \
	'-e "s|\(Test Run By\).*|\1|" ' \
	'-e "s|\(Native configuration is\).*|\1|" '

# Needed for "gmake test" to work successfully.
# Otherwise we see errors such as:
# FAIL: exec-nogaps.old-O3, sh: SHELLOPTS: readonly variable
unexport SHELLOPTS


# test dependencies:
REQUIRED_PACKAGES += developer/versioning/cvs
REQUIRED_PACKAGES += developer/versioning/git

REQUIRED_PACKAGES += system/library/math
