#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.illumos.org/license/CDDL.
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
# Copyright (c) 2015, Aurelien Larcher. All rights reserved.
#
include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		expedite
COMPONENT_VERSION=	1.7.9
COMPONENT_REVISION=	1
COMPONENT_FMRI=     	library/e/expedite
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://enlightenment.org
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:a05be096c911e0d66d4bdc497ebb935a04ad23696de9084aed9959b5172a593e
COMPONENT_ARCHIVE_URL=	http://download.enlightenment.org/releases/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      BSD
COMPONENT_LICENSE_FILE= $(COMPONENT_NAME).license
COMPONENT_SUMMARY=      Enlightenment - Performance and correctness test suite for Evas

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PYTHON_VERSION=2.7

PATCH_LEVEL=0

CONFIGURE_OPTIONS+=	--enable-opengl-x11
CONFIGURE_OPTIONS+=	--enable-software-x11
CONFIGURE_OPTIONS+=	--with-x

# pkgdepend fails to resolve the python version if env is used
COMPONENT_POST_INSTALL_ACTION=sed -i -e '1 s|^.*$$|\#!/usr/bin/python$(PYTHON_VERSION)|' $(PROTO_DIR)/usr/bin/expedite-cmp;


build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)

REQUIRED_PACKAGES += library/e/efl
REQUIRED_PACKAGES += library/sdl
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
