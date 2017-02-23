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
# Copyright (c) 2015, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME         = libdaemon
COMPONENT_VERSION      = 0.14
COMPONENT_PROJECT_URL  = http://0pointer.de/lennart/projects/libdaemon/
COMPONENT_ARCHIVE_HASH = \
	 sha256:fd23eb5f6f986dcc7e708307355ba3289abe03cc381fc47a80bca4a50aa6b834
COMPONENT_ARCHIVE_URL  = http://0pointer.de/lennart/projects/libdaemon/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB        = library/daemon
COMPONENT_ANITYA_ID=	13299

TPNO                   = 9316

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = (cd $(@D) ; autoreconf -if)

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
