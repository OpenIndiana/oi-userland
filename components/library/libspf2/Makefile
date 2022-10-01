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
# Copyright 2022 Friedrich Kink
# Copyright 2022 Niklas Poslovski
#

# NOTE (from Arch Package): package version is a pinned commit (titled 'bump to version 1.2.11').
# this is used due to inactivity upstream and CVE-2021-20314.
# when/if upstream becomes active again, this package can be re-done in a
# better way.

BUILD_BITS=		64 # for binaries or 32_and_64 for libraries

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libspf2
COMPONENT_VERSION=      1.2.11
COMPONENT_COMMIT=       8131fe140704eaae695e76b5cd09e39bd1dd220b
COMPONENT_SUMMARY=      libspf2 implements the Sender Policy Framework, a part of the SPF/SRS protocol pair.
COMPONENT_PROJECT_URL=  https://www.$(COMPONENT_NAME).org
COMPONENT_FMRI=         library/libspf2
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_COMMIT)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=  https://github.com/shevek/libspf2/archive/$(COMPONENT_COMMIT).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:2ba3dc7ea380a72646f5b2fbc1fff0d9a10d5c844a998621f8dd410afc50553a
COMPONENT_LICENSE=      Copyright 2005 by Shevek and Wayne Schlitt, LGPL 2.1
COMPONENT_LICENSE_FILE= LICENSES

TEST_TARGET=		$(NO_TESTS)
DROP_STATIC_LIBRARIES=	yes

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION=	cd $(@D) && autoreconf -fvi

# without '-m64' build will fail because of internally built 32bit objects
CONFIGURE_OPTIONS+=	"CFLAGS=-m64 -D__STDC_VERSION__=0"

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
