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
# Copyright 2020, Andreas Wacknitz
# Copyright 2023, Niklas Poslovski
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         apr
COMPONENT_VERSION=      1.7.4
COMPONENT_SUMMARY=      Apache Portable Runtime (APR) Shared Libraries
COMPONENT_PROJECT_URL=  https://apr.apache.org/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:a4137dd82a185076fa50ba54232d920a17c6469c30b0876569e1c2a05ff311d9
COMPONENT_ARCHIVE_URL=  https://archive.apache.org/dist/apr/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/apr
COMPONENT_CLASSIFICATION=Web Services/Application and Web Servers
COMPONENT_LICENSE=      Apache v2.0
COMPONENT_LICENSE_FILE= LICENSE

include $(WS_MAKE_RULES)/common.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

PATCH_LEVEL = 0

CFLAGS += -DSSL_EXPERIMENTAL -DSSL_ENGINE

COMPONENT_PRE_CONFIGURE_ACTION += ( $(CLONEY) $(SOURCE_DIR) $(@D) );
COMPONENT_PRE_CONFIGURE_ACTION += ( cd $(@D); autoconf )

CONFIGURE_SCRIPT = $(@D)/configure

CONFIGURE_PREFIX = $(USRDIR)/apr

CONFIGURE_OPTIONS += --enable-threads
CONFIGURE_OPTIONS += --enable-other-child
CONFIGURE_OPTIONS += --enable-nonportable-atomics
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += LTFLAGS="--tag=CC --silent"
CONFIGURE_OPTIONS += --enable-layout=OpenSolaris-$(MACH64)
CONFIGURE_OPTIONS += --bindir=$(CONFIGURE_PREFIX)/bin

COMPONENT_POST_INSTALL_ACTION += \
    cd $(SOURCE_DIR); \
    $(GSED) 's;OUTPUT_DIRECTORY=.*;OUTPUT_DIRECTORY=$(PROTO_DIR)$(CONFIGURE_PREFIX);' \
          docs/doxygen.conf | doxygen - ;

COMPONENT_TEST_TARGETS = test
COMPONENT_TEST_TRANSFORMS += \
	' -n ' \
	' -e "/OK/p" ' \
	' -e "/SUCCESS/p" '

# Build dependencies
REQUIRED_PACKAGES += developer/documentation-tool/doxygen

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
