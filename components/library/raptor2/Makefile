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

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		raptor2
COMPONENT_VERSION=	2.0.16
COMPONENT_REVISION=	2
COMPONENT_SUMMARY=	RDF Parser Library - RDF parser utility
COMPONENT_PROJECT_URL=	https://librdf.org/raptor/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:089db78d7ac982354bdbf39d973baf09581e6904ac4c92a98c5caadb3de44680
COMPONENT_ARCHIVE_URL=	https://download.librdf.org/source/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			library/raptor2
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=		Apache 2.0, LGPLv2.1+, GPLv2+, Raptor RDF Syntax Library License
COMPONENT_LICENSE_FILE=		LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-shared

COMPONENT_POST_INSTALL_ACTION = \
	$(ELFEDIT) -e "dyn:runpath ''" $(PROTOUSRLIBDIR64)/libraptor2.so.0.0.0

# Auto-generated dependencies
REQUIRED_PACKAGES += $(ICU_LIBRARY_PKG)
REQUIRED_PACKAGES += developer/icu
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += library/libyajl2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += web/curl
