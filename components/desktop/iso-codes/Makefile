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
# Copyright 2020, 2024 Andreas Wacknitz
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		iso-codes
COMPONENT_VERSION=	4.17.0
COMPONENT_SUMMARY=	ISO code lists and translations
COMPONENT_SRC=		$(COMPONENT_NAME)-v$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:6d178ef4cea44e55f02eb546b29dcf68d88e9f7a68e0dd7913f5465dbaf8fc14
COMPONENT_PROJECT_URL=	https://salsa.debian.org/iso-codes-team/$(COMPONENT_NAME)
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/-/archive/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		data/iso-codes
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Localizations
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE=	COPYING

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
