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
# Copyright (c) 2014, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME		= indri
COMPONENT_VERSION	= 5.11
COMPONENT_REVISION= 1
COMPONENT_FMRI		= library/indri
COMPONENT_SUMMARY	= indri - Text search engine
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_PROJECT_URL	= http://lemurproject.org/indri.php
COMPONENT_SRC		= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE 	= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH	= \
  sha256:ee975cc4dc83738009fa42889bc1a921706562bed4afbea3b10e8a7a0ed13d1c
COMPONENT_ARCHIVE_URL	= \
  http://sourceforge.net/projects/lemur/files/lemur/$(COMPONENT_SRC)/$(COMPONENT_SRC).tar.gz/download
COMPONENT_LICENSE	= Indri license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION	 = $(CLONEY) $(SOURCE_DIR) $(@D)
COMPONENT_INSTALL_ARGS		 = "includedir=$(PROTOUSRINCDIR)"
COMPONENT_INSTALL_ARGS		+= "datarootdir=$(PROTOUSRSHAREDIR)"

$(BUILD_DIR_32)/.installed: COMPONENT_INSTALL_ARGS += "bindir=$(PROTOUSRBINDIR)"
$(BUILD_DIR_32)/.installed: COMPONENT_INSTALL_ARGS += "libdir=$(PROTOUSRLIBDIR)"
$(BUILD_DIR_64)/.installed: COMPONENT_INSTALL_ARGS += "bindir=$(PROTOUSRBINDIR64)"
$(BUILD_DIR_64)/.installed: COMPONENT_INSTALL_ARGS += "libdir=$(PROTOUSRLIBDIR64)"
# Because of 18041236
$(BUILD_DIR_64)/.built:     LD_B_DIRECT =

COMPONENT_POST_BUILD_ACTION = \
	(cd $(@D) ; $(ENV) $(COMPONENT_BUILD_ENV) \
		$(GMAKE) -f Makefile.app)

GPATCH_FLAGS += -E # remove empty files

# common targets
build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)

test:           $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
