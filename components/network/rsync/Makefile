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
# Copyright (c) 2009, 2012, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2018, Michal Nowak
# Copyright (c) 2020, 2022, Andreas Wacknitz
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		rsync
COMPONENT_VERSION=	3.5.0
COMPONENT_SUMMARY=	Utility that provides fast incremental file transfer and copy
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://rsync.samba.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:c7ffd1ef653e99540f661e47cb00b7f9cad1ee6b972399b16f93d672656e0d33
COMPONENT_ARCHIVE_URL=	https://rsync.samba.org/ftp/rsync/src/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	network/rsync
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_LICENSE=	GPL-3.0-only
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

# Make gcc-14 happy (configure needs this!)
CFLAGS += -Wno-error=implicit-function-declaration

CONFIGURE_OPTIONS += --with-included-popt
CONFIGURE_OPTIONS += --enable-xattr-support
CONFIGURE_OPTIONS += CPPFLAGS=-I$(OPENSSL_INCDIR)
CONFIGURE_OPTIONS += LDFLAGS=-L$(OPENSSL_LIBDIR)

# Make sure to use 64 bit binaries if available. This is needed during tests by fakeroot. 
COMPONENT_TEST_ENV += PATH="/usr/bin/amd64:$(PATH.gnu)"

COMPONENT_TEST_TRANSFORMER = $(NAWK)
COMPONENT_TEST_TRANSFORMS = "'/^PASS|^SKIP|^FAIL|^XFAIL|passed|skipped|failed/'"

# Manually added; needed during tests
TEST_REQUIRED_PACKAGES += developer/fakeroot

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += library/libxxhash
REQUIRED_PACKAGES += library/lz4
REQUIRED_PACKAGES += system/library
