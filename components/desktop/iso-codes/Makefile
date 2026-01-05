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
# Copyright 2020, 2026 Andreas Wacknitz
#

BUILD_STYLE= meson
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		iso-codes
COMPONENT_VERSION=	4.20.1
COMPONENT_SUMMARY=	ISO code lists and translations
COMPONENT_SRC=		$(COMPONENT_NAME)-v$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:66ea9879f9a4d6f767f424bf74bc5471215d36d54f8940f6d32dd7737ceef046
COMPONENT_PROJECT_URL=	https://salsa.debian.org/iso-codes-team/$(COMPONENT_NAME)
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/-/archive/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		data/iso-codes
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Localizations
COMPONENT_LICENSE=	LGPLv2.1+

include $(WS_MAKE_RULES)/common.mk

# GNU ln is needed as '-v' option is used, and GNU msgfmt is required
PATH= $(PATH.gnu)

CLEAN_PATHS	+= build

# bin/xml_from_json.py script requires a Python 3 interpreter
PYTHON_REQUIRED_PACKAGES += runtime/python

# Auto-generated dependencies
