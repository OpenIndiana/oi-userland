#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2023 Niklas Poslovski
#

BUILD_STYLE = justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         lmdbxx
COMPONENT_VERSION=      1.0.0
COMPONENT_REVISION=     1
COMPONENT_PROJECT_URL=  https://github.com/hoytech/lmdbxx
COMPONENT_SUMMARY=      C++17 wrapper for the LMDB embedded B+ tree database library
COMPONENT_FMRI=         database/lmdb/library/c++/lmdbxx
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:5e12eb3aefe9050068af7df2c663edabc977ef34c9e7ba7b9d2c43e0ad47d8df
COMPONENT_ARCHIVE_URL=	https://github.com/hoytech/$(COMPONENT_NAME)/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_CLASSIFICATION=       Development/Databases
COMPONENT_LICENSE=      Unlicense
COMPONENT_LICENSE_FILE= UNLICENSE

include $(WS_MAKE_RULES)/common.mk

COMPONENT_INSTALL_ARGS += PREFIX=/usr

# Manually added dependencies
REQUIRED_PACKAGES += database/lmdb

# Auto-generated dependencies
