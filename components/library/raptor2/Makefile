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
# Copyright (c) 2013 David Hoeppner. All rights reserved.
# Copyright (c) 2019 Nona Hansel
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		raptor2
COMPONENT_VERSION=	2.0.15
COMPONENT_PROJECT_URL=	http://librdf.org/raptor/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:ada7f0ba54787b33485d090d3d2680533520cd4426d2f7fb4782dd4a6a1480ed
COMPONENT_ARCHIVE_URL=	http://download.librdf.org/source/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS  +=		--disable-static
CONFIGURE_OPTIONS  +=		--enable-shared

$(INSTALL_64):	COMPONENT_POST_INSTALL_ACTION = \
	/usr/bin/elfedit -e "dyn:runpath ''" $(PROTOUSRLIBDIR64)/libraptor2.so.0.0.0

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += library/libyajl2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += web/curl
