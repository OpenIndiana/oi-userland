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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mod_fcgid
COMPONENT_VERSION=	2.3.9
COMPONENT_PROJECT_URL=	http://httpd.apache.org/mod_fcgid/
COMPONENT_ARCHIVE_HASH=	\
    sha256:1cbad345e3376b5d7c8f9a62b471edd7fa892695b90b79502f326b4692a679cf
COMPONENT_ARCHIVE_URL=	http://archive.apache.org/dist/httpd/mod_fcgid/$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	13295

TPNO=			8878

BUILD_STYLE= justmake
include ../modules.mk

PATCH_LEVEL=0

COMPONENT_PRE_BUILD_ACTION= ( cd $(@D); APXS=$(APXS) ./configure.apxs )
