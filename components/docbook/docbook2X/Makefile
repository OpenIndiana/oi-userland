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
# Copyright 2020 Aurelien Larcher
#

BUILD_BITS=64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		docbook2X
COMPONENT_VERSION=	0.8.8
COMPONENT_SUMMARY=	docbook2X - converts DocBook documents into the traditional Unix man page format and the GNU Texinfo format
COMPONENT_PROJECT_URL=	http://docbook2x.sourceforge.net/
COMPONENT_FMRI=		data/docbook2x
COMPONENT_CLASSIFICATION=Desktop (GNOME)/Documentation
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://sourceforge.net/projects/docbook2x/files/docbook2x/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_ARCHIVE_HASH= sha256:4077757d367a9d1b1427e8d5dfc3c49d993e90deabc6df23d05cfe9cd2fcdc45
COMPONENT_LICENSE=	MIT

include $(WS_MAKE_RULES)/common.mk

# Build dependencies
REQUIRED_PACKAGES += library/perl-5/xml-sax 

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
