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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libiax2
COMPONENT_VERSION=      0.2.3
COMPONENT_FMRI=         library/libiax2
COMPONENT_SUMMARY=      A portable IAX/IAX2 protocol telephony client library.
COMPONENT_CLASSIFICATION=Applications/Internet
COMPONENT_SRC=          iaxmodem-1.3.3
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:463f96b4e7e1abf0efc9bdb7cbe3b2f10486a123ca8e2e40a5b04c1abb00d28d
COMPONENT_PROJECT_URL=  https://iaxmodem.sourceforge.net/
COMPONENT_ARCHIVE_URL=  https://sourceforge.net/projects/iaxmodem/files/latest/$(COMPONENT_ARCHIVE)

COMPONENT_LICENSE=      GPLv2

TEST_TARGET=$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

#
# we just want to build libiax2 
# the real iaxmodem will be build in an own package
#
CONFIGURE_SCRIPT =      $(SOURCE_DIR)/lib/libiax2/configure

COMPONENT_PRE_CONFIGURE_ACTION += ( \
        cd $(SOURCE_DIR)/lib/libiax2; \
        ./bootstrap.sh; \
        $(CLONEY) $(SOURCE_DIR)/lib/libiax2 $(@D); \
         );

COMPONENT_POST_CONFIGURE_ACTION += ( $(GSED) -i -e 's:$$(includedir)/iax:$$(DESTDIR)$$(includedir)/iax:' $(@D)/src/Makefile )

CFLAGS+=        -DSOLARIS

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
