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
#

BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         spfmilter
COMPONENT_VERSION=      2.0.1
HUMAN_VERSION=          2.001
COMPONENT_REVISION=		1
COMPONENT_SUMMARY=      spfmilter - SPF mail filter module
COMPONENT_DESCRIPTION=	Spfmilter implements the Sender Policy Framework (SPF) as a milter, using libspf2 libraries.
COMPONENT_PROJECT_URL=  https://www.acme.com/software/$(COMPONENT_NAME)/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:fe446200947a910dcabc8c26b7a038548a98abb653bb10a311e90c4071968e7d
COMPONENT_FMRI=         mail/spfmilter
COMPONENT_CLASSIFICATION=Applications/Internet
COMPONENT_LICENSE=      No license available.

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# This packages does not understand the DESTDIR concept
COMPONENT_PRE_CONFIGURE_ACTION= ( cd $(SOURCE_DIR) && $(GSED) -i -e 's:PROTO_DIR:$(PROTO_DIR):' Makefile.in && cp *.8 *.h *.c $(@D) )

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/libmilter
REQUIRED_PACKAGES += library/libspf2
REQUIRED_PACKAGES += system/library
