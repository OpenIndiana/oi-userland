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
# Copyright (c) 2014 Alexander Pyhalov
# Copyright 2017 Gary Mills
# Copyright 2019 Michal Nowak
# Copyright 2022 Niklas Poslovski
#

BUILD_BITS=64
BUILD_STYLE=justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         purple-matrix
COMPONENT_VERSION=      0.1.0
COMPONENT_REVISION=     1
COMPONENT_PROJECT_URL=  https://github.com/matrix-org/purple-matrix
COMPONENT_SUMMARY=      Libpurple protocol plugin for matrix
COMPONENT_FMRI=         communication/libpurple/purple-matrix
COMPONENT_SRC=          purple-matrix-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:645c7952740e1b53a9e7a0ea347acc3d305ee5a7aeb20aa43a711e794861ebcf
COMPONENT_ARCHIVE_URL=  http://sourceforge.net/projects/$(COMPONENT_NAME)/files/Pidgin/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_ARCHIVE_URL=	https://github.com/matrix-org/$(COMPONENT_NAME)/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=       Applications/Plug-ins and Run-times
COMPONENT_LICENSE=      GPLv2
COMPONENT_LICENSE_FILE= purple-matrix.license

TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += communication/im/pidgin
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/desktop/json-glib
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/http-parser
REQUIRED_PACKAGES += library/olm
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/libgcrypt
