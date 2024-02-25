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
# Copyright 2016 Alexander Pyhalov
# Copyright 2019 Michal Nowak
# Copyright 2020 Marco van Wieringen
# Copyright (c) 2021 Tim Mooney.  All rights reserved
# Copyright 2022 Andreas Wacknitz
#

MATE_CATEGORY= APP
BUILD_STYLE= configure
include ../../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/mate.mk

COMPONENT_NAME=		mate-user-guide
COMPONENT_MJR_VERSION=	1.28
COMPONENT_MNR_VERSION=	0
COMPONENT_SUMMARY=	MATE documentation
COMPONENT_ARCHIVE_HASH= sha256:53ef0814f506544614ed61ab7be5221cc8d3a9f14f7ef9698c90fe7e46014b9e
COMPONENT_ARCHIVE_URL=	https://pub.mate-desktop.org/releases/$(COMPONENT_MJR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Documentation
COMPONENT_LICENSE=	FDLv1.1
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION = ( $(CLONEY) $(SOURCE_DIR) $(@D) )
CONFIGURE_SCRIPT = $(@D)/configure

# build dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/xml-parser
PERL_REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += text/gnu-gettext
REQUIRED_PACKAGES += text/gnu-grep
REQUIRED_PACKAGES += text/intltool

# Auto-generated dependencies
