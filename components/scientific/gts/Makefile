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

BUILD_BITS= 64_and_32
USE_DEFAULT_TEST_TRANSFORMS= yes
USE_COMMON_TEST_MASTER= no
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gts
COMPONENT_VERSION=	0.7.6
COMPONENT_REVISION=	1
COMPONENT_SNAPSHOT_VERSION=	121130
COMPONENT_SUMMARY=     	GNU Triangulated Surface Library 
COMPONENT_SRC=		$(COMPONENT_NAME)-snapshot-$(COMPONENT_SNAPSHOT_VERSION)
COMPONENT_PROJECT_URL=	http://gts.sourceforge.net/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:c23f72ab74bbf65599f8c0b599d6336fabe1ec2a09c19b70544eeefdc069b73b
COMPONENT_ARCHIVE_URL=	http://gts.sourceforge.net/tarballs/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=     	library/math/gts
COMPONENT_CLASSIFICATION=	Development/High Performance Computing
COMPONENT_LICENSE=      GPLv2
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

PATCH_LEVEL= 0

CONFIGURE_OPTIONS += --includedir=$(USRINCDIR)/$(COMPONENT_NAME)
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static

COMPONENT_POST_INSTALL_ACTION += $(RM) -r $(PROTOUSRBINDIR32);

COMPONENT_PRE_CONFIGURE_ACTION += ( $(CLONEY) $(SOURCE_DIR) $(@D) );

COMPONENT_POST_UNPACK_ACTION += $(CHMOD) 755 $(SOURCE_DIR)/test/boolean/test.sh;

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/glib2/32
REQUIRED_PACKAGES += library/netpbm
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
