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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		expect
COMPONENT_VERSION=	5.45
COMPONENT_PROJECT_URL=	http://expect.nist.gov/
COMPONENT_SRC=		$(COMPONENT_NAME)$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:b28dca90428a3b30e650525cdc16255d76bb6ccd65d448be53e620d95d5cc040
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/expect/files/Expect/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download

include ../../../make-rules/prep.mk
include ../../../make-rules/configure.mk
include ../../../make-rules/ips.mk

SCRIPTS = timed-run timed-read ftp-rfc autopasswd lpunlock weather \
          passmass rftp kibitz rlogin-cwd xpstat tkpasswd dislocate xkibitz \
          tknewsbiff unbuffer mkpasswd cryptdir decryptdir autoexpect multixterm

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_PRE_BUILD_ACTION = \
	(cd $(@D); $(GMAKE) all ${SCRIPTS};)

CONFIGURE_OPTIONS 	+= CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS 	+= --with-tcl="$(COMPONENT_DIR)/../tcl/build/$(MACH32)"
CONFIGURE_OPTIONS 	+= --with-tclinclude="$(COMPONENT_DIR)/../tcl/build/$(MACH32)/generic"
CONFIGURE_OPTIONS 	+= --enable-shared

COMPONENT_TEST_TARGETS = test

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32) 
	
test: 		$(TEST_32)

# special targets due to tcl internals dependencies
../tcl/build/%/.built:
	(cd ../tcl ; $(GMAKE) build)

$(BUILD_32):    ../tcl/build/$(MACH32)/.built

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../../make-rules/depend.mk
