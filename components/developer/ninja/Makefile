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
BUILD_BITS=64
BUILD_STYLE=justmake

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         ninja
COMPONENT_VERSION=      1.10.2
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=      Ninja - a small build system with a focus on speed
COMPONENT_PROJECT_URL=  https://ninja-build.org/
COMPONENT_FMRI=         developer/build/ninja
COMPONENT_CLASSIFICATION=Development/Distribution Tools
COMPONENT_SRC=    $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL= \
	https://github.com/ninja-build/ninja/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:ce35865411f0490368a8fc383f29071de6690cbadc27704734978221f25e2bed
COMPONENT_LICENSE=      Apache License version 2.0

include $(WS_MAKE_RULES)/common.mk

PATH=$(GCC_BINDIR):$(PATH.illumos)

PYTHON_VERSION=3.9

COMPONENT_BUILD_ACTION = cd $(@D); \
  CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)" ./configure.py --bootstrap --with-python=$(PYTHON.64)

COMPONENT_TEST_CMD = cd $(@D); \
  CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)" ./configure.py && ./ninja ninja_test && ./ninja_test
COMPONENT_TEST_TARGETS =

COMPONENT_INSTALL_ACTION = cd $(@D); \
	$(MKDIR) $(PROTO_DIR)/usr/bin && \
  install -vm755 ninja $(PROTO_DIR)/usr/bin/ && \
	$(MKDIR) $(PROTO_DIR)/usr/share/vim/vim80/syntax && \
  install -vDm644 misc/ninja.vim \
      $(PROTO_DIR)/usr/share/vim/vim80/syntax/ninja.vim && \
	$(MKDIR) $(PROTO_DIR)/usr/share/bash-completion/completions && \
  install -vDm644 misc/bash-completion \
      $(PROTO_DIR)/usr/share/bash-completion/completions/ninja && \
	$(MKDIR) $(PROTO_DIR)/usr/share/zsh-completions && \
  install -vDm644 misc/zsh-completion \
      $(PROTO_DIR)/usr/share/zsh-completions/_ninja

COMPONENT_PRE_TEST_ACTION = \
    cd $(BUILD_DIR_64); \
    ./ninja all;

COMPONENT_TEST_CMD = cd $(BUILD_DIR_64); ./ninja_test
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_TRANSFORMS+= '-n -e "/^\[[0-9]*\/341\]/p"'

# Build dependencies
REQUIRED_PACKAGES += developer/lexer/re2c
REQUIRED_PACKAGES += runtime/python-39

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
