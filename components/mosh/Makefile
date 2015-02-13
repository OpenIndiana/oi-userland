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
# Copyright (c) 2015, Predrag Zecevic. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		mosh
COMPONENT_VERSION=	1.2.4
COMPONENT_REVISION=	1
COMPONENT_FMRI=	service/network/mosh
COMPONENT_CLASSIFICATION=System/Security
#                        or System/Services not sure
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://mosh.mit.edu/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:e74d0d323226046e402dd469a176075fc2013b69b0e67cea49762c957175df46
COMPONENT_ARCHIVE_URL=	https://mosh.mit.edu/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      GPLv3+
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license 
COMPONENT_SUMMARY=	Mosh (mobile shell) - Remote terminal application that allows roaming, supports intermittent connectivity, and provides intelligent local echo and line editing of user keystrokes (replacement for SSH).

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

CONFIGURE_OPTIONS+=	--sysconfdir=$(USRSHAREDIR)
CONFIGURE_OPTIONS+=	--enable-examples --enable-completion

COMPONENT_POST_INSTALL_ACTION= mkdir -p $(PROTO_DIR)/$(BASH_COMPLETIONS_PATH) && \
mv $(PROTO_DIR)/$(USRSHAREDIR)/bash_completion.d/mosh $(PROTO_DIR)/$(BASH_COMPLETIONS_PATH)/mosh && \
rmdir $(PROTO_DIR)/$(USRSHAREDIR)/bash_completion.d;

# Depends on protobuf only available as 32bit binaries

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)

BUILD_PKG_DEPENDENCIES =    $(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
