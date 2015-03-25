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
# Copyright (c) 2013, Aurelien Larcher. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		evas_generic_loaders
COMPONENT_VERSION=	1.12.0
COMPONENT_REVISION=	1
COMPONENT_FMRI=     	library/e/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://enlightenment.org
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:c531c82845b656cb8ea8e2db1e413509d9b4558450be6c5ee27da0cdc781376e
COMPONENT_ARCHIVE_URL=	http://download.enlightenment.org/rel/libs/$(COMPONENT_SRC_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      GPLv2
COMPONENT_LICENSE_FILE= $(COMPONENT_NAME).license
COMPONENT_SUMMARY=      Enlightenment - Evas external binary executable loaders

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION =        ( cd $(@D)  && \
					libtoolize --copy --force &&\
					aclocal -I m4 &&\
					automake -c -f -a &&\
					autoconf )


CONFIGURE_OPTIONS+=	--enable-poppler
CONFIGURE_OPTIONS+=	--enable-spectre
CONFIGURE_OPTIONS+=	--disable-libraw # adding libraw requires a bump of libjpeg
CONFIGURE_OPTIONS+=	--enable-svg
CONFIGURE_OPTIONS+=	--enable-gstreamer


build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)

BUILD_PKG_DEPENDENCIES =    $(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk

