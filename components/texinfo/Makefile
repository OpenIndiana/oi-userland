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
# Copyright (c) 2012, 2015, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		texinfo
COMPONENT_VERSION=	4.13
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/texinfo/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:1303e91a1c752b69a32666a407e9fbdd6e936def4b09bc7de30f416301530d68
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/texinfo/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/texinfo

TPNO_TEXINFO=		7876
TPNO_TEXI2HTML=		9089

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

INFOPATH := /usr/share/info
INFOPATH := $(INFOPATH):/usr/sfw/share/info
INFOPATH := $(INFOPATH):/usr/gnu/share/info
INFOPATH := $(INFOPATH):/usr/local/share/info
INFOPATH := $(INFOPATH):.

CPPFLAGS += -DDEFAULT_INFOPATH=\\\"$(INFOPATH)\\\"

CONFIGURE_OPTIONS  +=		--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  +=		CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS  +=		CPPFLAGS="$(CPPFLAGS)"

ASLR_MODE = $(ASLR_ENABLE)

# common targets
configure:	$(CONFIGURE_64)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

system-test:    $(NO_TESTS)


REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += runtime/perl-512
REQUIRED_PACKAGES += runtime/python-26
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library
