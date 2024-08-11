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
# Copyright (c) 2023-2024, Jonathan Schleifer. All rights reserved.
#

BUILD_BITS = 64
USE_PARALLEL_BUILD = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME = objfw
COMPONENT_VERSION = 1.1.6
COMPONENT_SUMMARY = A portable, lightweight framework for the Objective-C language
COMPONENT_SRC = $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE = $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH = sha256:c19a97a011e14780fb32cfbdbbd6a699a955b57124e4e079768cb8aad4430e1d
COMPONENT_ARCHIVE_URL = https://objfw.nil.im/downloads/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://objfw.nil.im/
COMPONENT_FMRI = library/objfw
COMPONENT_CLASSIFICATION = Development/Objective C
COMPONENT_LICENSE = LGPLv3
COMPONENT_LICENSE_FILE = COPYING

include $(WS_MAKE_RULES)/common.mk

# The build system does not support building out of tree.
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS += --disable-rpath
CONFIGURE_OPTIONS += --with-tls=gnutls
CONFIGURE_OPTIONS += OBJC="$(CLANG_PREFIX)/bin/clang -m$(BITS)"
CONFIGURE_OPTIONS += LDFLAGS="-Wl,-rpath,$$(realpath $$(dirname $$(gcc -m$(BITS) --print-file-name=libgcc_s.so)))"

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
