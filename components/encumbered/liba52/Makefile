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
# Copyright 2015 Alexander Pyhalov
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         liba52
COMPONENT_VERSION=      0.8.0
COMPONENT_SUMMARY=      liba52  - a free library for decoding ATSC A/52 streams
COMPONENT_SRC=          a52dec-v$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:d4f26685d32a8c85f86a5cb800554160fb85400298a0a27151c3d1e63a170943
COMPONENT_PROJECT_URL=  https://liba52.sourceforge.net
COMPONENT_ARCHIVE_URL=  https://git.adelielinux.org/community/a52dec/-/archive/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=System/Media
COMPONENT_FMRI=         library/audio/liba52
COMPONENT_LICENSE=      GPLv2
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION= ( cd $(@D)  && \
	aclocal -I autotools && \
	libtoolize --force --copy && \
	autoheader && \
	automake --add-missing --copy && \
	autoconf )

CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static

COMPONENT_TEST_ENV += PATH=$(PATH.gnu)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
