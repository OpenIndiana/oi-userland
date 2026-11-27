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

BUILD_STYLE = cargo
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		ripgrep
COMPONENT_VERSION =     16.0.0
COMPONENT_SUMMARY =		ripgrep is a line-oriented search tool that recursively searches the current directory for a regex pattern while respecting gitignore rules.
COMPONENT_ARCHIVE_URL =	https://github.com/BurntSushi/ripgrep/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH = sha256:17e7a1a0db80ed9618a0963c7ae4aecb8fce25c70cf7ebed514daf2b38a0d153
COMPONENT_FMRI =		text/ripgrep
COMPONENT_CLASSIFICATION =	Applications/System Utilities
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE-MIT

include $(WS_MAKE_RULES)/common.mk

# Manual dependency added for SPARC
REQUIRED_PACKAGES += system/library/math

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
