#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2014 Josef 'Jeff' Sipek <jeffpc@josefsipek.net>
# Copyright 2019 Nona Hansel
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		hercules
COMPONENT_VERSION=	4.7
COMPONENT_PROJECT_URL=	https://sdl-hercules-390.github.io/html/
COMPONENT_FMRI=		emulator/hercules
COMPONENT_SRC=		hyperion-Release_$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:74c747773e0b5639164f6f69ce9220e1bd1d4853c5c4f18329da21c03aebe388
COMPONENT_ARCHIVE_URL=	https://github.com/SDL-Hercules-390/hyperion/archive/refs/tags/Release_$(HUMAN_VERSION).tar.gz
COMPONENT_LICENSE=	QPL-1.0
COMPONENT_LICENSE_FILE=	COPYRIGHT
COMPONENT_SUMMARY=	The Hercules S/370, ESA/390, and z/Architecture Emulator
COMPONENT_CLASSIFICATION=System/Virtualization

include $(WS_MAKE_RULES)/common.mk

# configure expects GNU make
PATH= $(PATH.gnu)

CONFIGURE_OPTIONS += --disable-ipv6

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
