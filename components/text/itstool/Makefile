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

BUILD_BITS=NO_ARCH
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		itstool
COMPONENT_VERSION=	2.0.7
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	ITS Tool allows you to translate your XML documents with PO files using rules from the W3C Internationalization Tag Set
COMPONENT_PROJECT_URL=	http://itstool.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:6b9a7cd29a12bb95598f5750e8763cee78836a1a207f85b74d8b3275b27e87ca
COMPONENT_ARCHIVE_URL=	http://files.itstool.org/itstool/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	text/$(COMPONENT_NAME)
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	COPYING.GPL3
COMPONENT_CLASSIFICATION=	System/Text Tools

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

PYTHON_VERSION=3.9

CFLAGS += $(CPP_LARGEFILES)
CPPFLAGS += $(CPP_LARGEFILES)

CONFIGURE_ENV +=	PYTHON=$(PYTHON)

CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCDIR)

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/libxml2
PYTHON_REQUIRED_PACKAGES += runtime/python
