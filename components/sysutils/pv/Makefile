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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pv
COMPONENT_VERSION=	1.6.6
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_FMRI=		shell/pipe-viewer
COMPONENT_SUMMARY=	'Pipe Viewer'
COMPONENT_LICENSE=	Artistic
COMPONENT_LICENSE_FILE=	pv.license
COMPONENT_PROJECT_URL=	http://www.ivarch.com/programs/pv.shtml
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:608ef935f7a377e1439c181c4fc188d247da10d51a19ef79bcdee5043b0973f1
COMPONENT_ARCHIVE_URL=	http://www.ivarch.com/programs/sources/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/pv

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PKG_PROTO_DIRS += $(BUILD_DIR_32)

COMPONENT_PRE_CONFIGURE_ACTION = \
    ($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_TEST_ENV +=  PATH="$(GNUBIN):$(PATH)"

ASLR_MODE = $(ASLR_ENABLE)
LD_Z_IGNORE =

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
