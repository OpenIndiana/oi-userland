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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         cdrtools
COMPONENT_VERSION=      3.02a09
IPS_COMPONENT_VERSION=	3.0.2
COMPONENT_REVISION=     1
COMPONENT_SUMMARY=	CD/DVD/BluRay command line recording software
COMPONENT_DESCRIPTION=	the cdrtools CD/DVD/BluRay recording software
COMPONENT_SRC=          $(COMPONENT_NAME)-3.02
COMPONENT_PROJECT_URL= 	http://sourceforge.net/projects/cdrtools/
COMPONENT_ARCHIVE=      $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:c7e4f732fb299e9b5d836629dadf5512aa5e6a5624ff438ceb1d056f4dcb07c2
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)files/$(COMPONENT_ARCHIVE)/download
COMPONENT_FMRI=	media/cdrtools
COMPONENT_CLASSIFICATION=       System/Media
COMPONENT_LICENSE=      CDDLv1.0, GPLv2, LGPLv2.1, BSD 2 clause

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=	$(GCC_ROOT)/bin:/usr/bin:/usr/gnu/bin

COMPONENT_INSTALL_ARGS +=  GMAKE_NOWARN=true
COMPONENT_BUILD_ARGS += GMAKE_NOWARN=true

build:          $(BUILD_32)

install:        $(INSTALL_32)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += system/library
