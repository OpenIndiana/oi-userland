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
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		qunit
COMPONENT_VERSION=	1.23.1
COMPONENT_PROJECT_URL=	http://qunitjs.com/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:38f0f23e8441e1e2da6d4e90a10b85304eb52002d570e7016015d05718d4a3d5
COMPONENT_ARCHIVE_URL=	https://github.com/jquery/qunit/archive/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB= 	javascript/qunit

TPNO= 	27977

include ../../../make-rules/prep.mk
include ../../../make-rules/ips.mk

# common targets
publish: download prep

# To run the test, you'll need to get pre-built installer of node.js for
# Solaris at nodejs.org since node.js is not delivered as part of Solaris
# yet. 
# Then go to qunit's source code root, such as 'qunit-1.23.1',
# run `npm install -g grunt-cli` to have a global grunt binary,
# and run `npm install` to get required node modules for additional grunt tasks.
# Finally run `grunt` to start running all the test tasks.
# However, phantomjs is not supported well in Solaris and there is not an intuitive
# patch for fixing it, therefore `npm install` fails when it tries to install
# phantomjs, and the test taks can't be run.
# The phantomjs issue is discussed at:
#
# 	https://github.com/ariya/phantomjs/issues/10521
#
# These test tasks are passed successfully in a Mac OSX laptop. It'd be fine
# to use QUnit in the browser.
test:		$(NO_TESTS)

system-test:    $(NO_TESTS)
