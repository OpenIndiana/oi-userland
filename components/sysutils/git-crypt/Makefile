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
# Copyright (c) 2022 Andreas Wacknitz
#

BUILD_STYLE= justmake
# Alas this doesn't work yet:
USE_OPENSSL11= Yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         git-crypt
COMPONENT_VERSION=      0.7.0
COMPONENT_REVISION= 1
COMPONENT_SUMMARY=      git-crypt - transparent file encryption in git
COMPONENT_DESCRIPTION=	\
	git-crypt enables transparent encryption and decryption of files in a git repository. \
	Files which you choose to protect are encrypted when committed, and decrypted when checked out. \
	git-crypt lets you freely share a repository containing a mix of public and private content. \
	git-crypt gracefully degrades, so developers without the secret key can still clone and commit to \
	a repository with encrypted files. This lets you store your secret material (such as keys or passwords) \
	in the same repository as your code, without requiring you to lock down your entire repository.
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  https://github.com/AGWA/git-crypt
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:2210a89588169ae9a54988c7fdd9717333f0c6053ff704d335631a387bd3bcff
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=         crypto/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_LICENSE=		GPLv3
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Manually added build dependencies
REQUIRED_PACKAGES += library/libxslt

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += system/library
