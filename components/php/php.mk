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

# Various macros/variables that are useful for building both PHP itself and
# PHP extensions using the PHP build system, in the Userland framework.

# PHP build system needs this to build 64-bit (and probably other things)
CONFIGURE_ENV += CFLAGS="$(CFLAGS)"

# make install requires this instead of DESTDIR
COMPONENT_INSTALL_ENV += INSTALL_ROOT=$(PROTO_DIR)

COMPONENT_TEST_TARGETS = test
# Do not prompt to send test results upstream
COMPONENT_TEST_ENV += TEST_PHP_ARGS="-q"

# Put everything under /usr/php/{version} (like 5.2-5.3 did)
CONFIGURE_PREFIX =      /usr/php/$(UL_PHP_MINOR_VERSION)
# Don't put $(MACH64) in paths
CONFIGURE_LIBDIR.64 =   $(CONFIGURE_PREFIX)/lib
CONFIGURE_BINDIR.64 =   $(CONFIGURE_PREFIX)/bin
CONFIGURE_SBINDIR.64 =  $(CONFIGURE_PREFIX)/sbin
CONFIGURE_INCLUDEDIR =  $(CONFIGURE_PREFIX)/include
CONFIGURE_MANDIR =	$(CONFIGURE_PREFIX)/share/man

COMPONENT_TEST_TRANSFORMS += \
	'-e "/libtool/d"' \
	'-e "/^TIME START/d"' \
	'-e "/^TIME END/d"' \
	'-e "/^Time taken/d"' \
	'-e "/^PHP         :/d"' \
	'-e "/^PHP_OS      :/d"' \
	'-e "/^PHP_VERSION :/d"' \
	'-e "/^ZEND_VERSION:/d"'
