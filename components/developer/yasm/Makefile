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
# Copyright 2011 EveryCity Ltd. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         yasm
COMPONENT_VERSION=      1.3.0
COMPONENT_REVISION=     2
COMPONENT_SUMMARY=		The Yasm Modular Assembler
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  https://yasm.tortall.net/
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:3dce6601b495f5b3d45b59f7d2492a340ee7e84b5beca17e48f862502bd5603f
COMPONENT_ARCHIVE_URL=  https://www.tortall.net/projects/yasm/releases/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			developer/assembler/yasm
COMPONENT_CLASSIFICATION= Development/Other Languages
COMPONENT_LICENSE=		BSD
COMPONENT_LICENSE_FILE=	BSD.txt


TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

REQUIRED_PACKAGES += system/library
