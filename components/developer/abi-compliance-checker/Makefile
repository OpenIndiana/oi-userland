#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= abi-compliance-checker
COMPONENT_VERSION= 31007a47094495e4e63edc5a226241ca3811701d
# We build post-release version as it contains Solaris-related fixes
IPS_COMPONENT_VERSION= 1.99.25
COMPONENT_SUMMARY= A tool for checking backward API/ABI compatibility of a C/C++ library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_HASH= \
  sha256:fe35c8cf8ebcbd22c30014c32d39946bf1bdb555a35a85d7d8abf4cbab830f03
COMPONENT_ARCHIVE_URL= \
  https://github.com/lvc/abi-compliance-checker/archive/$(COMPONENT_VERSION).zip
COMPONENT_PROJECT_URL = https://abi-laboratory.pro/
COMPONENT_CLASSIFICATION = Development/C
COMPONENT_FMRI = developer/abi-compliance-checker
COMPONENT_LICENSE = LGPLv2.0
COMPONENT_LICENSE_FILE = LGPL-2.0

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

# We use build target just to clone $(SOURCE_DIR) to $(BUILD_DIR_32)
COMPONENT_BUILD_ACTION= /bin/true

COMPONENT_INSTALL_ACTION = \
	$(MKDIR) $(PROTO_DIR)/usr/bin ; \
        cd $(@D); $(ENV) $(COMPONENT_BUILD_ENV) \
        $(PERL) Makefile.pl -install --destdir=$(PROTO_DIR)

build: $(BUILD_32)

install: $(INSTALL_32)

REQUIRED_PACKAGES += developer/exuberant-ctags
REQUIRED_PACKAGES += developer/gcc-49
REQUIRED_PACKAGES += developer/gnu-binutils
REQUIRED_PACKAGES += runtime/perl-522
