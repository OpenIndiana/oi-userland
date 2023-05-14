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

MATE_CATEGORY= LIB
BUILD_STYLE= configure
include ../../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/mate.mk

COMPONENT_NAME=		libmatekbd
COMPONENT_MJR_VERSION=  1.26
COMPONENT_MNR_VERSION=  1
COMPONENT_SUMMARY=	MATE keyboard shared library
COMPONENT_ARCHIVE_HASH= sha256:63938d91252945eeea88fd8374d1231bd83d02cd965c6bba17c185edb397bced
COMPONENT_LICENSE=	GPLv2, LGPLv2, FDLv1.1

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/libxklavier
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
