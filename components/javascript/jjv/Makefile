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
# Copyright (c) 2016, 2017, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		jjv
COMPONENT_VERSION=	1.0.2
COMPONENT_PROJECT_URL=	https://github.com/acornejo/jjv/archive
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:130b9a2a09c2525f9ccecdf52e3d855901f2eaf6712edc7eedaad3824f65654d
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB= 	javascript/jjv
COMPONENT_ANITYA_ID=	13253

TPNO= 	21110

include ../../../make-rules/prep.mk
include ../../../make-rules/ips.mk

# common targets
publish: download prep

# To run the test files, you'll need to install node.js and npm, and then go to
# to the root of the source code, 'jjv-1.0.2', and run the following commands:
# $ npm install chai
# $ npm install mocha
# $ ./node_modules/mocha/bin/mocha
test:		$(NO_TESTS)

system-test:    $(NO_TESTS)
