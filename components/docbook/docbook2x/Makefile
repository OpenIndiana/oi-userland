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
# Copyright 2025 Andreas Wacknitz
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= docbook2X
COMPONENT_VERSION= 0.8.8
COMPONENT_SUMMARY= docbook2x converts DocBook documents into the traditional Unix man page format and the GNU Texinfo format
COMPONENT_PROJECT_URL= https://docbook2x.sourceforge.net
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL= https://sourceforge.net/projects/docbook2x/files/docbook2x/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_ARCHIVE_HASH= sha256:4077757d367a9d1b1427e8d5dfc3c49d993e90deabc6df23d05cfe9cd2fcdc45
COMPONENT_FMRI= text/docbook2x
COMPONENT_CLASSIFICATION= System/Text Tools
COMPONENT_LICENSE= MIT style
COMPONENT_LICENSE_FILE= COPYING

# Tests fail to build
TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_POST_INSTALL_ACTION += $(RM) $(PROTOUSRSHAREDIR)/info/dir ;

# Manually added build dependencies
# for xmllint
REQUIRED_PACKAGES += library/libxml2
# for xsltproc
REQUIRED_PACKAGES += library/libxslt
# for sgml2xml
REQUIRED_PACKAGES += developer/documentation-tool/opensp
REQUIRED_PACKAGES += text/gawk
REQUIRED_PACKAGES += text/groff
REQUIRED_PACKAGES += text/texinfo
REQUIRED_PACKAGES += text/tidy

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
