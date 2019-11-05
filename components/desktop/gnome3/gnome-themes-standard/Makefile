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
# Copyright (c) 2015, 2018, Oracle and/or its affiliates. All rights reserved.
#

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnome-themes-standard
COMPONENT_VERSION=	3.22.2
COMPONENT_PROJECT_URL=	http://www.gnome.org
COMPONENT_SUMMARY=	Base themes for the GNOME desktop
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:b34516cd59b873c187c1897c25bac3b9ce2d30a472f1fd7ae9d7105d93e17da5
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/gnome-themes-standard/3.22/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE= LGPLv2.1
COMPONENT_LICENSE_FILE = COPYING
COMPONENT_CLASSIFICATION = Desktop (GNOME)/Theming
COMPONENT_FMRI = gnome/theme/$(COMPONENT_NAME)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION =	(cd $(@D) && libtoolize --force &&\
                                        aclocal -I ./m4 &&\
                                        automake -a -f -c --gnu &&\
                                        autoconf )

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=     --libexecdir=/usr/lib/gtk-2.0
CONFIGURE_OPTIONS+=	--localstatedir=/var/lib

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += library/desktop/xdg/icon-naming-utils
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
