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

BUILD_BITS =            32_and_64
# For now, all things built for C++11 require gcc.
COMPILER =              gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gtkmm
COMPONENT_VERSION=	2.24.4
COMPONENT_PROJECT_URL=	https://developer.gnome.org/gtkmm/stable/
COMPONENT_ARCHIVE_HASH= \
    sha256:443a2ff3fcb42a915609f1779000390c640a6d7fd19ad8816e6161053696f5ee
COMPONENT_BUGDB=	gnome/libraries

TPNO=			25780

TEST_TARGET = $(NO_TESTS)

# Needs updated gtk, not available on S11.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_32_and_64=
INSTALL_32_and_64=
PUBLISH_STAMP=
endif

include $(WS_MAKE_RULES)/gnome-component.mk

CXXFLAGS += -std=c++11

# Delete this when build servers are installed with atkmm
ATKMM_BASE = $(WS_COMPONENTS)/gnome/atkmm/build/prototype/$(MACH)
PKG_CONFIG_PATHS += $(ATKMM_BASE)$(PKG_CONFIG_PATH.$(BITS))

LD_OPTIONS += -L $(ATKMM_BASE)$(USRLIB.$(BITS))

CPPFLAGS += -I$(ATKMM_BASE)$(USRINCDIR)/atkmm-1.6

DEPENDED += $(WS_TOP)/components/gnome/atkmm/build/manifest-$(MACH)-atkmm.depend

REQUIRED_PACKAGES += $(shell $(GSED) -n -e 's%\$$(PERL_PKG)%$(PERL_PKG)%' -e 's/REQUIRED_PACKAGES +=//p' ../atkmm/Makefile)
#end Delete

REQUIRED_PACKAGES += developer/documentation-tool/doxygen
REQUIRED_PACKAGES += image/graphviz
REQUIRED_PACKAGES += library/c++/glibmm
REQUIRED_PACKAGES += library/c++/sigcpp
REQUIRED_PACKAGES += library/desktop/c++/atkmm
REQUIRED_PACKAGES += library/desktop/c++/cairomm
REQUIRED_PACKAGES += library/desktop/c++/pangomm
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/math
