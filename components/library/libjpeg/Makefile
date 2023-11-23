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
# Copyright 2023 Till Wegmueller
#

BUILD_BITS=64 # for binaries or 32_and_64 for libraries
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			libjpeg
COMPONENT_VERSION=		9.5
PROJECT_VERSION =       	9e
COMPONENT_SUMMARY=		'The JPEG reference implementation'
COMPONENT_PROJECT_URL=		https://www.ijg.org/
COMPONENT_FMRI=			image/library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	System/Multimedia Libraries
COMPONENT_SRC=			jpeg-$(PROJECT_VERSION)
COMPONENT_ARCHIVE=		jpegsrc.v$(PROJECT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL=		https://www.ijg.org/files/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=		sha256:4077d6a6a75aeb01884f708919d25934c93305e49f7e3f36db9129320e6f4f3d
COMPONENT_LICENSE=		libjpeg.license

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS +=    --enable-shared

CONFIGURE_ENV += INSTALL="$(INSTALL) -D"

# Prevent libtool from embedding runpath (via -R).
COMPONENT_POST_CONFIGURE_ACTION += \
        $(GSED) -i -e 's/hardcode_into_libs=yes/hardcode_into_libs=no/' $(@D)/libtool; \
        $(GSED) -i -e 's/hardcode_libdir_flag_spec=.*/hardcode_libdir_flag_spec=""/' $(@D)/libtool;

# Build dependencies

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
