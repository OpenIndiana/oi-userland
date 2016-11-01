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
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#

BUILD_ARCH= i386
BUILD_BITS= 64
# component fails to build with Studio
COMPILER= gcc
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		shim
COMPONENT_VERSION=	0.9
COMPONENT_PROJECT_URL=  https://github.com/rhinstaller/$(COMPONENT_NAME)
COMPONENT_ARCHIVE_HASH= \
    sha256:d277d7bea0b5d554dacf284d84252a5e995fb4ef54b6de5ec6296c6c2a9a21bd
COMPONENT_ARCHIVE_URL=  https://github.com/rhinstaller/$(COMPONENT_NAME)/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_BUGDB=	boot/shim

TPNO=			25414

BUILD_STYLE= justmake
TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION +=(cp elf_x86_64_efi_sol2.lds $(SOURCE_DIR))

ORACLE_CERT=$(SOURCE_DIR)/../OL7Secureboot.cer
export VENDOR_CERT_FILE=$(ORACLE_CERT)
PATH=$(GNUBIN):/usr/bin

REQUIRED_PACKAGES += developer/gcc
REQUIRED_PACKAGES += developer/gnu-binutils
ifeq ($(MACH), i386)
REQUIRED_PACKAGES += developer/sbsigntool
REQUIRED_PACKAGES += library/libgnuefi
endif
REQUIRED_PACKAGES += text/text-utilities
