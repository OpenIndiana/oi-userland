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
# Copyright (c) 2020, Aurelien Larcher. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mdds
COMPONENT_MAJOR_VERSION=	2.1
COMPONENT_VERSION=	$(COMPONENT_MAJOR_VERSION).0
COMPONENT_SUMMARY=      mdds - A collection of multi-dimensional data structures and indexing algorithms
COMPONENT_PROJECT_URL=	https://gitlab.com/mdds/mdds
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:f2941304ae5dc5f315117b3604137891ea90f61ffc0eb75224df7aa2944f5e71
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/-/archive/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=     	library/c++/mdds
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=      MIT
COMPONENT_LICENSE_FILE= LICENSE

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = ( cd ${@D} && NOCONFIGURE=1 ./autogen.sh )

# Auto-generated dependencies
