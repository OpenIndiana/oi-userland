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
# Copyright (c) 2014, 2017, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2019, Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		text-utilities
COMPONENT_MAJOR_VERSION=2.33
COMPONENT_MINOR_VERSION=2
COMPONENT_VERSION=	$(COMPONENT_MAJOR_VERSION).$(COMPONENT_MINOR_VERSION)
COMPONENT_SUMMARY=	Various Linux utilities
COMPONENT_FMRI=		text/text-utilities
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_PROJECT_URL=	https://www.kernel.org/pub/linux/utils/util-linux
COMPONENT_SRC=		util-linux-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
	sha256:631be8eac6cf6230ba478de211941d526808dba3cd436380793334496013ce97
COMPONENT_ARCHIVE_URL=	https://mirrors.edge.kernel.org/pub/linux/utils/util-linux/v$(COMPONENT_MAJOR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE_FILE=	README.licensing
COMPONENT_LICENSE=	GPL-2.0-or-later, GPL-2.0, LGPL-2.1-or-later, BSD-3-Clause, BSD-4-Clause-UC, Public Domain

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# We currently only want some of the text-utils text utilities from this
# component, so enumerate it in a macro that we can use for build and install.
# Anything else that we want should be added to this macro in the future.
PROGRAMS =	colcrt colrm column hexdump rename

# Build a utility program used by one of the hexdump tests.
PROGRAMS +=	test_sysinfo

# We don't need the Python bindings built.
CONFIGURE_OPTIONS =	--prefix=/usr
CONFIGURE_OPTIONS +=	--bindir=$(CONFIGURE_BINDIR.32)
CONFIGURE_OPTIONS +=	--mandir=$(CONFIGURE_MANDIR)
CONFIGURE_OPTIONS +=	--without-python

# Always show the build and link lines for easier debugging.
COMPONENT_BUILD_ARGS +=		V=1

# Only build the programs that we want.
COMPONENT_BUILD_ARGS +=		bin_PROGRAMS="$(PROGRAMS)"
COMPONENT_BUILD_TARGETS =	$(PROGRAMS)

# Only install the bits we want.
COMPONENT_INSTALL_ARGS +=	bin_PROGRAMS="$(PROGRAMS)"
COMPONENT_INSTALL_TARGETS =	install-man install-binPROGRAMS

# Limit translations to the text utilities (and lib/* and include/* ) only.
COMPONENT_PRE_INSTALL_ACTION = \
	(cd $(@D)/po ; $(GMAKE) text-utilities.pot-update)

# Install the message files.
COMPONENT_POST_INSTALL_ACTION = \
	(cd $(@D)/po ; $(GMAKE) $(COMPONENT_INSTALL_ARGS) install ;\
	$(RM) -rf $(PROTOUSRLIBDIR64)/libsmartcols.so* ;\
	$(MKDIR) $(PROTOUSRLIBDIR64) ;\
	$(CP) -a $(@D)/.libs/libsmartcols.so* $(PROTOUSRLIBDIR64) ;\
	$(STRIP) $(PROTOUSRLIBDIR64)/libsmartcols.so.1.1.0 ; )

COMPONENT_TEST_ENV +=	TS_CMD_COLRM=$(PROTOUSRBINDIR)/colrm
COMPONENT_TEST_ENV +=	TS_CMD_COLCRT=$(PROTOUSRBINDIR)/colcrt
COMPONENT_TEST_ENV +=	TS_CMD_COLUMN=$(PROTOUSRBINDIR)/column
COMPONENT_TEST_ENV +=	TS_CMD_HEXDUMP=$(PROTOUSRBINDIR)/hexdump
COMPONENT_TEST_ENV +=   TS_CMD_RENAME=$(PROTOUSRBINDIR)/rename
COMPONENT_TEST_ENV +=	PATH="$(PATH.gnu)"
# Needed for the libsmartcols.so library
COMPONENT_TEST_ENV +=	LD_LIBRARY_PATH=$(PROTOUSRLIBDIR64)
COMPONENT_TEST_DIR =	$(COMPONENT_SRC)/tests

# The hexdump tests expect the test_sysinfo program in a different location
# than where it's built.
COMPONENT_PRE_TEST_ACTION = $(CP) $(@D)/test_sysinfo $(COMPONENT_SRC)/

COMPONENT_TEST_CMD =		./run.sh
COMPONENT_TEST_ARGS =		--verbose --show-diff
COMPONENT_TEST_TARGETS =	colrm colcrt column hexdump rename

# Remove date from diff
COMPONENT_TEST_TRANSFORMS += \
	'-e "s/ *20[12][0-9].*//"'

TEST_TARGET= install $(TEST_64)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library
