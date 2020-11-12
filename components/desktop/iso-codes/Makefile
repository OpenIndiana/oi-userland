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
# Copyright 2014 Ken Mays. All rights reserved.
# Copyright 2016 Adam Stevko. All rights reserved.
# Copyright 2019 Michal Nowak
# Copyright 2020 Andreas Wacknitz
#

BUILD_BITS=			32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		iso-codes
COMPONENT_VERSION=	4.5.0
COMPONENT_FMRI=		data/iso-codes
COMPONENT_SUMMARY=	ISO code lists and translations
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
	sha256:295caf14632696a5c6aedf4119450a7943581cff34b628c46bbe16f0d21e3201
COMPONENT_PROJECT_URL=	https://salsa.debian.org/iso-codes-team/iso-codes
COMPONENT_ARCHIVE_URL=	https://ftp.osuosl.org/pub/blfs/conglomeration/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Localizations

include $(WS_MAKE_RULES)/common.mk

# GNU ln is needed as '-v' option is used, and GNU msgfmt is required
PATH=$(PATH.gnu)

CLEAN_PATHS	+= build

# Failure to update symlinks
COMPONENT_POST_CONFIGURE_ACTION= \
  ( cd $(@D); $(GSED) -i '/^LN_S/s/s/sfvn/' */Makefile )

# bin/xml_from_json.py script requires a Python 3 interpret
REQUIRED_PACKAGES+= $(PYTHON3_RUNTIME_PKG)

# Auto-generated dependencies
