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
# Copyright (c) 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME         = gamin
COMPONENT_VERSION      = 0.1.10
COMPONENT_PROJECT_URL  = http://www.gnome.org/~veillard/gamin/
COMPONENT_SRC          = $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE      = $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH = \
    sha256:28085f0ae8be10eab582ff186af4fb0be92cc6c62b5cc19cd09b295c7c2899a1
COMPONENT_ARCHIVE_URL  = https://people.gnome.org/~veillard/gamin/sources/gamin-0.1.10.tar.gz
COMPONENT_BUGDB        = library/gamin

TPNO                   = 9483

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_ENABLE)

COMPONENT_PREP_ACTION = (cd $(@D) ; autoreconf -if; bzip2 NEWS; bzip2 ChangeLog; bzip2 COPYING)

# The tests can leave a socket behind, which makes the tests fail next time
COMPONENT_PRE_TEST_ACTION += rm -f /tmp/fam-$$LOGNAME/fam-test

# The test suite sets permission on the temp dir to 000 and 'gmake clean' is
# not able to remove it afterwards
PRE_CLEAN_ACTION = chmod 777 $(BUILD_DIR)/*/python/tests/temp_dir &> /dev/null || :

# Remove times from the test output
COMPONENT_TEST_TRANSFORMS += '-e "s/^\(--- result\.[0-9][0-9]*\).*/\1/" '

# Since the tests don't pass, remove mostly all output of the tests
COMPONENT_TEST_TRANSFORMS += '-e "/^ /d"'
COMPONENT_TEST_TRANSFORMS += '-e "/^Error/d"'
COMPONENT_TEST_TRANSFORMS += '-e "/^error/d"'
COMPONENT_TEST_TRANSFORMS += '-e "/^Traceback/d"'
COMPONENT_TEST_TRANSFORMS += '-e "/^IndexError/d"'
COMPONENT_TEST_TRANSFORMS += '-e "/^Got callback/d"'
COMPONENT_TEST_TRANSFORMS += '-e "/^No differences encountered/d"'
COMPONENT_TEST_TRANSFORMS += '-e "/^+/d"'
COMPONENT_TEST_TRANSFORMS += '-e "/^\-/d"'
COMPONENT_TEST_TRANSFORMS += '-e "/^\*/d"'
COMPONENT_TEST_TRANSFORMS += '-e "/^!/d"'

configure:	$(CONFIGURE_32)

build:          $(BUILD_32)

install:        $(INSTALL_32)

test:           $(TEST_32)

REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library
