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

#
# Copyright (c) 2024, Andreas Wacknitz
#

BUILD_STYLE= justmake
DROP_STATIC_LIBRARIES= yes
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         tree-sitter
COMPONENT_VERSION=      0.25.5
COMPONENT_SUMMARY=      Tree-sitter is a parser generator tool and an incremental parsing library
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  https://tree-sitter.github.io/tree-sitter/
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:17a72b9dd7525b01d8fabf9ebee0edd3203fe3058ccc73cbc5e2070ccbe26c0d
COMPONENT_ARCHIVE_URL=  https://github.com/tree-sitter/tree-sitter/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=         library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=      MIT
COMPONENT_LICENSE_FILE= LICENSE

include $(WS_MAKE_RULES)/common.mk

COMPONENT_BUILD_ENV += PREFIX=$(USRDIR)
COMPONENT_BUILD_ENV += LIBDIR=$(USRLIBDIR64)
COMPONENT_INSTALL_ENV += PREFIX=$(USRDIR)
COMPONENT_INSTALL_ENV += LIBDIR=$(USRLIBDIR64)

PATH= $(PATH.gnu)

COMPONENT_TEST_TARGETS= test

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
