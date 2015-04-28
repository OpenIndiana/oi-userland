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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		aalib
COMPONENT_VERSION=	1.4.0
HUMAN_VERSION=		1.4rc5
IPS_COMPONENT_VERSION =	1.4.5
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://aa-project.sourceforge.net/aalib/
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:fbddda9230cf6ee2a4f5706b4b11e2190ae45f5eda1f0409dc4f99b35e0a70ee
COMPONENT_ARCHIVE_URL=	http://downloads.sourceforge.net/aa-project/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/aalib

TPNO=			6118

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk
include $(WS_MAKE_RULES)/lint-libraries.mk

LINT_FLAGS += -I$(SOURCE_DIR)/src

PKG_PROTO_DIRS +=	$(COMPONENT_SRC)

# We need to reset configure options here because aalib is confused with
# CC and CFLAGS definitions as configure parameters.
CONFIGURE_OPTIONS	= --prefix=/usr
CONFIGURE_OPTIONS	+= --infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS	+= --mandir=$(CONFIGURE_MANDIR)
CONFIGURE_OPTIONS	+= --bindir=$(CONFIGURE_BINDIR.$(BITS))
CONFIGURE_OPTIONS	+= --libdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS	+= --enable-shared
CONFIGURE_OPTIONS	+= --disable-static
CONFIGURE_OPTIONS	+= --x-includes=/usr/include
CONFIGURE_OPTIONS	+= --x-libraries=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS	+= $(CONFIGURE_OPTIONS.$(BITS))

CONFIGURE_ENV += CC="$(CC)"
CONFIGURE_ENV += CFLAGS="$(CFLAGS)"

COMPONENT_TEST_DIR =	$(@D)/src
COMPONENT_TEST_CMD =	perl -E 'say "\n" x 40' | ./aatest
COMPONENT_TEST_ARGS =	-kbddriver stdin -driver stdout
COMPONENT_TEST_TARGETS =

COMPONENT_SYSTEM_TEST_DIR =	$(SOURCE_DIR)/src
COMPONENT_SYSTEM_TEST_CMD =	perl -E 'say "\n" x 40' | /usr/demo/aalib/aatest
COMPONENT_SYSTEM_TEST_ARGS =	-kbddriver stdin -driver stdout
COMPONENT_SYSTEM_TEST_TARGETS =

# Master test results are the same for both 32-bit and 64-bit, so override
# here, rather than create multiple identical master files.
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

ASLR_MODE = $(ASLR_ENABLE)

# common targets
configure:	$(CONFIGURE_32_and_64)

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)
system-test:	$(SYSTEM_TEST_32_and_64)


REQUIRED_PACKAGES += library/slang
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
