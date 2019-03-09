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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		iso-codes
COMPONENT_VERSION=	4.2
COMPONENT_FMRI=		data/iso-codes
COMPONENT_SUMMARY=	ISO code lists and translations
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
	sha256:b1f2190219bbf100aa14d92d5b2683baccd47ed7d80a8ba20ae680c0281caa14
COMPONENT_PROJECT_URL=	https://salsa.debian.org/iso-codes-team/iso-codes
COMPONENT_ARCHIVE_URL=	https://ftp.osuosl.org/pub/blfs/conglomeration/iso-codes/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Localizations

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# GNU ln is needed as '-v' option is used, and GNU msgfmt is required
PATH=$(PATH.gnu)

CLEAN_PATHS	+= build

# Failure to update symlinks
COMPONENT_POST_CONFIGURE_ACTION= \
  ( cd $(@D); $(GSED) -i '/^LN_S/s/s/sfvn/' */Makefile )

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

# bin/xml_from_json.py script requires a Python 3 interpret
REQUIRED_PACKAGES += runtime/python-34

# Auto-generated dependencies
