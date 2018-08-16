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
# Copyright (c) 2015, 2017, Oracle and/or its affiliates. All rights reserved.
#

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gucharmap
COMPONENT_MAJOR_MINOR=  3.18
COMPONENT_VERSION=	$(COMPONENT_MAJOR_MINOR).2
COMPONENT_SUMMARY=	Unicode character map for the GNOME project
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_PROJECT_URL=  https://wiki.gnome.org/Apps/
COMPONENT_ARCHIVE_URL= \
  https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPONENT_MAJOR_MINOR)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
	sha256:80141d3e892c3c4812c1a8fad8f89978559ef19e933843267e6e9a5524c09ec9
COMPONENT_FMRI = desktop/character-map/gucharmap
COMPONENT_CLASSIFICATION = Desktop (GNOME)/Documentation
COMPONENT_LICENSE = GPLv2
COMPONENT_LICENSE_FILE = COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

#COMPONENT_PREP_ACTION=  cd $(@D)  && NOCONFIGURE=1 ./autogen.sh

# Assumes xgettext in PATH.
CONFIGURE_ENV += PATH="$(GNUBIN):$(PATH)"
CONFIGURE_ENV += XGETTEXT=/usr/gnu/bin/xgettext

# gobject-introspection
COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
# need to use /usr/gnu/bin/msgfmt
COMPONENT_BUILD_ENV += PATH="$(GNUBIN):$(PATH)"

# configure generally requires GNU make explicitly.
#CONFIGURE_ENV += MAKE=$(MAKE)

CONFIGURE_ENV += INTLTOOL_PERL="$(PERL)"

COMPONENT_BUILD_ENV += GI_SCANNER_DISABLE_CACHE=""

CONFIGURE_OPTIONS += --libexecdir=/usr/lib
CONFIGURE_OPTIONS += --localstatedir=/var/lib
CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-Bsymbolic
# Required for other components.
CONFIGURE_OPTIONS += --enable-introspection
CONFIGURE_OPTIONS += --enable-shared
# Required for other components.
CONFIGURE_OPTIONS += --with-gtk=3.0

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test:           $(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES += library/c++/harfbuzz
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
