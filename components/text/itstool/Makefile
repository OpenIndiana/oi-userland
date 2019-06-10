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
# Copyright 2016 Jim Klimov
# Copyright 2019 Tim Mooney
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		itstool
COMPONENT_VERSION=	2.0.6
COMPONENT_SUMMARY=	ITS Tool allows you to translate your XML documents with PO files using rules from the W3C Internationalization Tag Set
COMPONENT_PROJECT_URL=	http://itstool.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:6233cc22726a9a5a83664bf67d1af79549a298c23185d926c3677afa917b92a9
COMPONENT_ARCHIVE_URL=	http://files.itstool.org/itstool/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	text/$(COMPONENT_NAME)
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	COPYING.GPL3
COMPONENT_CLASSIFICATION=	System/Text Tools

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

CFLAGS += $(CPP_LARGEFILES)
CPPFLAGS += $(CPP_LARGEFILES)

CONFIGURE_ENV +=	PYTHON=$(PYTHON)

CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCDIR)

# common targets; no ARCH since this is just a script
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/libxml2-27
REQUIRED_PACKAGES += runtime/python-27
