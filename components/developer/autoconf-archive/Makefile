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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         autoconf-archive
COMPONENT_VERSION=      2018.03.13
IPS_COMPONENT_VERSION=  2018.3.13
COMPONENT_FMRI=         developer/build/autoconf-archive
COMPONENT_SUMMARY=      GNU Autoconf Archive
COMPONENT_CLASSIFICATION=Development/GNU
COMPONENT_PROJECT_URL=  http://www.gnu.org/software/autoconf-archive/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=  \
  sha256:6175f90d9fa64c4d939bdbb3e8511ae0ee2134863a2c7bf8d9733819efa6e159
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnu.org/gnu/autoconf-archive/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      GPLv3  

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

# Build dependencies
REQUIRED_PACKAGES += developer/macro/gnu-m4
REQUIRED_PACKAGES += developer/build/autoconf-archive
