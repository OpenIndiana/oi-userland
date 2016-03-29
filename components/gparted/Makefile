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
COMPONENT_VERSION=	0.25.0
COMPONENT_PROJECT_URL=	http://gparted.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:2d996d5f4921d49eae850a1824acb8ab1299b1ea9bbb9c607248cd6c8cdc94ae
COMPONENT_ARCHIVE_URL=	http://prdownloads.sourceforge.net/gparted/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/gparted

TPNO=			27500

# we're i386-only
ifeq ($(MACH), sparc)
PUBLISH_STAMP=
INSTALL_32=
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

REQUIRED_PACKAGES += developer/gnome/gnome-doc-utils
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
REQUIRED_PACKAGES += system/library/math
ifneq ($(MACH), sparc)
REQUIRED_PACKAGES += system/storage/parted
endif
