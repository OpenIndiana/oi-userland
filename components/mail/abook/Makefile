#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END

#
# Copyright (c) 2015 Matt Samudio
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		abook
COMPONENT_VERSION=	0.5.6
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://abook.sourceforge.net/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:0646f6311a94ad3341812a4de12a5a940a7a44d5cb6e9da5b0930aae9f44756e
COMPONENT_ARCHIVE_URL=	http://prdownloads.sourceforge.net/abook/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		mail/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_SUMMARY=	abook addressbook program
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CPPFLAGS += -I/usr/include/ncurses
CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

COMPONENT_PRE_CONFIGURE_ACTION = (cp -r $(SOURCE_DIR)/* $(BUILD_DIR_$(BITS))/) 
COMPONENT_BUILD_ARGS=
COMPONENT_BUILD_ENV += CC=$(CC)

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += system/library
