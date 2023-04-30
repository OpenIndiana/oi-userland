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
# Copyright 2020, 2023 Andreas Wacknitz
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		iso-codes
COMPONENT_VERSION=	4.15.0
COMPONENT_SUMMARY=	ISO code lists and translations
COMPONENT_SRC=		$(COMPONENT_NAME)-v$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:ca2cadca98ad50af6e0ee4e139ec838695f75729d7a2c6353d31d9dfc6d3f027
COMPONENT_PROJECT_URL=	https://salsa.debian.org/iso-codes-team/$(COMPONENT_NAME)
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/-/archive/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		data/iso-codes
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Localizations
COMPONENT_LICENSE=	LGPLv2.1

include $(WS_MAKE_RULES)/common.mk

# GNU ln is needed as '-v' option is used, and GNU msgfmt is required
PATH= $(PATH.gnu)

CLEAN_PATHS	+= build

# Failure to update symlinks
COMPONENT_POST_CONFIGURE_ACTION= \
  ( cd $(@D); $(GSED) -i '/^LN_S/s/s/sfvn/' */Makefile )

# bin/xml_from_json.py script requires a Python 3 interpreter
PYTHON_REQUIRED_PACKAGES += runtime/python

# Auto-generated dependencies
