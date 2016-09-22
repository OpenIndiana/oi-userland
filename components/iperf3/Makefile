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
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		iperf
COMPONENT_VERSION=	3.1.3
COMPONENT_PROJECT_URL=	https://iperf.fr/
COMPONENT_ARCHIVE_HASH=	\
    sha256:60d8db69b1d74a64d78566c2317c373a85fef691b8d277737ee5d29f448595bf
COMPONENT_ARCHIVE_URL=	http://downloads.es.net/pub/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/iperf

TPNO=			31583

# There is no easy way to do automated testing that produce consistent
# results independent of what machine there are run on, but the following
# can be done manually.
#
# In one terminal window, start the iperf3 server with:
#
# $ cd .../components/iperf3/build/[amd64,sparcv9]/src
# $ ./iperf3 -s
#
# In another terminal window, start the script to test various commands with:
#
# $ cd .../components/iperf3/build/[amd64,sparcv9]/
# $ ./test_commands.sh localhost
#
TEST_TARGET= $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# Needed to successfully run the test_commands.sh script in a built workspace.
COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

REQUIRED_PACKAGES += system/library/math
