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
# Copyright (c) 2022 Jim Klimov
#

BUILD_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pidgin-save-conv-order
COMPONENT_VERSION=	1.1
COMPONENT_PROJECT_URL=	https://github.com/kgraefe/pidgin-save-conv-order
COMPONENT_SUMMARY=	Save Conversations Order Messaging plugin for Pidgin
COMPONENT_DESCRIPTION=	This plugin saves the order of chats and IMs and restores it the next time you open a conversation
COMPONENT_CLASSIFICATION=	org.opensolaris.category.2008:Applications/Internet
COMPONENT_FMRI=	communication/im/pidgin/$(COMPONENT_NAME)
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:5b9e796ed75979594538100fe788eeeed5961c27b8f4cd8bb13f33290b5f6ce8
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE_FILE=	pidgin-save-conv-order.license
COMPONENT_LICENSE=	GPL v2

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION =        ( cd $(@D) && \
                                        aclocal -I. && \
                                        autoheader && \
                                        libtoolize --automake --copy --force && \
                                        automake -a -f -c &&\
                                        autoconf )


CONFIGURE_OPTIONS+=	--sysconfdir=/etc

CONFIGURE_ENV+=	PERL=$(PERL)
CONFIGURE_ENV+=	INTLTOOL_PERL=$(PERL)
CONFIGURE_ENV+=	PYTHON=$(PYTHON)

# Build dependencies
REQUIRED_PACKAGES += communication/im/pidgin

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += library/desktop/gtk2
