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

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		gparted
COMPONENT_VERSION=	0.4.5
COMPONENT_PROJECT_URL=	http://gparted.sourceforge.net/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:a0a102ee51c1d70fa1c786c77a613111179ce81efccb637bd04aef525199b93f
COMPONENT_ARCHIVE_URL=	http://prdownloads.sourceforge.net/gparted/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/gparted

TPNO=			7497

# we're i386-only
ifeq ($(MACH), sparc)
PUBLISH_STAMP=
endif

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION += (cd $(@D); autoreconf -fiv)

CC += $(CC_BITS)
CXX += $(CC_BITS)

# needed to find xgettext
PATH=/usr/gnu/bin:/usr/bin
CONFIGURE_OPTIONS +=    CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS +=	CXX="$(CXX) -norunpath"

ASLR_MODE =	$(ASLR_ENABLE)

# common targets, we're i386-only

build_sparc:
	@echo "Not available."

configure:	$(CONFIGURE_32)

build_i386:	$(BUILD_32)

build:		build_$(MACH)

install:	$(INSTALL_32) 

test:           $(NO_TESTS)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)

REQUIRED_PACKAGES += library/c++/glibmm
REQUIRED_PACKAGES += library/c++/sigcpp
REQUIRED_PACKAGES += library/desktop/c++/cairomm
REQUIRED_PACKAGES += library/desktop/c++/gtkmm
REQUIRED_PACKAGES += library/desktop/c++/pangomm
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/c++-runtime
REQUIRED_PACKAGES += system/storage/parted
