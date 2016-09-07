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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		eventlet
COMPONENT_VERSION=	0.18.4
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:74ef11d67ee5e85e009b0fced733c907620bca1ab8e6b0489d9f247405ab2685
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	http://eventlet.net/
COMPONENT_BUGDB=	python-mod/eventlet

TPNO=			28455

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

COMPONENT_TEST_DIR =	$(SOURCE_DIR)
COMPONENT_TEST_ARGS =	setup.py test

# Skipping this during automated tests since it hangs sometimes
$(SKIP_TEST_AT_TOP_LEVEL)

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:		$(TEST_NO_ARCH)

system-test:	$(SYSTEM_TESTS_NOT_IMPLEMENTED)
