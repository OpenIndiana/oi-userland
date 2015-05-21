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
# Copyright (c) 2012, 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		findutils
COMPONENT_VERSION=	4.5.14
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/findutils/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:0de3cf625a5c9f154eee3171e072515ffdde405244dd00502af617ac57b73ae2
COMPONENT_ARCHIVE_URL=	http://alpha.gnu.org/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/gnu-findutils

TPNO=			19655

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_PREFIX =	/usr/gnu

CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"

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
	'-e "/^XXX_CC_XXX$$/d" ' \
	'-e "s|\(Test Run By\).*|\1|" ' \
	'-e "s|\(Native configuration is\).*|\1|" '

ASLR_MODE = $(ASLR_ENABLE)

# common targets
configure:	$(CONFIGURE_64)

build:          $(BUILD_64)

install:        $(INSTALL_64)

# Needed for "gmake test" to work successfully.
# Otherwise we see errors such as:
# FAIL: exec-nogaps.old-O3, sh: SHELLOPTS: readonly variable
unexport SHELLOPTS

test:           $(TEST_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)


REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
