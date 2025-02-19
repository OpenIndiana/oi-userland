#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2017-2018 Aurelien Larcher
#

BUILD_STYLE = cmake
USE_PARALLEL_BUILD = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         ninja
COMPONENT_VERSION=	1.12.1
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=      Ninja - a small build system with a focus on speed
COMPONENT_PROJECT_URL=  https://ninja-build.org/
COMPONENT_SRC=    		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/ninja-build/ninja/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:821bdff48a3f683bc4bb3b6f0b5fe7b2d647cf65d52aeb63328c91a6c6df285a
COMPONENT_FMRI=         developer/build/ninja
COMPONENT_CLASSIFICATION=Development/Distribution Tools
COMPONENT_LICENSE=	Apache-2.0
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

# Install additional files for command line completion
COMPONENT_POST_INSTALL_ACTION += $(INSTALL) -D $(SOURCE_DIR)/misc/bash-completion $(PROTOUSRSHAREDIR)/bash-completion/completions/ninja ;
COMPONENT_POST_INSTALL_ACTION += $(INSTALL) -D $(SOURCE_DIR)/misc/zsh-completion $(PROTOUSRSHAREDIR)/zsh-completions/_ninja ;

# see README.md
COMPONENT_TEST_CMD = ./ninja_test

# Remove timing
COMPONENT_TEST_TRANSFORMS += "-e 's/ ([0-9]\{1,\} ms.*)\$$//'"

# Build dependencies
REQUIRED_PACKAGES += developer/lexer/re2c
PYTHON_REQUIRED_PACKAGES += runtime/python

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
