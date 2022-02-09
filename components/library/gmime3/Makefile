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
COMPONENT_VERSION=      3.2.7
#COMPONENT_REVISION=     1
COMPONENT_PROJECT_URL=  https://github.com/jstedfast/gmime
COMPONENT_SUMMARY=      A C/C++ MIME creation and parser library with support for S/MIME, PGP, and Unix mbox spools
COMPONENT_FMRI=         library/gmime3
COMPONENT_SRC=          gmime-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
    sha256:2aea96647a468ba2160a64e17c6dc6afe674ed9ac86070624a3f584c10737d44
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/gmime/3.2/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=      LGPLv2.1
COMPONENT_LICENSE_FILE= gmime3.license

CONFIGURE_OPTIONS += MAKE=gmake

TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libidn2
REQUIRED_PACKAGES += library/security/gpgme
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
