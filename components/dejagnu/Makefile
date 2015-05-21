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
# Copyright (c) 2013, 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		dejagnu
COMPONENT_VERSION=	1.5.3
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/dejagnu/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:099b8e364ca1d6248f8e1d32168c4b12677abff4253bbbb4a8ac8cdd321e3f19
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/dejagnu

TPNO=			22219

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_TEST_ENV +=	PATH="$(GNUBIN):$(PATH)"

# The additional dejagnu specific set of transforms to be applied to the
# test results to try to normalize them.
COMPONENT_TEST_TRANSFORMS += \
	'-e "s|^.*$(CXX).*$$|XXX_CXX_XXX|g" ' \
	'-e "/^XXX_CXX_XXX$$/d" ' \
	'-e "s|\(Test Run By\).*|\1|" ' \
	'-e "s|\(Native configuration is\).*|\1|" '

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# common targets
configure:	$(CONFIGURE_64)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)

REQUIRED_PACKAGES += shell/expect
REQUIRED_PACKAGES += shell/ksh93

