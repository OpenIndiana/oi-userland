#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.illumos.org/license/CDDL.
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
# Copyright (c) 2015-2016, Aurelien Larcher. All rights reserved.
#
include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=         enlightenment
COMPONENT_VERSION=      0.21.9
COMPONENT_FMRI=         desktop/window-manager/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=System/X11
COMPONENT_SUMMARY=      Enlightenment - The Compositing Window Manager and Desktop Shell
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  https://www.enlightenment.org
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:6b328eec14c5b658b8b3f448d9b65dfc189d98db7b92610e56c438f1232f4973
COMPONENT_ARCHIVE_URL= \
    https://download.enlightenment.org/rel/apps/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      BSD

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_BINDIR.64=$(USRBINDIR)

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--enable-shared
CONFIGURE_OPTIONS+=	--disable-static
CONFIGURE_OPTIONS+=	--disable-cpufreq
CONFIGURE_OPTIONS+=	--disable-temperature
CONFIGURE_OPTIONS+=	--disable-device-udev
CONFIGURE_OPTIONS+=	--disable-mount-udisks

COMPONENT_PREP_ACTION= \
    ( cd $(@D); aclocal -I m4 --install && autoconf && automake -a; )

build: $(BUILD_64)

install: $(INSTALL_64)

test: $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/e/efl
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/dbus/dbus-x11
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libxcb
REQUIRED_PACKAGES += x11/library/xcb-util-keysyms
