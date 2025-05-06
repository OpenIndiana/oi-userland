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
# Copyright 2025 Bill Sommerfeld
#

BUILD_STYLE= cmake
USE_PARALLEL_BUILD= yes
USE_DEFAULT_TEST_TRANSFORMS= yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= gnucash-docs
COMPONENT_VERSION= 5.11
COMPONENT_SUMMARY= Desktop accounting program
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL= https://github.com/gnucash/
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:d22a8a1caeffe3b5638de05a9dd3b3166ee0d1c0d2c6e9d6950f1ab7f142e865

COMPONENT_ARCHIVE_URL=	https://sourceforge.net/projects/gnucash/files/gnucash%20%28stable%29/$(COMPONENT_VERSION)/${COMPONENT_ARCHIVE}

COMPONENT_CLASSIFICATION= Applications/Office
COMPONENT_FMRI= desktop/gnucash-docs
COMPONENT_LICENSE= GPLv2 GFDLv1.1
COMPONENT_LICENSE_FILE= COPYING-DOCS

# nothing to test
COMPONENT_TEST_TARGETS=

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

# Auto-generated dependencies
