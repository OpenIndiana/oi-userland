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
BUILD_ARCH= i386
BUILD_BITS= 32
COMPILER= gcc
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		gparted
COMPONENT_VERSION=	0.25.0
COMPONENT_PROJECT_URL=	http://gparted.org/
COMPONENT_ARCHIVE_HASH=	\
    sha256:2d996d5f4921d49eae850a1824acb8ab1299b1ea9bbb9c607248cd6c8cdc94ae
COMPONENT_ARCHIVE_URL=	http://prdownloads.sourceforge.net/gparted/$(COMPONENT_ARCHIVE)

TPNO=			27500

TEST_TARGET= $(NO_TESTS)

# Needs updated sigcpp, not available on S11.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_32=
INSTALL_32=
PUBLISH_STAMP=
endif

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION += (cd $(@D); autoreconf -fiv)

CXXFLAGS += -std=c++11

# needed to find xgettext
PATH=$(GNUBIN):$(USRBINDIR)

REQUIRED_PACKAGES += developer/gnome/gnome-doc-utils
REQUIRED_PACKAGES += library/c++/glibmm
REQUIRED_PACKAGES += library/c++/sigcpp
REQUIRED_PACKAGES += library/desktop/c++/atkmm
REQUIRED_PACKAGES += library/desktop/c++/cairomm
REQUIRED_PACKAGES += library/desktop/c++/gtkmm
REQUIRED_PACKAGES += library/desktop/c++/pangomm
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/perl-5/xml-parser
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library/c++-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/math
ifneq ($(MACH), sparc)
REQUIRED_PACKAGES += system/storage/parted
endif
