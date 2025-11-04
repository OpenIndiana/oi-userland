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
# Copyright 2022 Niklas Poslovski
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         gmime3
COMPONENT_VERSION=      3.2.15
COMPONENT_SUMMARY=      A C/C++ MIME creation and parser library with support for S/MIME, PGP, and Unix mbox spools
COMPONENT_PROJECT_URL=  https://github.com/jstedfast/gmime
COMPONENT_SRC=          gmime-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:84cd2a481a27970ec39b5c95f72db026722904a2ccf3fdbd57b280cf2d02b5c4
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/gmime3
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=      LGPLv2.1
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

CFLAGS += $(XPG6MODE)

CONFIGURE_OPTIONS += MAKE=gmake

COMPONENT_TEST_TRANSFORMS += \
	' -n ' \
	' -e "/Testing/p" ' \
	' -e "/Results:/p" '
	
# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libidn2
REQUIRED_PACKAGES += library/security/gpgme
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
