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
# Copyright 2022 Niklas Poslovski
#
BUILD_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         mono
COMPONENT_VERSION=      6.13.0.1239
#COMPONENT_REVISION=     1
COMPONENT_PROJECT_URL=  https://www.mono-project.com
COMPONENT_SUMMARY=      	Free implementation of the .NET platform including runtime and compiler
COMPONENT_FMRI=         developer/lang/mono
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
    sha256:535951d980f45d453beb99f2ce957e38955f106b790a073dbbc36e5265abdef8
COMPONENT_ARCHIVE_URL=	https://download.mono-project.com/sources/$(COMPONENT_NAME)/nightly/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=	Development/Other Languages
COMPONENT_LICENSE=      MIT

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)
unexport SHELLOPTS

GCC_VERSION = 11

LDFLAGS += -lpthread

COMPONENT_PREP_ACTION= \
    cd $(@D); rm external/bdwgc/config.status

CONFIGURE_OPTIONS += --disable-werror --enable-dtrace=no