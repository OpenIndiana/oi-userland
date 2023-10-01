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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2019, Michal Nowak
# Copyright (c) 2023, Niklas Poslovski
#
BUILD_STYLE=meson
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		elinks
COMPONENT_VERSION=	0.16.1.1
COMPONENT_PROJECT_URL=	https://github.com/rkd77/elinks
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:303c6f830b98658dcb813b68432ecde27d3857ccf1e765109fb6b0edb89f5095
COMPONENT_ARCHIVE_URL=	https://github.com/rkd77/$(COMPONENT_NAME)/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		web/browser/elinks
COMPONENT_SUMMARY=	advanced text-mode WWW browser
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += -Dgpm=false
CONFIGURE_OPTIONS += -Didn=false

# Auto-generated dependencies
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/security/openssl-31
REQUIRED_PACKAGES += library/tre
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
