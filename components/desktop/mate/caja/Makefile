#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016 Till Wegmueller
# Copyright 2016 Ken Mays
# Copyright 2020 Michal Nowak
# Copyright (c) 2021 Tim Mooney.  All rights reserved
# Copyright 2022 Andreas Wacknitz
#

MATE_CATEGORY= APP
BUILD_STYLE= configure
USE_COMMON_TEST_MASTER= no
include ../../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/mate.mk

COMPONENT_NAME=		caja
COMPONENT_MJR_VERSION=	1.26
COMPONENT_MNR_VERSION=	1
COMPONENT_REVISION=	2
COMPONENT_SUMMARY=	File manager for the MATE desktop
COMPONENT_ARCHIVE_HASH= sha256:30fd6e6f00a38200f6e2e898ad7fa797876bb060f1d0341dd2f7393279e14c07
COMPONENT_LICENSE=	GPLv2, LGPLv2, FDLv1.1
COMPONENT_CLASSIFICATION= System/Libraries

TEST_TARGET= $(TEST_$(MK_BITS))
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION=	\
	( cp $(COMPONENT_DIR)/files/icons/*.png $(@D)/icons && \
		cd $(@D) && NOCONFIGURE=1 ./autogen.sh )

# tests in different dirs, keep going if early tests fail
COMPONENT_TEST_ARGS += -k -i
# minimal tests
unexport SHELLOPTS
COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/^\(PASS|SKIP|FAIL\): /p" ' \
	"-e '/^====*/p' " \
	'-e "s/^\(Testsuite summary\).*/\1/p" ' \
	'-e "/^. TOTAL: /,/^. ERROR: /p" '

# Build dependencies
REQUIRED_PACKAGES += developer/build/autoconf-archive

# Auto-generated dependencies
REQUIRED_PACKAGES += image/library/libexif
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/mate/mate-desktop
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libnotify
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/file-system/zfs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
