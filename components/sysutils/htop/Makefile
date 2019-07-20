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

#
# Copyright 2018, Aurelien Larcher
# Copyright 2019, Michal Nowak
#

PREFERRED_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		htop
COMPONENT_VERSION=	2.2.0
COMPONENT_REVISION=	2
COMPONENT_FMRI=		diagnostic/htop
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_SUMMARY=	htop - an interactive process viewer for Unix
COMPONENT_PROJECT_URL=	https://hisham.hm/htop/
COMPONENT_SRC=		htop-220-sunos_11-p2
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:8cb90827a719ee0ca0aafce776ed0bc027565be448aea99ee70dae2fa65bd6f6
# htop is broken without https://github.com/hishamhm/htop/pull/880 and
# as upstream seems stalled on this (and other things), we opt for a source
# which has illumos fixes included. Revert to the source below once merged:
#
# COMPONENT_SRC=	$(COMPONENT_NAME)-$(COMPONENT_VERSION)
# COMPONENT_ARCHIVE_URL= \
# 	https://hisham.hm/htop/releases/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_URL= \
	https://github.com/ninefathom/htop/archive/220-sunos_11-p2.tar.gz
COMPONENT_LICENSE=  GPLv2 

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION= ( cd $(@D); $(RM) config.h; sh autogen.sh )

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
