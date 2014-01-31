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
# Copyright (c) 2011, 2014, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=         cdrtools
COMPONENT_VERSION=      3.01
IPS_COMPONENT_VERSION=  3.1 # Zero not allowed in front of number
COMPONENT_SUBVERSION=   a22
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL= 	http://cdrecord.berlios.de/private/cdrecord.html 
COMPONENT_ARCHIVE=      $(COMPONENT_SRC)$(COMPONENT_SUBVERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:facd40dc66f1499dfe936e647b694bee7a12cd63afd901a35bec855d9e3600a5
COMPONENT_ARCHIVE_URL=  ftp://ftp.berlios.de/pub/cdrecord/alpha/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/cdrtools

PATH=			$(SPRO_VROOT)/bin:/usr/bin:/usr/gnu/bin
ifeq   ($(strip $(PARFAIT_BUILD)),yes)
PATH=$(PARFAIT_TOOLS):$(SPRO_VROOT)/bin:/usr/bin
endif

include ../../make-rules/prep.mk
include ../../make-rules/justmake.mk
include ../../make-rules/ips.mk

COMPONENT_INSTALL_ARGS +=  GMAKE_NOWARN=true
COMPONENT_BUILD_ARGS += GMAKE_NOWARN=true
ifeq   ($(strip $(PARFAIT_BUILD)),yes)
COMPONENT_BUILD_ENV +=	"ac_cv_exeext=no"
COMPONENT_BUILD_ENV +=	"ac_cv_objext=o"
endif


build:          $(BUILD_32)

install:        $(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =        $(BUILD_TOOLS)

include ../../make-rules/depend.mk
