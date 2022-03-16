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
# Copyright 2018 Aurelien Larcher
# Copyright 2020, 2022 Andreas Wacknitz
#

BUILD_BITS=	64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         autoconf-archive
COMPONENT_VERSION=      2022.2.11
HUMAN_VERSION=  		2022.02.11
COMPONENT_FMRI=         developer/build/autoconf-archive
COMPONENT_SUMMARY=      GNU Autoconf Archive
COMPONENT_CLASSIFICATION=Development/GNU
COMPONENT_PROJECT_URL=  https://www.gnu.org/software/autoconf-archive/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:78a61b611e2eeb55a89e0398e0ce387bcaf57fe2dd53c6fe427130f777ad1e8c
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/gnu/autoconf-archive/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      GPLv3  

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --docdir=$(USRSHAREDIR)/autoconf-archive

# Manually added build dependencies
REQUIRED_PACKAGES += developer/macro/gnu-m4

# Auto-generated dependencies
