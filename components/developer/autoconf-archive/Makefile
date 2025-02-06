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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         autoconf-archive
COMPONENT_VERSION=  	2024.10.16
#HUMAN_VERSION=  		2024.10.16
COMPONENT_SUMMARY=      GNU Autoconf Archive
COMPONENT_PROJECT_URL=  https://www.gnu.org/software/autoconf-archive/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/gnu/autoconf-archive/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:7bcd5d001916f3a50ed7436f4f700e3d2b1bade3ed803219c592d62502a57363
COMPONENT_FMRI=         developer/build/autoconf-archive
COMPONENT_CLASSIFICATION=Development/GNU
COMPONENT_LICENSE=      GPLv3  

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --docdir=$(USRSHAREDIR)/autoconf-archive

# Manually added build dependencies
REQUIRED_PACKAGES += developer/macro/gnu-m4

# Auto-generated dependencies
