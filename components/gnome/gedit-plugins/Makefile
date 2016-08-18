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

BUILD_BITS =            64
# All components using gobject-introspection must be built with gcc as
# gobject-introspection does not produce correct results when using Studio.
COMPILER =              gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gedit-plugins
COMPONENT_VERSION=	3.18.0
COMPONENT_PROJECT_URL=  https://wiki.gnome.org/Apps/Gedit
COMPONENT_ARCHIVE_HASH=	\
    sha256:e25249c0c2a057827bb4d4755a2359e1f9b4de288e0c4e201c6ef4f0e0e8c580
COMPONENT_BUGDB=        gnome/applications

TPNO=			26843

TEST_TARGET = $(NO_TESTS)

# Needs gobject-introspection, not available on S11.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_64=
INSTALL_64=
PUBLISH_STAMP=
endif

include $(WS_MAKE_RULES)/gnome-component.mk

CONFIGURE_ENV += PATH="$(GNUBIN):$(PATH)"
COMPONENT_BUILD_ENV += PATH="$(GNUBIN):$(PATH)"

# Delete this when build servers are installed with an updated gedit
GEDIT_BASE = $(WS_COMPONENTS)/gnome/gedit/build/prototype/$(MACH)
PKG_CONFIG_PATHS += $(GEDIT_BASE)$(PKG_CONFIG_PATH.$(BITS))
LD_OPTIONS += -L$(GEDIT_BASE)$(USRLIB.$(BITS))
CPPFLAGS += -I$(GEDIT_BASE)/usr/include/gedit-3.14

# Temporary until dependencies are all on build machines
REQUIRED_PACKAGES += $(shell $(GSED) -n 's/REQUIRED_PACKAGES +=//p' ../gedit/Makefile)
#end Delete

REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/gtksourceview3
REQUIRED_PACKAGES += library/desktop/libpeas
REQUIRED_PACKAGES += library/glib2
