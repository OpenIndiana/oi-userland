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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2019, Michal Nowak
# Copyright (c) 2021, Nona Hansel
#

BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         xorriso
COMPONENT_VERSION=      1.5.7
#IPS_COMPONENT_VERSION=	$(COMPONENT_VERSION).2
#HUMAN_VERSION=			1.5.6.pl02
COMPONENT_SUMMARY=		command line ISO-9660 and Rock Ridge manipulation tool
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  https://www.gnu.org/software/xorriso/
COMPONENT_ARCHIVE=      $(COMPONENT_NAME)-$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:867577c387f6b4a9a3224eb441ded8fb1638df6cbc060f8d1a1e5d00f318f502
COMPONENT_ARCHIVE_URL=  https://www.gnu.org/software/xorriso/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			media/xorriso
COMPONENT_CLASSIFICATION=	System/Media
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	COPYING

CPPFLAGS += -I./test

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --sysconfdir=/etc/gnu
CONFIGURE_OPTIONS += --infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS += CPPFLAGS="$(CPPFLAGS)"

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/tk-8
REQUIRED_PACKAGES += system/library
