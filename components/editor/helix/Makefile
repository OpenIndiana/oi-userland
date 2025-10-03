#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2025 Till Wegmueller
#

BUILD_STYLE=cargo
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=					helix
HUMAN_VERSION=                  25.07.1
COMPONENT_VERSION=              25.7.1
COMPONENT_SUMMARY=				A post-modern text editor.
COMPONENT_PROJECT_URL=			https://helix-editor.com/
COMPONENT_FMRI=					editor/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=		Development/Editors
COMPONENT_SRC=					$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=				$(COMPONENT_SRC)-source.tar.xz
COMPONENT_ARCHIVE_URL=			https://github.com/helix-editor/helix/releases/download/$(HUMAN_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=			sha256:2d0cf264ac77f8c25386a636e2b3a09a23dec555568cc9a5b2927f84322f544e
COMPONENT_LICENSE=				MPL-2.0
COMPONENT_LICENSE_FILE=         LICENSE

TEST_TARGET=$(NO_TESTS) # if no testsuite enabled
include $(WS_MAKE_RULES)/common.mk

UNPACK_ARGS=					-r $(COMPONENT_SRC)

COMPONENT_BUILD_ENV += HELIX_DEFAULT_RUNTIME=/usr/lib/helix/runtime

COMPONENT_INSTALL_ARGS = --path helix-term
COMPONENT_INSTALL_ARGS += --root $(PROTOUSRDIR)
COMPONENT_INSTALL_ARGS += --force
COMPONENT_INSTALL_ARGS += --no-track
COMPONENT_INSTALL_ARGS += --offline
COMPONENT_INSTALL_ARGS += --locked

COMPONENT_POST_INSTALL_ACTION =  ./install.sh $(PROTO_DIR) $(SOURCE_DIR)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
