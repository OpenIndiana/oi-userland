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

#
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		foomatic-filters
FOO_VERSION=		4.0
# Latest foomatic-filters patchlevel where the snapshot is derived from.
# Makes the IPS versioning monotonously growing.
FOO_PATCHLEVEL=		17
DAILY_VERSION=		20160212
COMPONENT_VERSION=	$(FOO_VERSION)-$(DAILY_VERSION)
IPS_COMPONENT_VERSION=	$(FOO_VERSION).$(FOO_PATCHLEVEL).$(DAILY_VERSION)
TPNO=			30223
COMPONENT_ARCHIVE_HASH=	sha256:e6f75544d61de5b36ffc4009c0729a6fb0f19245da7d05f0c236731d6f2ebecf
COMPONENT_ARCHIVE_URL=	http://www.openprinting.org/download/foomatic/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://wiki.linuxfoundation.org/openprinting/database/foomatic
COMPONENT_BUGDB=	utility/foomatic

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCDIR)/gnu
CONFIGURE_OPTIONS +=	--with-echo=wecho
CONFIGURE_OPTIONS +=	--with-file-converter="a2ps -1 -q -c -B @@--medium=@@PAGESIZE@@ -o -"
CONFIGURE_OPTIONS +=	--with-execpath=$(USRLIBDIR)/cups/filter:$(USRBINDIR):$(BINDIR)
CONFIGURE_OPTIONS +=	PERL=$(PERL)
CONFIGURE_OPTIONS +=	A2PS=$(USRBINDIR)/a2ps

COMPONENT_PREP_ACTION += (cd $(@D); autoreconf -fiv);
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))
# do not install filters for PPR spooler
COMPONENT_INSTALL_TARGETS= install-cups install-man

REQUIRED_PACKAGES += print/filter/a2ps
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/math
