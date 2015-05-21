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
# Copyright (c) 2012, 2015, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		libdnet
COMPONENT_VERSION=	1.12
COMPONENT_PROJECT_URL=	http://code.google.com/p/libdnet/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	\
    sha256:83b33039787cf99990e977cef7f18a5d5e7aaffc4505548a83d31bd3515eb026
COMPONENT_ARCHIVE_URL=	http://libdnet.googlecode.com/files/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/libdnet 

TPNO=			9402

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Needed to generate libraries with a .so extension.
COMPONENT_PREP_ACTION = \
	(cd $(@D) ; libtoolize --automake --copy ; \
		aclocal -I config ; \
		autoheader ; \
		automake --add-missing --copy ; \
		autoconf)

# Set -m32 or -m64 correctly for 32 and 64 bit versions.
CC +=	$(CC_BITS)

# Remove Linux specific functionality.
CONFIGURE_OPTIONS += ac_cv_dnet_linux_pf_packet=no

CONFIGURE_OPTIONS +=	--with-check=/usr

# Needed for "gmake test" to work successfully.
# If SHELLOPTS is exported (as it is by the userland makefiles),
# then all shell options get exported to child invocations of bash,
# which results in test failures due to nounset and xtrace being
# set unexpectedly, and errors such as "$1: unbound variable" and
# diffs failing due to script tracing in output files.
unexport SHELLOPTS

COMPONENT_TEST_DIR =	$(@D)/test/check

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

ASLR_MODE = $(ASLR_ENABLE)

configure:	$(CONFIGURE_32_and_64)

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)

REQUIRED_PACKAGES += developer/test/check
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
