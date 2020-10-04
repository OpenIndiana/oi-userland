#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2020 Alexander Pyhalov
#

BUILD_BITS= 32_and_64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           anthy
COMPONENT_VERSION=        9100h
IPS_COMPONENT_VERSION=    0.9100.8
COMPONENT_REVISION=		  1
COMPONENT_SUMMARY=        libanthy - Japanese input method library
COMPONENT_SRC=            $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=   sha256:d256f075f018b4a3cb0d165ed6151fda4ba7db1621727e0eb54569b6e2275547
COMPONENT_ARCHIVE_URL=    https://jaist.dl.sourceforge.jp/anthy/37536/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=           system/input-method/library/libanthy
COMPONENT_CLASSIFICATION= System/Localizations
COMPONENT_LICENSE=        LGPL v2.1
COMPONENT_LICENSE_FILE=   COPYING
COMPONENT_PROJECT_URL=    https://anthy.osdn.jp/

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --disable-static

# Build dependencies
REQUIRED_PACKAGES += editor/gnu-emacs

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
